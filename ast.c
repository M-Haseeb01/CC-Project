#include "ast.h"
#include <stdarg.h>

ASTNode *ast_root = NULL;

char *dupstr(const char *s) {
    if (!s) return NULL;
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

ASTNode *create_node(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for ASTNode\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->line_num = yylineno;
    // Initialize all union members to 0/NULL to be safe
    memset(&node->data, 0, sizeof(node->data));
    return node;
}

ASTNode *create_number_node(int value) {
    ASTNode *node = create_node(NODE_NUMBER);
    node->data.number.value = value;
    return node;
}

ASTNode *create_identifier_node(const char *name) {
    ASTNode *node = create_node(NODE_IDENTIFIER);
    node->data.identifier.name = dupstr(name);
    return node;
}

ASTNode *create_binary_op_node(OperatorType op, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(NODE_BINARY_OP);
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

ASTNode *create_unary_op_node(OperatorType op, ASTNode *operand) {
    ASTNode *node = create_node(NODE_UNARY_OP);
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    return node;
}

ASTNode *create_assignment_node(const char *var_name, ASTNode *expression) {
    ASTNode *node = create_node(NODE_ASSIGNMENT);
    node->data.assignment.var_name = dupstr(var_name);
    node->data.assignment.expression = expression;
    return node;
}

ASTNode *create_function_def_node(const char *func_name, char **param_names, int param_count, ASTNode *body_stmts_node) {
    ASTNode *node = create_node(NODE_FUNCTION_DEF);
    node->data.function_def.func_name = dupstr(func_name);
    node->data.function_def.param_count = param_count;
    if (param_count > 0 && param_names) {
        node->data.function_def.param_names = (char**)malloc(param_count * sizeof(char*));
        for(int i=0; i<param_count; ++i) {
            node->data.function_def.param_names[i] = dupstr(param_names[i]);
        }
    } else {
        node->data.function_def.param_names = NULL;
    }
    node->data.function_def.body_stmts_node = body_stmts_node;
    return node;
}

ASTNode *create_function_call_node(const char *func_name, ASTNode **args, int arg_count) {
    ASTNode *node = create_node(NODE_FUNCTION_CALL);
    node->data.function_call.func_name = dupstr(func_name);
    node->data.function_call.arg_count = arg_count;
    if (arg_count > 0 && args) {
        node->data.function_call.args = (ASTNode**)malloc(arg_count * sizeof(ASTNode*));
        memcpy(node->data.function_call.args, args, arg_count * sizeof(ASTNode*));
    } else {
        node->data.function_call.args = NULL;
    }
    return node;
}

ASTNode *create_pipeline_node(ASTNode *left_expr, ASTNode *right_op) {
    ASTNode *node = create_node(NODE_PIPELINE);
    node->data.pipeline.left_expr = left_expr;
    node->data.pipeline.right_op = right_op;
    return node;
}

ASTNode *create_if_else_node(ASTNode *condition_expr, ASTNode *then_stmts_node, ASTNode *else_stmts_node) {
    ASTNode *node = create_node(NODE_IF_ELSE);
    node->data.if_else.condition_expr = condition_expr;
    node->data.if_else.then_stmts_node = then_stmts_node;
    node->data.if_else.else_stmts_node = else_stmts_node;
    return node;
}

ASTNode *create_for_loop_node(ASTNode *range_expr, const char* loop_var_name, ASTNode *body_stmts_node) {
    ASTNode *node = create_node(NODE_FOR_LOOP);
    node->data.for_loop.range_expr = range_expr;
    node->data.for_loop.loop_var_name = dupstr(loop_var_name ? loop_var_name : "_item");
    node->data.for_loop.body_stmts_node = body_stmts_node;
    return node;
}

ASTNode *create_range_node(ASTNode *start, ASTNode *end) {
    ASTNode *node = create_node(NODE_RANGE);
    node->data.range.start = start;
    node->data.range.end = end;
    return node;
}

ASTNode *create_return_node(ASTNode *value) {
    ASTNode *node = create_node(NODE_RETURN);
    node->data.return_stmt.value = value;
    return node;
}

ASTNode *create_statement_list_node(void) {
    ASTNode *node = create_node(NODE_STATEMENT_LIST);
    // Payload is already zeroed by create_node's memset if using that,
    // but explicit initialization is also fine.
    node->data.statement_list_payload.statements = NULL;
    node->data.statement_list_payload.count = 0;
    return node;
}

ASTNode *create_print_call_node(ASTNode* expression) {
    ASTNode *node = create_node(NODE_PRINT_CALL);
    node->data.print_call.expression = expression;
    return node;
}

void add_statement_to_list(ASTNode *list_node, ASTNode *statement) {
    if (!list_node || list_node->type != NODE_STATEMENT_LIST || !statement) return;
    StatementListPayload *payload = &list_node->data.statement_list_payload;
    payload->statements = (ASTNode **)realloc(payload->statements, (payload->count + 1) * sizeof(ASTNode *));
    if (!payload->statements) {
        fprintf(stderr, "Memory allocation failed for statement list payload\n");
        exit(EXIT_FAILURE);
    }
    payload->statements[payload->count++] = statement;
}

void print_ast_indent(int indent) {
    for (int i = 0; i < indent; ++i) printf("  ");
}

void print_ast(ASTNode *node, int indent) {
    if (!node) {
        print_ast_indent(indent); printf("NULL Node\n");
        return;
    }

    print_ast_indent(indent);
    switch (node->type) {
        case NODE_NUMBER: printf("NUMBER: %d (Line %d)\n", node->data.number.value, node->line_num); break;
        case NODE_IDENTIFIER: printf("IDENTIFIER: %s (Line %d)\n", node->data.identifier.name, node->line_num); break;
        case NODE_BINARY_OP:
            printf("BINARY_OP: %d (Line %d)\n", node->data.binary_op.op, node->line_num);
            print_ast(node->data.binary_op.left, indent + 1);
            print_ast(node->data.binary_op.right, indent + 1);
            break;
        case NODE_UNARY_OP:
            printf("UNARY_OP: %d (Line %d)\n", node->data.unary_op.op, node->line_num);
            print_ast(node->data.unary_op.operand, indent + 1);
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGN: %s (Line %d)\n", node->data.assignment.var_name, node->line_num);
            print_ast(node->data.assignment.expression, indent + 1);
            break;
        case NODE_FUNCTION_DEF:
            printf("FUNC_DEF: %s (Params: %d) (Line %d)\n", node->data.function_def.func_name, node->data.function_def.param_count, node->line_num);
            for(int i=0; i<node->data.function_def.param_count; ++i) {
                print_ast_indent(indent+1); printf("PARAM: %s\n", node->data.function_def.param_names[i]);
            }
            print_ast_indent(indent+1); printf("BODY:\n");
            print_ast(node->data.function_def.body_stmts_node, indent + 2);
            break;
        case NODE_FUNCTION_CALL:
            printf("FUNC_CALL: %s (Args: %d) (Line %d)\n", node->data.function_call.func_name, node->data.function_call.arg_count, node->line_num);
            for (int i = 0; i < node->data.function_call.arg_count; ++i) {
                print_ast(node->data.function_call.args[i], indent + 1);
            }
            break;
        case NODE_PIPELINE:
            printf("PIPELINE (Line %d):\n", node->line_num);
            print_ast_indent(indent+1); printf("INPUT:\n");
            print_ast(node->data.pipeline.left_expr, indent + 2);
            print_ast_indent(indent+1); printf("OPERATION:\n");
            print_ast(node->data.pipeline.right_op, indent + 2);
            break;
        case NODE_IF_ELSE:
            printf("IF (Line %d):\n", node->line_num);
            print_ast_indent(indent+1); printf("CONDITION:\n");
            print_ast(node->data.if_else.condition_expr, indent + 2);
            print_ast_indent(indent+1); printf("THEN:\n");
            print_ast(node->data.if_else.then_stmts_node, indent + 2);
            if (node->data.if_else.else_stmts_node) {
                print_ast_indent(indent+1); printf("ELSE:\n");
                print_ast(node->data.if_else.else_stmts_node, indent + 2);
            }
            break;
        case NODE_FOR_LOOP:
            printf("FOR_LOOP (var: %s) (Line %d):\n", node->data.for_loop.loop_var_name, node->line_num);
            print_ast_indent(indent+1); printf("RANGE:\n");
            print_ast(node->data.for_loop.range_expr, indent + 2);
            print_ast_indent(indent+1); printf("BODY:\n");
            print_ast(node->data.for_loop.body_stmts_node, indent + 2);
            break;
        case NODE_RANGE:
            printf("RANGE (Line %d):\n", node->line_num);
            print_ast_indent(indent+1); printf("START:\n");
            print_ast(node->data.range.start, indent + 2);
            print_ast_indent(indent+1); printf("END:\n");
            print_ast(node->data.range.end, indent + 2);
            break;
        case NODE_RETURN:
            printf("RETURN (Line %d):\n", node->line_num);
            print_ast(node->data.return_stmt.value, indent + 1);
            break;
        case NODE_STATEMENT_LIST:
            printf("STATEMENT_LIST (Count: %d) (Line %d)\n", node->data.statement_list_payload.count, node->line_num);
            for (int i = 0; i < node->data.statement_list_payload.count; ++i) {
                print_ast(node->data.statement_list_payload.statements[i], indent + 1);
            }
            break;
        case NODE_PRINT_CALL:
            printf("PRINT_CALL (Line %d):\n", node->line_num);
            print_ast(node->data.print_call.expression, indent + 1);
            break;
        default: printf("Unknown Node Type: %d (Line %d)\n", node->type, node->line_num); break;
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case NODE_IDENTIFIER: free(node->data.identifier.name); break;
        case NODE_BINARY_OP:
            free_ast(node->data.binary_op.left);
            free_ast(node->data.binary_op.right);
            break;
        case NODE_UNARY_OP:
            free_ast(node->data.unary_op.operand);
            break;
        case NODE_ASSIGNMENT:
            free(node->data.assignment.var_name);
            free_ast(node->data.assignment.expression);
            break;
        case NODE_FUNCTION_DEF:
            free(node->data.function_def.func_name);
            for(int i=0; i<node->data.function_def.param_count; ++i) {
                if (node->data.function_def.param_names[i]) free(node->data.function_def.param_names[i]);
            }
            if (node->data.function_def.param_names) free(node->data.function_def.param_names);
            free_ast(node->data.function_def.body_stmts_node);
            break;
        case NODE_FUNCTION_CALL:
            free(node->data.function_call.func_name);
            for (int i = 0; i < node->data.function_call.arg_count; ++i) {
                free_ast(node->data.function_call.args[i]);
            }
            if (node->data.function_call.args) free(node->data.function_call.args);
            break;
        case NODE_PIPELINE:
            free_ast(node->data.pipeline.left_expr);
            free_ast(node->data.pipeline.right_op);
            break;
        case NODE_IF_ELSE:
            free_ast(node->data.if_else.condition_expr);
            free_ast(node->data.if_else.then_stmts_node);
            if (node->data.if_else.else_stmts_node) free_ast(node->data.if_else.else_stmts_node);
            break;
        case NODE_FOR_LOOP:
            free_ast(node->data.for_loop.range_expr);
            free(node->data.for_loop.loop_var_name);
            free_ast(node->data.for_loop.body_stmts_node);
            break;
        case NODE_RANGE:
            free_ast(node->data.range.start);
            free_ast(node->data.range.end);
            break;
        case NODE_RETURN:
            free_ast(node->data.return_stmt.value);
            break;
        case NODE_STATEMENT_LIST:
            for (int i = 0; i < node->data.statement_list_payload.count; ++i) {
                free_ast(node->data.statement_list_payload.statements[i]);
            }
            if (node->data.statement_list_payload.statements) free(node->data.statement_list_payload.statements);
            break;
        case NODE_PRINT_CALL:
            free_ast(node->data.print_call.expression);
            break;
        case NODE_NUMBER: // No dynamic members besides the node itself
            break;
        default: break;
    }
    free(node);
}
