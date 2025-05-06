#include "llvm_generator.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> // For assert, if you choose to use it

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h> // Not used yet, but often for JIT
#include <llvm-c/Target.h>
// #include <llvm-c/Transforms/Scalar.h> // Still commented if causing LLVM install issues
#include <llvm-c/Analysis.h>        // For LLVMVerifyModule, LLVMVerifyFunction

// --- Simple Symbol Table Implementation ---
#define SYMBOL_TABLE_SIZE 100
typedef struct Symbol {
    char* name;
    LLVMValueRef value; // LLVMValueRef for variables (AllocaInst) or functions (FunctionValue)
    LLVMTypeRef type;   // For functions, this is the LLVMFunctionType; for variables, the AllocaInst's type
    int is_param;       // Differentiates params (which are allocas here) from other local allocas
} Symbol;

typedef struct SymbolTable {
    Symbol entries[SYMBOL_TABLE_SIZE];
    int count;
    struct SymbolTable* parent; // For scoping
} SymbolTable;

SymbolTable* create_symbol_table(SymbolTable* parent) {
    SymbolTable* st = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!st) { perror("malloc for SymbolTable"); exit(EXIT_FAILURE); }
    st->count = 0;
    st->parent = parent;
    memset(st->entries, 0, sizeof(st->entries)); // Initialize all entries to zero/NULL
    return st;
}

void add_symbol(SymbolTable* st, const char* name, LLVMValueRef value, LLVMTypeRef type, int is_param) {
    if (!st || !name) return;
    if (st->count >= SYMBOL_TABLE_SIZE) {
        fprintf(stderr, "Symbol table overflow for symbol '%s'\n", name);
        return;
    }
    // Check if symbol already exists in the current scope (simple check)
    for(int i=0; i < st->count; ++i) {
        if (st->entries[i].name && strcmp(st->entries[i].name, name) == 0) {
            // fprintf(stderr, "Warning: Symbol '%s' redefined in current scope. Updating.\n", name);
            st->entries[i].value = value; // Update existing entry
            st->entries[i].type = type;
            st->entries[i].is_param = is_param;
            return;
        }
    }
    // Add new symbol
    st->entries[st->count].name = strdup(name);
    if (!st->entries[st->count].name && name) { perror("strdup for symbol name"); exit(EXIT_FAILURE); }
    st->entries[st->count].value = value;
    st->entries[st->count].type = type;
    st->entries[st->count].is_param = is_param;
    st->count++;
}

Symbol* find_symbol(SymbolTable* st, const char* name) {
    if (!name) return NULL;
    SymbolTable* current = st;
    while (current) {
        for (int i = 0; i < current->count; i++) {
            if (current->entries[i].name && strcmp(current->entries[i].name, name) == 0) {
                return &current->entries[i]; // Fixed: changed "¤t" to "current"
            }
        }
        current = current->parent;
    }
    return NULL;
}

void free_symbol_table(SymbolTable* st) {
    if (!st) return;
    for (int i = 0; i < st->count; i++) {
        if (st->entries[i].name) free(st->entries[i].name);
    }
    // Do not free st->parent here; parent scopes are managed by their creators
    free(st);
}
// --- End Simple Symbol Table ---

// Forward declarations for codegen functions
static LLVMValueRef codegen_expr(LLVMGeneratorState *state, ASTNode *node);
static void codegen_statement_list_payload(LLVMGeneratorState *state, StatementListPayload *payload);

void llvm_initialize() {
    // LLVMInitializeCore(LLVMGetGlobalPassRegistry()); // Often not needed for basic setup with modern LLVM
    LLVMInitializeNativeTarget();      // Initialize the native target for JIT and AOT compilation
    LLVMInitializeNativeAsmPrinter();  // Initialize the native assembly printer
    LLVMInitializeNativeAsmParser();   // Initialize the native assembly parser
}

void llvm_shutdown() {
    // LLVMShutdown(); // Generally not required unless specific resource cleanup is critical
}

LLVMGeneratorState* create_llvm_generator_state() {
    LLVMGeneratorState* state = (LLVMGeneratorState*) malloc(sizeof(LLVMGeneratorState));
    if (!state) { perror("malloc for LLVMGeneratorState"); exit(EXIT_FAILURE); }
    state->context = LLVMContextCreate();
    state->module = LLVMModuleCreateWithNameInContext("flowscript_module", state->context);
    state->builder = LLVMCreateBuilderInContext(state->context);
    state->current_function = NULL;
    state->piped_value = NULL;
    state->current_loop_var_name = NULL; // For loop variable name (less critical if using symbol table)
    state->current_loop_var_ptr = NULL;  // LLVMValueRef for the loop variable's memory
    state->current_loop_cond_bb = NULL;  // Target for 'continue' (usually increment/re-check block)
    state->current_loop_end_bb = NULL;   // Target for 'break'

    state->global_symbols = create_symbol_table(NULL);    // Global scope has no parent
    state->current_scope_symbols = state->global_symbols; // Initially, we are in the global scope
    return state;
}

void free_llvm_generator_state(LLVMGeneratorState* state) {
    if (!state) return;
    // global_symbols is the root. current_scope_symbols should point to global_symbols
    // or a scope that was already freed when its context (e.g., function) ended.
    if (state->global_symbols) {
        free_symbol_table(state->global_symbols);
    }
    LLVMDisposeBuilder(state->builder);
    LLVMDisposeModule(state->module);
    LLVMContextDispose(state->context);
    free(state);
}

// Helper to get the signature type of a function if func_val is an LLVMValueRef for the function
LLVMTypeRef get_function_signature_type_from_value(LLVMValueRef func_val) {
    if (!func_val) return NULL;
    LLVMTypeRef type_of_func_val = LLVMTypeOf(func_val); // This is typically a pointer to a function type

    if (LLVMGetTypeKind(type_of_func_val) == LLVMPointerTypeKind) {
        LLVMTypeRef pointee_type = LLVMGetElementType(type_of_func_val);
        if (LLVMGetTypeKind(pointee_type) == LLVMFunctionTypeKind) {
            return pointee_type; // This is the LLVMFunctionType
        }
    } else if (LLVMGetTypeKind(type_of_func_val) == LLVMFunctionTypeKind) {
        // This case might happen if func_val was already the LLVMFunctionType,
        // e.g., directly from a symbol table storing it.
        return type_of_func_val;
    }
    // If it's not a pointer to a function or a function type directly, something is wrong.
    char* type_str = LLVMPrintTypeToString(type_of_func_val);
    fprintf(stderr, "Error in get_function_signature_type_from_value: value is not a function or pointer to function. Type: %s\n", type_str);
    LLVMDisposeMessage(type_str);
    return NULL;
}


// Gets or declares the 'printf' function in the LLVM module
LLVMValueRef get_printf_function(LLVMGeneratorState* state) {
    LLVMValueRef printf_func_val = LLVMGetNamedFunction(state->module, "printf");
    if (!printf_func_val) {
        // Define printf signature: int printf(const char* format, ...)
        LLVMTypeRef printf_return_type = LLVMInt32TypeInContext(state->context);
        LLVMTypeRef printf_format_arg_type = LLVMPointerType(LLVMInt8TypeInContext(state->context), 0); // char*
        LLVMTypeRef printf_arg_types[] = { printf_format_arg_type };
        LLVMTypeRef printf_signature_type = LLVMFunctionType(
            printf_return_type,
            printf_arg_types,     // Array of fixed argument types
            1,                    // Number of fixed arguments
            1                     // Is variadic (true for ...)
        );
        printf_func_val = LLVMAddFunction(state->module, "printf", printf_signature_type);
    }
    return printf_func_val;
}

static LLVMValueRef codegen_number(LLVMGeneratorState *state, NumberNode *node) {
    return LLVMConstInt(LLVMInt32TypeInContext(state->context), node->value, 0);
}

static LLVMValueRef codegen_identifier(LLVMGeneratorState *state, IdentifierNode *node, ASTNode* parent_node) {
    Symbol* sym = find_symbol(state->current_scope_symbols, node->name);
    if (!sym) {
        fprintf(stderr, "Line %d: Undeclared identifier '%s'\n", parent_node->line_num, node->name);
        return NULL;
    }

    // If sym->value is an AllocaInst (a pointer to stack space for a variable), load its value.
    // LLVMIsAAllocaInst checks if the LLVMValueRef is an instance of AllocaInst.
    if (LLVMIsAAllocaInst(sym->value)) {
        LLVMTypeRef alloca_type = LLVMTypeOf(sym->value); // This is PointerType(ElementType)
        LLVMTypeRef element_type = LLVMGetElementType(alloca_type); // This is ElementType
        return LLVMBuildLoad2(state->builder, element_type, sym->value, node->name);
    }
    // Otherwise, sym->value is assumed to be a direct value (e.g., an LLVMValueRef for a function).
    return sym->value;
}

static LLVMValueRef codegen_binop(LLVMGeneratorState *state, BinaryOpNode *node, ASTNode* parent_node) {
    LLVMValueRef L = codegen_expr(state, node->left);
    LLVMValueRef R = NULL; // R is evaluated conditionally for short-circuit ops

    if (node->op != OP_AND && node->op != OP_OR) { // For non-short-circuit ops, evaluate R now
        R = codegen_expr(state, node->right);
    }

    if (!L || (node->op != OP_AND && node->op != OP_OR && !R) ) { // Check for errors in operands
        fprintf(stderr, "Line %d: Error in operand(s) for binary operation.\n", parent_node->line_num);
        return NULL;
    }

    switch (node->op) {
        case OP_PLUS: return LLVMBuildAdd(state->builder, L, R, "addtmp");
        case OP_MINUS: return LLVMBuildSub(state->builder, L, R, "subtmp");
        case OP_MULTIPLY: return LLVMBuildMul(state->builder, L, R, "multmp");
        case OP_DIVIDE: return LLVMBuildSDiv(state->builder, L, R, "divtmp"); // Signed division
        case OP_LT: return LLVMBuildICmp(state->builder, LLVMIntSLT, L, R, "lttmp");
        case OP_GT: return LLVMBuildICmp(state->builder, LLVMIntSGT, L, R, "gttmp");
        case OP_LTE: return LLVMBuildICmp(state->builder, LLVMIntSLE, L, R, "ltetmp");
        case OP_GTE: return LLVMBuildICmp(state->builder, LLVMIntSGE, L, R, "gtetmp");
        case OP_EQ: return LLVMBuildICmp(state->builder, LLVMIntEQ, L, R, "eqtmp");
        case OP_NEQ: return LLVMBuildICmp(state->builder, LLVMIntNE, L, R, "neqtmp");
        case OP_AND:
        {
            LLVMBasicBlockRef eval_L_block = LLVMGetInsertBlock(state->builder);
            LLVMValueRef func = LLVMGetBasicBlockParent(eval_L_block);
            LLVMBasicBlockRef eval_R_block = LLVMAppendBasicBlockInContext(state->context, func, "and.evalR");
            LLVMBasicBlockRef merge_block = LLVMAppendBasicBlockInContext(state->context, func, "and.merge");

            LLVMValueRef l_bool = LLVMBuildICmp(state->builder, LLVMIntNE, L, LLVMConstNull(LLVMTypeOf(L)), "tobool.l");
            LLVMBuildCondBr(state->builder, l_bool, eval_R_block, merge_block); // If L is false, result is false (0), go to merge

            LLVMPositionBuilderAtEnd(state->builder, eval_R_block); // L is true, so we must evaluate R
            LLVMValueRef R_val_for_and = codegen_expr(state, node->right); // Evaluate R here
            if(!R_val_for_and) R_val_for_and = LLVMConstInt(LLVMInt1TypeInContext(state->context), 0, 0); // Default on error
            LLVMValueRef r_bool = LLVMBuildICmp(state->builder, LLVMIntNE, R_val_for_and, LLVMConstNull(LLVMTypeOf(R_val_for_and)), "tobool.r");
            LLVMBasicBlockRef r_evaluated_block = LLVMGetInsertBlock(state->builder); // Block after R is evaluated
            LLVMBuildBr(state->builder, merge_block);

            LLVMPositionBuilderAtEnd(state->builder, merge_block);
            LLVMValueRef phi = LLVMBuildPhi(state->builder, LLVMInt1TypeInContext(state->context), "andtmp");
            LLVMValueRef incoming_vals[] = {r_bool, LLVMConstInt(LLVMInt1TypeInContext(state->context), 0, 0)}; // Value if L was true, Value if L was false
            LLVMBasicBlockRef incoming_blocks[] = {r_evaluated_block, eval_L_block};
            LLVMAddIncoming(phi, incoming_vals, incoming_blocks, 2);
            return phi;
        }
        case OP_OR:
        {
            LLVMBasicBlockRef eval_L_block = LLVMGetInsertBlock(state->builder);
            LLVMValueRef func = LLVMGetBasicBlockParent(eval_L_block);
            LLVMBasicBlockRef eval_R_block = LLVMAppendBasicBlockInContext(state->context, func, "or.evalR");
            LLVMBasicBlockRef merge_block = LLVMAppendBasicBlockInContext(state->context, func, "or.merge");

            LLVMValueRef l_bool = LLVMBuildICmp(state->builder, LLVMIntNE, L, LLVMConstNull(LLVMTypeOf(L)), "tobool.l");
            LLVMBuildCondBr(state->builder, l_bool, merge_block, eval_R_block); // If L true, result is true (1), go to merge

            LLVMPositionBuilderAtEnd(state->builder, eval_R_block); // L is false, so we must evaluate R
            LLVMValueRef R_val_for_or = codegen_expr(state, node->right); // Evaluate R here
            if(!R_val_for_or) R_val_for_or = LLVMConstInt(LLVMInt1TypeInContext(state->context), 0, 0);
            LLVMValueRef r_bool = LLVMBuildICmp(state->builder, LLVMIntNE, R_val_for_or, LLVMConstNull(LLVMTypeOf(R_val_for_or)), "tobool.r");
            LLVMBasicBlockRef r_evaluated_block = LLVMGetInsertBlock(state->builder);
            LLVMBuildBr(state->builder, merge_block);

            LLVMPositionBuilderAtEnd(state->builder, merge_block);
            LLVMValueRef phi = LLVMBuildPhi(state->builder, LLVMInt1TypeInContext(state->context), "ortmp");
            LLVMValueRef incoming_vals[] = {LLVMConstInt(LLVMInt1TypeInContext(state->context), 1, 0), r_bool}; // Value if L was true, Value if L was false
            LLVMBasicBlockRef incoming_blocks[] = {eval_L_block, r_evaluated_block};
            LLVMAddIncoming(phi, incoming_vals, incoming_blocks, 2);
            return phi;
        }
        default: fprintf(stderr, "Line %d: Unknown binary operator %d\n", parent_node->line_num, node->op); return NULL;
    }
}

static LLVMValueRef codegen_unaryop(LLVMGeneratorState *state, UnaryOpNode *node, ASTNode* parent_node) {
    LLVMValueRef operand = codegen_expr(state, node->operand);
    if (!operand) return NULL;
    switch (node->op) {
        case OP_NOT: // Logical not: (operand == 0)
            return LLVMBuildICmp(state->builder, LLVMIntEQ, operand, LLVMConstNull(LLVMTypeOf(operand)), "nottmp");
        case OP_MINUS: // Arithmetic negation
             return LLVMBuildNeg(state->builder, operand, "negtmp");
        default:
            fprintf(stderr, "Line %d: Unknown unary operator %d\n", parent_node->line_num, node->op);
            return NULL;
    }
}

static LLVMValueRef codegen_assignment(LLVMGeneratorState *state, AssignmentNode *node, ASTNode* parent_node) {
    LLVMValueRef val_to_assign = codegen_expr(state, node->expression);
    if (!val_to_assign) {
        fprintf(stderr, "Line %d: Expression for assignment to '%s' failed to generate code.\n", parent_node->line_num, node->var_name);
        return NULL;
    }

    Symbol* sym = find_symbol(state->current_scope_symbols, node->var_name);
    LLVMValueRef var_storage_ptr; // This will be an AllocaInst or GlobalVariable (a pointer)

    if (!sym) { // Variable not found, implicitly declare it
        LLVMTypeRef val_type = LLVMTypeOf(val_to_assign);
        if (state->current_function) { // Local variable
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(state->current_function);
            LLVMBuilderRef TmpB = LLVMCreateBuilderInContext(state->context); // Temp builder for alloca at func entry
            if (LLVMGetFirstInstruction(entry_block)) {
                 LLVMPositionBuilder(TmpB, entry_block, LLVMGetFirstInstruction(entry_block));
            } else {
                 LLVMPositionBuilderAtEnd(TmpB, entry_block);
            }
            var_storage_ptr = LLVMBuildAlloca(TmpB, val_type, node->var_name);
            LLVMDisposeBuilder(TmpB);
        } else { // Global variable (should only happen if compiling top-level script code not in 'main')
            var_storage_ptr = LLVMAddGlobal(state->module, val_type, node->var_name);
            LLVMSetInitializer(var_storage_ptr, LLVMConstNull(val_type)); // Globals should be initialized
        }
        add_symbol(state->current_scope_symbols, node->var_name, var_storage_ptr, val_type, 0); // Store type of value, not ptr
    } else { // Variable already exists
        var_storage_ptr = sym->value;
        if (!LLVMIsAAllocaInst(var_storage_ptr) && !LLVMIsAGlobalVariable(var_storage_ptr)) {
            fprintf(stderr, "Line %d: Cannot assign to '%s' as it is not a modifiable variable (e.g. function name).\n", parent_node->line_num, node->var_name);
            return NULL;
        }
        LLVMTypeRef var_element_type = LLVMGetElementType(LLVMTypeOf(var_storage_ptr));
        if (LLVMTypeOf(val_to_assign) != var_element_type) {
            char* expected_t_str = LLVMPrintTypeToString(var_element_type);
            char* got_t_str = LLVMPrintTypeToString(LLVMTypeOf(val_to_assign));
            fprintf(stderr, "Line %d: Type mismatch in assignment to '%s'. Expected %s, got %s.\n",
                parent_node->line_num, node->var_name, expected_t_str, got_t_str);
            LLVMDisposeMessage(expected_t_str);
            LLVMDisposeMessage(got_t_str);
            // return NULL; // Or attempt cast, or let LLVM potentially error
        }
    }
    LLVMBuildStore(state->builder, val_to_assign, var_storage_ptr);
    return val_to_assign; // Assignment expression evaluates to the assigned value
}

static LLVMValueRef codegen_func_def(LLVMGeneratorState *state, FunctionDefNode *fnode, ASTNode* parent_node) {
    unsigned int param_count = fnode->param_count;
    LLVMTypeRef *param_llvm_types = NULL;
    if (param_count > 0) {
        param_llvm_types = (LLVMTypeRef*)malloc(param_count * sizeof(LLVMTypeRef));
        if (!param_llvm_types) { perror("malloc for param_llvm_types"); exit(EXIT_FAILURE); }
        for (unsigned int i = 0; i < param_count; i++) {
            param_llvm_types[i] = LLVMInt32TypeInContext(state->context); // All params are i32 for now
        }
    }

    LLVMTypeRef return_llvm_type = LLVMInt32TypeInContext(state->context); // Default to i32 return type

    LLVMTypeRef func_signature_type = LLVMFunctionType(return_llvm_type, param_llvm_types, param_count, 0); // isVarArg = false
    LLVMValueRef func_val = LLVMAddFunction(state->module, fnode->func_name, func_signature_type);
    add_symbol(state->global_symbols, fnode->func_name, func_val, func_signature_type, 0); // Store func & its signature type

    LLVMBasicBlockRef preserved_insert_block = LLVMGetInsertBlock(state->builder);
    LLVMValueRef preserved_current_func = state->current_function;
    SymbolTable* preserved_current_scope = state->current_scope_symbols;

    state->current_function = func_val;
    state->current_scope_symbols = create_symbol_table(state->global_symbols); // New scope for function params/locals

    LLVMBasicBlockRef entry_bb = LLVMAppendBasicBlockInContext(state->context, func_val, "entry");
    LLVMPositionBuilderAtEnd(state->builder, entry_bb);

    for (unsigned int i = 0; i < param_count; i++) {
        LLVMValueRef param_val_from_caller = LLVMGetParam(func_val, i);
        LLVMSetValueName(param_val_from_caller, fnode->param_names[i]);
        LLVMValueRef param_alloca = LLVMBuildAlloca(state->builder, param_llvm_types[i], fnode->param_names[i]);
        LLVMBuildStore(state->builder, param_val_from_caller, param_alloca);
        add_symbol(state->current_scope_symbols, fnode->param_names[i], param_alloca, param_llvm_types[i], 1);
    }
    if (param_count > 0) free(param_llvm_types);

    if (fnode->body_stmts_node && fnode->body_stmts_node->type == NODE_STATEMENT_LIST) {
        codegen_statement_list_payload(state, &fnode->body_stmts_node->data.statement_list_payload);
    }

    LLVMBasicBlockRef last_block_in_func = LLVMGetInsertBlock(state->builder);
    if (last_block_in_func && LLVMGetBasicBlockTerminator(last_block_in_func) == NULL) {
        if (LLVMGetTypeKind(LLVMGetReturnType(func_signature_type)) == LLVMVoidTypeKind) {
            LLVMBuildRetVoid(state->builder);
        } else {
             LLVMBuildRet(state->builder, LLVMConstInt(LLVMInt32TypeInContext(state->context), 0, 0));
             // fprintf(stderr, "Warning: Function '%s' (Line %d) missing explicit return for non-void type; defaulting to return 0.\n", fnode->func_name, parent_node->line_num);
        }
    }
    
    char *error_msg = NULL;
    if (LLVMVerifyFunction(func_val, LLVMReturnStatusAction)) { // Check return status
         fprintf(stderr, "LLVMVerifyFunction failed for function '%s' (Line %d). Details might be on stderr from LLVM.\n", fnode->func_name, parent_node->line_num);
         // LLVMPrintValueToString(func_val) could give IR if needed, then LLVMDisposeMessage.
    }

    if (preserved_insert_block) LLVMPositionBuilderAtEnd(state->builder, preserved_insert_block);
    else LLVMClearInsertionPosition(state->builder);
    state->current_function = preserved_current_func;
    free_symbol_table(state->current_scope_symbols);
    state->current_scope_symbols = preserved_current_scope;
    return func_val;
}

static LLVMValueRef codegen_func_call(LLVMGeneratorState *state, FunctionCallNode *fnode, LLVMValueRef explicit_piped_input_val, ASTNode* parent_node) {
    Symbol* sym = find_symbol(state->global_symbols, fnode->func_name);
    if (!sym) {
        fprintf(stderr, "Line %d: Call to undefined function '%s'.\n", parent_node->line_num, fnode->func_name);
        return NULL;
    }
    LLVMValueRef func_to_call_val = sym->value;        // LLVMValueRef for the function
    LLVMTypeRef func_signature_type = sym->type; // This is the LLVMFunctionType

    if (!func_signature_type || LLVMGetTypeKind(func_signature_type) != LLVMFunctionTypeKind) {
        fprintf(stderr, "Line %d: Symbol '%s' is not a function or has invalid type information.\n", parent_node->line_num, fnode->func_name);
        return NULL;
    }

    unsigned int expected_param_count = LLVMCountParamTypes(func_signature_type);
    unsigned int actual_arg_count = fnode->arg_count + (explicit_piped_input_val ? 1 : 0);

    if (expected_param_count != actual_arg_count) {
         fprintf(stderr, "Line %d: Incorrect number of arguments for function '%s'. Expected %u, got %u.\n",
            parent_node->line_num, fnode->func_name, expected_param_count, actual_arg_count);
        return NULL;
    }

    LLVMValueRef *call_args_llvm = NULL;
    if (actual_arg_count > 0) {
        call_args_llvm = (LLVMValueRef*)malloc(actual_arg_count * sizeof(LLVMValueRef));
        if (!call_args_llvm) { perror("malloc for call_args_llvm"); exit(EXIT_FAILURE); }
    }

    int current_arg_idx = 0;
    if (explicit_piped_input_val) {
        call_args_llvm[current_arg_idx++] = explicit_piped_input_val;
    }
    for (int i = 0; i < fnode->arg_count; i++) {
        call_args_llvm[current_arg_idx] = codegen_expr(state, fnode->args[i]);
        if (!call_args_llvm[current_arg_idx]) {
            fprintf(stderr, "Line %d: Argument %d for function '%s' failed to generate code.\n", fnode->args[i]->line_num, i + 1, fnode->func_name);
            if (call_args_llvm) free(call_args_llvm);
            return NULL;
        }
        current_arg_idx++;
    }
    
    LLVMValueRef result_val = LLVMBuildCall2(state->builder, func_signature_type, func_to_call_val, call_args_llvm, actual_arg_count, "calltmp");
    if (actual_arg_count > 0) free(call_args_llvm);
    return result_val;
}

static LLVMValueRef codegen_pipeline(LLVMGeneratorState* state, PipelineNode* pnode, ASTNode* parent_node) {
    LLVMValueRef lhs_val_llvm = codegen_expr(state, pnode->left_expr);
    // If pnode->left_expr is NODE_RANGE, lhs_val_llvm is NULL from codegen_range, which is fine.
    // The AST node pnode->left_expr is used for for_loop.

    LLVMValueRef preserved_piped_value_in_state = state->piped_value;
    state->piped_value = lhs_val_llvm; // Make the *LLVM value* of LHS available for RHS if needed (e.g. print, if)

    LLVMValueRef result_llvm = NULL;
    ASTNode* rhs_op_ast_node = pnode->right_op;

    switch (rhs_op_ast_node->type) {
        case NODE_FUNCTION_CALL:
            result_llvm = codegen_func_call(state, &rhs_op_ast_node->data.function_call, lhs_val_llvm, rhs_op_ast_node);
            break;
        case NODE_IF_ELSE:
            // state->piped_value (set to lhs_val_llvm) is implicitly available to codegen_if_else
            result_llvm = codegen_expr(state, rhs_op_ast_node);
            break;
        case NODE_FOR_LOOP:
            {
                ForLoopNode* for_loop_data = &rhs_op_ast_node->data.for_loop;
                ASTNode* original_range_expr_in_for_node = for_loop_data->range_expr; // Expected to be NULL from parser for piped for

                // The LHS of the pipe (pnode->left_expr, an ASTNode) IS the range definition.
                // Temporarily set this AST node onto the ForLoopNode so codegen_for_loop can access it.
                for_loop_data->range_expr = pnode->left_expr;
                result_llvm = codegen_expr(state, rhs_op_ast_node); // This will call codegen_for_loop
                for_loop_data->range_expr = original_range_expr_in_for_node; // Restore (back to NULL)
            }
            break;
        case NODE_PRINT_CALL:
            // codegen_print_call will use state->piped_value if its own expression is NULL
            result_llvm = codegen_expr(state, rhs_op_ast_node);
            break;
        default:
            fprintf(stderr, "Line %d: Invalid AST node type %d on RHS of pipeline.\n", rhs_op_ast_node->line_num, rhs_op_ast_node->type);
    }
    state->piped_value = preserved_piped_value_in_state; // Restore state->piped_value
    return result_llvm;
}

static LLVMValueRef codegen_if_else(LLVMGeneratorState* state, IfElseNode* inode, ASTNode* parent_node) {
    LLVMValueRef condition_val_llvm = codegen_expr(state, inode->condition_expr);
    if (!condition_val_llvm) return NULL;

    if (LLVMTypeOf(condition_val_llvm) != LLVMInt1TypeInContext(state->context)) {
        condition_val_llvm = LLVMBuildICmp(state->builder, LLVMIntNE, condition_val_llvm,
                                      LLVMConstNull(LLVMTypeOf(condition_val_llvm)), "ifcond_tobool");
    }

    LLVMValueRef current_llvm_function = state->current_function;
    if (!current_llvm_function) {
        fprintf(stderr, "Line %d: If statement found outside of a function context.\n", parent_node->line_num);
        return NULL;
    }

    LLVMBasicBlockRef then_bb = LLVMAppendBasicBlockInContext(state->context, current_llvm_function, "then");
    LLVMBasicBlockRef else_bb = LLVMCreateBasicBlockInContext(state->context, "else");
    LLVMBasicBlockRef merge_bb = LLVMCreateBasicBlockInContext(state->context, "ifcont");

    LLVMBuildCondBr(state->builder, condition_val_llvm, then_bb, inode->else_stmts_node ? else_bb : merge_bb);

    LLVMPositionBuilderAtEnd(state->builder, then_bb);
    if (inode->then_stmts_node && inode->then_stmts_node->type == NODE_STATEMENT_LIST) {
        codegen_statement_list_payload(state, &inode->then_stmts_node->data.statement_list_payload);
    }
    if (LLVMGetInsertBlock(state->builder) && !LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(state->builder))) {
        LLVMBuildBr(state->builder, merge_bb);
    }

    if (inode->else_stmts_node) {
        LLVMAppendExistingBasicBlock(current_llvm_function, else_bb);
        LLVMPositionBuilderAtEnd(state->builder, else_bb);
        if (inode->else_stmts_node->type == NODE_STATEMENT_LIST) {
            codegen_statement_list_payload(state, &inode->else_stmts_node->data.statement_list_payload);
        }
        if (LLVMGetInsertBlock(state->builder) && !LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(state->builder))) {
            LLVMBuildBr(state->builder, merge_bb);
        }
    }

    LLVMAppendExistingBasicBlock(current_llvm_function, merge_bb);
    LLVMPositionBuilderAtEnd(state->builder, merge_bb);
    return NULL; // If-else itself does not produce a value in this implementation.
}

static LLVMValueRef codegen_range(LLVMGeneratorState* state, RangeNode* rnode, ASTNode* parent_node) {
    // Evaluate start/end expressions for validation, but codegen_for_loop will re-evaluate them.
    // The "value" of a range AST node for codegen_expr is NULL; it's structural.
    LLVMValueRef start_val_check = codegen_expr(state, rnode->start);
    LLVMValueRef end_val_check = codegen_expr(state, rnode->end);
    if(!start_val_check || !end_val_check) {
        fprintf(stderr, "Line %d: Error evaluating start/end expressions within range node itself.\n", parent_node->line_num);
        return NULL;
    }
    return NULL;
}

static LLVMValueRef codegen_for_loop(LLVMGeneratorState* state, ForLoopNode* fnode, ASTNode* parent_node) {
    if (!state->current_function) {
        fprintf(stderr, "Line %d: For loop found outside of a function.\n", parent_node->line_num);
        return NULL;
    }

    LLVMValueRef start_val_llvm, end_val_llvm;
    // fnode->range_expr is the ASTNode for the range (e.g., NODE_RANGE).
    // It's set by parser or by codegen_pipeline for piped 'for'.
    if (fnode->range_expr && fnode->range_expr->type == NODE_RANGE) {
        RangeNode* range_ast_payload = &fnode->range_expr->data.range;
        start_val_llvm = codegen_expr(state, range_ast_payload->start);
        end_val_llvm = codegen_expr(state, range_ast_payload->end);
    } else {
         fprintf(stderr, "Line %d: For loop requires a valid range_expr (AST node of type NODE_RANGE).\n", parent_node->line_num);
        return NULL;
    }

    if (!start_val_llvm || !end_val_llvm) {
        fprintf(stderr, "Line %d: Could not evaluate start or end expressions for the for-loop range.\n", parent_node->line_num);
        return NULL;
    }

    LLVMValueRef current_llvm_function = state->current_function;
    LLVMBasicBlockRef func_entry_bb = LLVMGetEntryBasicBlock(current_llvm_function);
    LLVMBuilderRef TmpB = LLVMCreateBuilderInContext(state->context);
    if (LLVMGetFirstInstruction(func_entry_bb)) {
        LLVMPositionBuilder(TmpB, func_entry_bb, LLVMGetFirstInstruction(func_entry_bb));
    } else {
        LLVMPositionBuilderAtEnd(TmpB, func_entry_bb);
    }
    LLVMValueRef loop_var_alloca = LLVMBuildAlloca(TmpB, LLVMInt32TypeInContext(state->context), fnode->loop_var_name);
    LLVMDisposeBuilder(TmpB);

    SymbolTable* loop_scope = create_symbol_table(state->current_scope_symbols);
    SymbolTable* old_scope = state->current_scope_symbols;
    state->current_scope_symbols = loop_scope;
    add_symbol(state->current_scope_symbols, fnode->loop_var_name, loop_var_alloca, LLVMInt32TypeInContext(state->context), 0);
    
    LLVMBuildStore(state->builder, start_val_llvm, loop_var_alloca);

    LLVMBasicBlockRef old_continue_target = state->current_loop_cond_bb;
    LLVMBasicBlockRef old_break_target = state->current_loop_end_bb;

    LLVMBasicBlockRef loop_cond_bb = LLVMAppendBasicBlockInContext(state->context, current_llvm_function, "loop.cond");
    LLVMBasicBlockRef loop_body_bb = LLVMAppendBasicBlockInContext(state->context, current_llvm_function, "loop.body");
    LLVMBasicBlockRef loop_inc_bb = LLVMAppendBasicBlockInContext(state->context, current_llvm_function, "loop.inc");
    LLVMBasicBlockRef loop_end_bb = LLVMAppendBasicBlockInContext(state->context, current_llvm_function, "loop.end");

    state->current_loop_cond_bb = loop_inc_bb; // 'continue' target
    state->current_loop_end_bb = loop_end_bb;   // 'break' target

    LLVMBuildBr(state->builder, loop_cond_bb);

    LLVMPositionBuilderAtEnd(state->builder, loop_cond_bb);
    LLVMValueRef current_iter_val = LLVMBuildLoad2(state->builder, LLVMInt32TypeInContext(state->context), loop_var_alloca, "loopvar.val");
    LLVMValueRef condition = LLVMBuildICmp(state->builder, LLVMIntSLT, current_iter_val, end_val_llvm, "loopcond");
    LLVMBuildCondBr(state->builder, condition, loop_body_bb, loop_end_bb);

    LLVMPositionBuilderAtEnd(state->builder, loop_body_bb);
    LLVMValueRef old_piped_val_for_body = state->piped_value;
    state->piped_value = current_iter_val; // Make loop item available for piping in body

    if (fnode->body_stmts_node && fnode->body_stmts_node->type == NODE_STATEMENT_LIST) {
        codegen_statement_list_payload(state, &fnode->body_stmts_node->data.statement_list_payload);
    }
    state->piped_value = old_piped_val_for_body; // Restore
    if(LLVMGetInsertBlock(state->builder) && !LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(state->builder))) {
        LLVMBuildBr(state->builder, loop_inc_bb);
    }

    LLVMPositionBuilderAtEnd(state->builder, loop_inc_bb);
    LLVMValueRef val_before_inc = LLVMBuildLoad2(state->builder, LLVMInt32TypeInContext(state->context), loop_var_alloca, "val.beforeinc");
    LLVMValueRef next_val = LLVMBuildAdd(state->builder, val_before_inc, LLVMConstInt(LLVMInt32TypeInContext(state->context), 1, 0), "next.val");
    LLVMBuildStore(state->builder, next_val, loop_var_alloca);
    LLVMBuildBr(state->builder, loop_cond_bb);

    LLVMPositionBuilderAtEnd(state->builder, loop_end_bb);

    state->current_scope_symbols = old_scope;
    free_symbol_table(loop_scope);
    state->current_loop_cond_bb = old_continue_target;
    state->current_loop_end_bb = old_break_target;
    return NULL;
}

static LLVMValueRef codegen_return(LLVMGeneratorState* state, ReturnNode* rnode, ASTNode* parent_node) {
    if (!state->current_function) {
        fprintf(stderr, "Line %d: Return statement found outside of a function.\n", parent_node->line_num);
        return NULL;
    }
    if (rnode->value) {
        LLVMValueRef ret_val_llvm = codegen_expr(state, rnode->value);
        if (!ret_val_llvm) return NULL;
        return LLVMBuildRet(state->builder, ret_val_llvm);
    } else {
        return LLVMBuildRetVoid(state->builder);
    }
}

static LLVMValueRef codegen_print_call(LLVMGeneratorState* state, PrintCallNode* pnode, ASTNode* parent_node) {
    LLVMValueRef arg_to_print_llvm = NULL;

    if (pnode->expression) { // Case: print(expr)
        arg_to_print_llvm = codegen_expr(state, pnode->expression);
    } else if (state->piped_value) { // Case: data |> print()
        arg_to_print_llvm = state->piped_value;
    } else { // No argument provided or piped
        fprintf(stderr, "Line %d: print() called with no argument (neither explicit nor piped).\n", parent_node->line_num);
        return NULL;
    }

    if (!arg_to_print_llvm) {
        // An error would have likely been printed by codegen_expr if it failed.
        return NULL;
    }

    LLVMValueRef printf_func_val = get_printf_function(state);
    if (!printf_func_val) {
        fprintf(stderr, "Line %d: Failed to get LLVMValueRef for printf function.\n", parent_node->line_num);
        return NULL;
    }

    // Explicitly define/reconstruct printf's known signature type for LLVMBuildCall2.
    LLVMTypeRef printf_return_llvm_type = LLVMInt32TypeInContext(state->context);
    LLVMTypeRef printf_format_arg_llvm_type = LLVMPointerType(LLVMInt8TypeInContext(state->context), 0); // char*
    LLVMTypeRef printf_arg_llvm_types[] = { printf_format_arg_llvm_type };
    LLVMTypeRef printf_signature_llvm_type = LLVMFunctionType(
        printf_return_llvm_type,
        printf_arg_llvm_types, 1, 1 // 1 fixed arg, isVarArg = true
    );

    LLVMValueRef format_str_val;
    LLVMTypeKind arg_actual_llvm_type_kind = LLVMGetTypeKind(LLVMTypeOf(arg_to_print_llvm));

    if (arg_actual_llvm_type_kind == LLVMIntegerTypeKind) {
        format_str_val = LLVMBuildGlobalStringPtr(state->builder, "%d\n", ".fmt_int_ln");
    } else if (arg_actual_llvm_type_kind == LLVMFloatTypeKind || arg_actual_llvm_type_kind == LLVMDoubleTypeKind) {
        format_str_val = LLVMBuildGlobalStringPtr(state->builder, "%f\n", ".fmt_float_ln");
        if (arg_actual_llvm_type_kind == LLVMFloatTypeKind) {
            arg_to_print_llvm = LLVMBuildFPExt(state->builder, arg_to_print_llvm, LLVMDoubleTypeInContext(state->context), "fpext_for_printf");
        }
    } else if (arg_actual_llvm_type_kind == LLVMPointerTypeKind &&
               LLVMGetElementType(LLVMTypeOf(arg_to_print_llvm)) &&
               LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(arg_to_print_llvm))) == LLVMIntegerTypeKind &&
               LLVMGetIntTypeWidth(LLVMGetElementType(LLVMTypeOf(arg_to_print_llvm))) == 8) {
        format_str_val = LLVMBuildGlobalStringPtr(state->builder, "%s\n", ".fmt_str_ln");
    }
    else {
        char* type_str_for_error_msg = LLVMPrintTypeToString(LLVMTypeOf(arg_to_print_llvm));
        fprintf(stderr, "Warning Line %d: print() called with unhandled LLVM type: %s. Printing generic message.\n", parent_node->line_num, type_str_for_error_msg);
        LLVMDisposeMessage(type_str_for_error_msg);
        format_str_val = LLVMBuildGlobalStringPtr(state->builder, "Value(type_unhandled_by_print)\n", ".fmt_unknown_ln");
        LLVMValueRef call_args_for_unknown_type[] = { format_str_val };
        return LLVMBuildCall2(state->builder, printf_signature_llvm_type, printf_func_val, call_args_for_unknown_type, 1, "calltmp_printf_unknown");
    }

    LLVMValueRef call_args_for_known_type[] = { format_str_val, arg_to_print_llvm };
    return LLVMBuildCall2(state->builder, printf_signature_llvm_type, printf_func_val, call_args_for_known_type, 2, "calltmp_printf_known");
}

static LLVMValueRef codegen_expr(LLVMGeneratorState *state, ASTNode *node) {
    if (!node) return NULL;
    LLVMValueRef result = NULL;
    switch (node->type) {
        case NODE_NUMBER:         result = codegen_number(state, &node->data.number); break;
        case NODE_IDENTIFIER:     result = codegen_identifier(state, &node->data.identifier, node); break;
        case NODE_BINARY_OP:      result = codegen_binop(state, &node->data.binary_op, node); break;
        case NODE_UNARY_OP:       result = codegen_unaryop(state, &node->data.unary_op, node); break;
        case NODE_ASSIGNMENT:     result = codegen_assignment(state, &node->data.assignment, node); break;
        case NODE_FUNCTION_CALL:  result = codegen_func_call(state, &node->data.function_call, NULL, node); break;
        case NODE_PIPELINE:       result = codegen_pipeline(state, &node->data.pipeline, node); break;
        case NODE_IF_ELSE:        result = codegen_if_else(state, &node->data.if_else, node); break;
        case NODE_PRINT_CALL:     result = codegen_print_call(state, &node->data.print_call, node); break;
        case NODE_RANGE:          result = codegen_range(state, &node->data.range, node); break;
        default:
            fprintf(stderr, "Line %d: AST node type %d is not a recognized expression type.\n", node->line_num, node->type);
    }
    return result;
}

static void codegen_statement_list_payload(LLVMGeneratorState *state, StatementListPayload *payload) {
    if (!payload) return;
    for (int i = 0; i < payload->count; i++) {
        ASTNode *stmt_node = payload->statements[i];
        if (!stmt_node) continue;

        if (LLVMGetInsertBlock(state->builder) && LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(state->builder))) {
            // fprintf(stderr, "Warning: Unreachable code (statement at line %d) due to prior block termination.\n", stmt_node->line_num);
            return;
        }

        switch (stmt_node->type) {
            case NODE_FUNCTION_DEF:
                codegen_func_def(state, &stmt_node->data.function_def, stmt_node);
                break;
            case NODE_RETURN:
                codegen_return(state, &stmt_node->data.return_stmt, stmt_node);
                return; 
            case NODE_FOR_LOOP:
                codegen_for_loop(state, &stmt_node->data.for_loop, stmt_node);
                break;
            case NODE_STATEMENT_LIST:
                codegen_statement_list_payload(state, &stmt_node->data.statement_list_payload);
                break;
            default: // Expression as statement
                codegen_expr(state, stmt_node);
                break;
        }
    }
}

void llvm_generate_code(LLVMGeneratorState* state, ASTNode *root_ast_node) {
    if (!root_ast_node || root_ast_node->type != NODE_STATEMENT_LIST) {
        fprintf(stderr, "Error: AST root must be a NODE_STATEMENT_LIST for llvm_generate_code.\n");
        if(root_ast_node) fprintf(stderr, "Actual root node type: %d\n", root_ast_node->type);
        // Create a dummy main that returns 1 to indicate error if AST is bad
        LLVMTypeRef dummy_ret_type = LLVMInt32TypeInContext(state->context);
        LLVMTypeRef dummy_func_type = LLVMFunctionType(dummy_ret_type, NULL, 0, 0);
        LLVMValueRef dummy_func = LLVMAddFunction(state->module, "main_ast_error", dummy_func_type);
        LLVMBasicBlockRef dummy_entry = LLVMAppendBasicBlockInContext(state->context, dummy_func, "entry_ast_error");
        LLVMPositionBuilderAtEnd(state->builder, dummy_entry);
        LLVMBuildRet(state->builder, LLVMConstInt(dummy_ret_type, 1, 0)); // Return 1
        return;
    }

    LLVMTypeRef main_ret_type = LLVMInt32TypeInContext(state->context);
    LLVMTypeRef main_func_type = LLVMFunctionType(main_ret_type, NULL, 0, 0);
    LLVMValueRef main_func = LLVMAddFunction(state->module, "main", main_func_type);
    
    LLVMBasicBlockRef main_entry_block = LLVMAppendBasicBlockInContext(state->context, main_func, "main_script_entry");
    LLVMPositionBuilderAtEnd(state->builder, main_entry_block);

    LLVMValueRef preserved_outer_func = state->current_function;
    SymbolTable* preserved_outer_scope = state->current_scope_symbols;

    state->current_function = main_func;
    state->current_scope_symbols = create_symbol_table(state->global_symbols);

    codegen_statement_list_payload(state, &root_ast_node->data.statement_list_payload);

    if (LLVMGetInsertBlock(state->builder) && !LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(state->builder))) {
        LLVMBuildRet(state->builder, LLVMConstInt(main_ret_type, 0, 0)); // Default return 0 for success
    }
    
    state->current_function = preserved_outer_func;
    free_symbol_table(state->current_scope_symbols);
    state->current_scope_symbols = preserved_outer_scope;

    char *llvm_error_message = NULL;
    if (LLVMVerifyModule(state->module, LLVMReturnStatusAction, &llvm_error_message)) {
        fprintf(stderr, "LLVM module verification failed:\n%s\n", llvm_error_message);
        LLVMDisposeMessage(llvm_error_message);
    }
}
