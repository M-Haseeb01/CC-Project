#ifndef LLVM_GENERATOR_H
#define LLVM_GENERATOR_H

#include "ast.h"
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h> // For JIT, if you add it
#include <llvm-c/Target.h>

#include <llvm-c/Analysis.h> // For LLVMVerifyModule

// Structure to hold current LLVM context during generation
typedef struct {
    LLVMContextRef context;
    LLVMModuleRef module;
    LLVMBuilderRef builder;
    
    // Symbol table for variables (simple implementation)
    // For a real compiler, this would be more complex (scopes, types, etc.)
    LLVMValueRef current_function; // To handle 'return' statements correctly

    // For managing named values (variables, function parameters)
    // A more robust symbol table would be a hash map of scopes.
    // For simplicity, we'll use a flat list or pass around.
    // Let's try a simple symbol table for local variables within a function:
    struct SymbolTable* current_scope_symbols; 
    struct SymbolTable* global_symbols;

    LLVMValueRef piped_value; // Holds the LLVMValueRef of the LHS of a pipe |>
    char* current_loop_var_name; // For 'for each' loops
    LLVMValueRef current_loop_var_ptr; // Pointer to the loop variable's storage
    LLVMBasicBlockRef current_loop_cond_bb;
    LLVMBasicBlockRef current_loop_end_bb;

} LLVMGeneratorState;


void llvm_initialize();
void llvm_shutdown();

LLVMGeneratorState* create_llvm_generator_state();
void free_llvm_generator_state(LLVMGeneratorState* state);

// Main codegen function
void llvm_generate_code(LLVMGeneratorState* state, ASTNode *root_node);

// Helper to get or create printf
LLVMValueRef get_printf_function(LLVMGeneratorState* state);


#endif // LLVM_GENERATOR_H
