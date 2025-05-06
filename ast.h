#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declare ASTNode for use in struct definitions
struct ASTNode;

typedef enum {
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_BINARY_OP,
    NODE_ASSIGNMENT,
    // NODE_VAR_DECL, // Not explicitly used if assignments handle declaration
    NODE_FUNCTION_DEF,
    NODE_FUNCTION_CALL,
    NODE_PIPELINE,
    NODE_IF_ELSE,
    NODE_FOR_LOOP,
    NODE_RANGE,
    NODE_RETURN,
    NODE_STATEMENT_LIST, // Represents a list of statements, it's an ASTNode itself
    NODE_PRINT_CALL,
    NODE_UNARY_OP
} NodeType;

typedef enum {
    OP_PLUS, OP_MINUS, OP_MULTIPLY, OP_DIVIDE,
    OP_EQ, OP_NEQ, OP_LT, OP_GT, OP_LTE, OP_GTE,
    OP_AND, OP_OR, OP_NOT
} OperatorType;

// This is the actual payload for an ASTNode of type NODE_STATEMENT_LIST
typedef struct {
    struct ASTNode **statements; // Array of ASTNode pointers
    int count;                   // Number of statements in the array
} StatementListPayload;

typedef struct {
    int value;
} NumberNode;

typedef struct {
    char *name;
} IdentifierNode;

typedef struct {
    OperatorType op;
    struct ASTNode *left;
    struct ASTNode *right;
} BinaryOpNode;

typedef struct {
    OperatorType op;
    struct ASTNode *operand;
} UnaryOpNode;

typedef struct {
    char *var_name;
    struct ASTNode *expression;
} AssignmentNode;

typedef struct {
    char *func_name;
    char **param_names; // Array of parameter name strings
    int param_count;
    struct ASTNode *body_stmts_node; // An ASTNode of type NODE_STATEMENT_LIST
} FunctionDefNode;

typedef struct {
    char *func_name;
    struct ASTNode **args; // Array of ASTNode pointers for arguments
    int arg_count;
} FunctionCallNode;

typedef struct {
    struct ASTNode *left_expr;
    struct ASTNode *right_op; // The operation node (e.g., FunctionCallNode, IfElseNode)
} PipelineNode;

typedef struct {
    struct ASTNode *condition_expr;
    struct ASTNode *then_stmts_node;  // An ASTNode of type NODE_STATEMENT_LIST
    struct ASTNode *else_stmts_node;  // An ASTNode of type NODE_STATEMENT_LIST, can be NULL
} IfElseNode;

typedef struct {
    struct ASTNode* range_expr;      // An ASTNode, expected to be type NODE_RANGE
    char* loop_var_name;
    struct ASTNode *body_stmts_node; // An ASTNode of type NODE_STATEMENT_LIST
} ForLoopNode;

typedef struct {
    struct ASTNode* start;
    struct ASTNode* end;
} RangeNode;

typedef struct {
    struct ASTNode *value; // Expression to return, can be NULL for `return;`
} ReturnNode;

typedef struct {
    struct ASTNode *expression; // Expression to print, can be NULL for `data |> print()`
} PrintCallNode;

// The main Abstract Syntax Tree Node structure
typedef struct ASTNode {
    NodeType type;
    union {
        NumberNode number;
        IdentifierNode identifier;
        BinaryOpNode binary_op;
        UnaryOpNode unary_op;
        AssignmentNode assignment;
        FunctionDefNode function_def;
        FunctionCallNode function_call;
        PipelineNode pipeline;
        IfElseNode if_else;
        ForLoopNode for_loop;
        RangeNode range;
        ReturnNode return_stmt;
        StatementListPayload statement_list_payload; // Used when type is NODE_STATEMENT_LIST
        PrintCallNode print_call;
    } data;
    int line_num; // Line number for error reporting
} ASTNode;

// --- AST Node constructor function declarations ---
ASTNode *create_number_node(int value);
ASTNode *create_identifier_node(const char *name);
ASTNode *create_binary_op_node(OperatorType op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_op_node(OperatorType op, ASTNode *operand);
ASTNode *create_assignment_node(const char *var_name, ASTNode *expression);
ASTNode *create_function_def_node(const char *func_name, char **param_names, int param_count, ASTNode *body_stmts_node);
ASTNode *create_function_call_node(const char *func_name, ASTNode **args, int arg_count);
ASTNode *create_pipeline_node(ASTNode *left_expr, ASTNode *right_op);
ASTNode *create_if_else_node(ASTNode *condition_expr, ASTNode *then_stmts_node, ASTNode *else_stmts_node);
ASTNode *create_for_loop_node(ASTNode *range_expr, const char* loop_var_name, ASTNode *body_stmts_node);
ASTNode *create_range_node(ASTNode *start, ASTNode *end);
ASTNode *create_return_node(ASTNode *value);
ASTNode *create_statement_list_node(void); // Returns an ASTNode of type NODE_STATEMENT_LIST
ASTNode *create_print_call_node(ASTNode* expression);

// Helper function to add a statement to an ASTNode of type NODE_STATEMENT_LIST
void add_statement_to_list(ASTNode *list_node, ASTNode *statement);

// Functions for managing and debugging the AST
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int indent); // For debugging

// --- Global variable declarations (defined in ast.c or by lexer) ---
extern ASTNode *ast_root; // The root of the entire Abstract Syntax Tree
extern int yylineno;      // Current line number, managed by Flex

#endif // AST_H
