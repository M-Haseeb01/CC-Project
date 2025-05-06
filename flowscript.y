%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h" // Included for ASTNode, OperatorType etc.

extern int yylex(void);
extern int yylineno;
extern FILE *yyin;
extern char *yytext; // To access the token text in yyerror
void yyerror(const char *s);



%}

%union {
    int ival;
    char *sval;
    struct ASTNode *node; // Primary type for AST nodes
    struct {
        void **arr; // Can hold char* for params, or ASTNode* for args
        int count;
    } generic_array;
    OperatorType op_type;
}

%token <ival> T_NUMBER
%token <sval> T_IDENTIFIER T_PRINT // T_PRINT now carries its string value

%token T_FUNC T_RETURN T_IF T_ELSE T_FOR T_EACH T_RANGE
%token T_PIPE T_ASSIGN
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE
%token T_EQ T_NEQ T_LT T_GT T_LTE T_GTE
%token T_AND T_OR T_NOT
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_COMMA T_SEMICOLON

%type <node> program statement expression term factor primary_expression
%type <node> assignment_statement function_definition function_call pipeline_expression
%type <node> if_statement for_statement return_statement range_call print_operation // Renamed from print_statement
%type <node> piped_operation
%type <node> statement_list block // These now return ASTNode* of type NODE_STATEMENT_LIST

%type <generic_array> param_list_opt param_list non_empty_param_list
%type <generic_array> arg_list_opt arg_list non_empty_arg_list

%type <op_type> comparison_op additive_op multiplicative_op logical_and_op logical_or_op

%left T_OR
%left T_AND
%nonassoc T_EQ T_NEQ T_LT T_GT T_LTE T_GTE // Non-assoc for comparison to avoid a == b == c
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_NOT
%right T_ASSIGN
%nonassoc T_IFX
%nonassoc T_ELSE

%%

program:
    statement_list { ast_root = $1; }
    ;

statement_list:
    /* empty */ { $$ = create_statement_list_node(); }
    | statement_list statement {
        add_statement_to_list($1, $2);
        $$ = $1;
    }
    ;

statement:
    assignment_statement optional_semicolon  { $$ = $1; }
    | function_definition                    { $$ = $1; }
    | pipeline_expression optional_semicolon { $$ = $1; }
    | expression optional_semicolon          { $$ = $1; }
    | if_statement                           { $$ = $1; }
    | for_statement                          { $$ = $1; } // Standalone for (e.g. for range() each {})
    | return_statement optional_semicolon    { $$ = $1; }
    | block                                  { $$ = $1; } // A block itself is an ASTNode (NODE_STATEMENT_LIST)
    ;

optional_semicolon: /* empty */ | T_SEMICOLON ;

block:
    T_LBRACE statement_list T_RBRACE { $$ = $2; } // $2 is ASTNode* (NODE_STATEMENT_LIST)
    ;

assignment_statement:
    T_IDENTIFIER T_ASSIGN expression { $$ = create_assignment_node($1, $3); free($1); }
    ;

function_definition:
    T_FUNC T_IDENTIFIER T_LPAREN param_list_opt T_RPAREN block {
        // $4 is generic_array (char **arr), $6 is ASTNode* for block
        $$ = create_function_def_node($2, (char**)$4.arr, $4.count, $6);
        free($2); // Free func name T_IDENTIFIER
        if ($4.arr) { // Free param names array and its contents
            for(int i=0; i<$4.count; ++i) if (((char**)$4.arr)[i]) free(((char**)$4.arr)[i]);
            free($4.arr);
        }
    }
    ;

param_list_opt:
    /* empty */        { $$.arr = NULL; $$.count = 0; }
    | param_list       { $$ = $1; }
    ;

param_list:
    non_empty_param_list { $$ = $1; }
    ;

non_empty_param_list:
    T_IDENTIFIER { // $1 is char* from yylval.sval
        $$.arr = (void**)malloc(sizeof(char*));
        ((char**)$$.arr)[0] = $1; // Store char*, create_function_def_node will dup
        $$.count = 1;
    }
    | non_empty_param_list T_COMMA T_IDENTIFIER { // $1 is generic_array, $3 is char*
        $$.arr = (void**)realloc($1.arr, ($1.count + 1) * sizeof(char*));
        ((char**)$$.arr)[$1.count] = $3; // Store char*
        $$.count = $1.count + 1;
    }
    ;

expression:
    term                                   { $$ = $1; }
    | expression additive_op term          { $$ = create_binary_op_node($2, $1, $3); }
    | expression comparison_op term        { $$ = create_binary_op_node($2, $1, $3); }
    | expression logical_and_op term       { $$ = create_binary_op_node($2, $1, $3); }
    | expression logical_or_op term        { $$ = create_binary_op_node($2, $1, $3); }
    ;

term:
    factor                                 { $$ = $1; }
    | term multiplicative_op factor        { $$ = create_binary_op_node($2, $1, $3); }
    ;

factor:
    primary_expression                     { $$ = $1; }
    | T_NOT factor                         { $$ = create_unary_op_node(OP_NOT, $2); }
    | T_MINUS factor                       { $$ = create_unary_op_node(OP_MINUS, $2); }
    ;

primary_expression:
    T_NUMBER                               { $$ = create_number_node($1); }
    | T_IDENTIFIER                         { $$ = create_identifier_node($1); free($1); }
    | T_LPAREN expression T_RPAREN         { $$ = $2; }
    | function_call                        { $$ = $1; }
    | range_call                           { $$ = $1; }
    | print_operation                      { $$ = $1; } // print(expr) as a primary expression
    ;

function_call:
    T_IDENTIFIER T_LPAREN arg_list_opt T_RPAREN {
        // $3 is generic_array (ASTNode **arr)
        $$ = create_function_call_node($1, (ASTNode**)$3.arr, $3.count);
        free($1); // Free func name T_IDENTIFIER
        if ($3.arr) free($3.arr); // Free the temporary array holding ASTNode pointers
    }
    ;

arg_list_opt:
    /* empty */ { $$.arr = NULL; $$.count = 0; }
    | arg_list  { $$ = $1; }
    ;

arg_list:
    non_empty_arg_list { $$ = $1; }
    ;

non_empty_arg_list:
    expression { // $1 is ASTNode*
        $$.arr = (void**)malloc(sizeof(ASTNode*));
        ((ASTNode**)$$.arr)[0] = $1;
        $$.count = 1;
    }
    | non_empty_arg_list T_COMMA expression { // $1 is generic_array, $3 is ASTNode*
        $$.arr = (void**)realloc($1.arr, ($1.count + 1) * sizeof(ASTNode*));
        ((ASTNode**)$$.arr)[$1.count] = $3;
        $$.count = $1.count + 1;
    }
    ;

range_call:
    T_RANGE T_LPAREN expression T_COMMA expression T_RPAREN {
        $$ = create_range_node($3, $5);
    }
    ;

pipeline_expression:
    primary_expression T_PIPE piped_operation { $$ = create_pipeline_node($1, $3); }
    | pipeline_expression T_PIPE piped_operation { $$ = create_pipeline_node($1, $3); }
    ;

piped_operation:
    function_call { $$ = $1; }
    | if_statement  { $$ = $1; }
    | T_FOR T_EACH block { // The 'for each block' part of a pipeline
        // The piped input (range) is on LHS of pipeline_expression.
        // Here $3 is the block (ASTNode* of type NODE_STATEMENT_LIST)
        $$ = create_for_loop_node(NULL, "item", $3); // Range is set by pipeline node logic
    }
    | T_PRINT T_LPAREN T_RPAREN { // For `data |> print()`
        $$ = create_print_call_node(NULL); // NULL means use piped input
        // Note: T_PRINT token itself is not used here, maybe it should be.
        // If T_PRINT was an identifier, this would be a function_call.
        // To keep it distinct:
    }
    // | print_operation { $$ = $1; } // if print() is always piped like a func_call.
    ;

// For `print(expr)` as a statement or primary expression
print_operation:
    T_PRINT T_LPAREN expression T_RPAREN {
        $$ = create_print_call_node($3);
        free($1); // Free the "print" string from lexer if T_PRINT returns sval
    }
    // If T_PRINT does not return sval, no free($1) needed.
    // My lexer rule for T_PRINT now returns sval.
    ;


if_statement:
    T_IF expression block %prec T_IFX {
        $$ = create_if_else_node($2, $3, NULL);
    }
    | T_IF expression block T_ELSE block {
        $$ = create_if_else_node($2, $3, $5);
    }
    ;

// Standalone for loop (not part of pipeline)
// Example: for range(1,5) each { ... }
// This is more complex if range() is an expression evaluated first.
// Simpler: for_statement requires a range_call directly.
for_statement:
    T_FOR range_call T_EACH block {
        // $2 is range_call (ASTNode*), $4 is block (ASTNode*)
        $$ = create_for_loop_node($2, "item", $4);
    }
    ;


return_statement:
    T_RETURN expression { $$ = create_return_node($2); }
    | T_RETURN          { $$ = create_return_node(NULL); }
    ;

comparison_op: T_EQ { $$ = OP_EQ; } | T_NEQ { $$ = OP_NEQ; } | T_LT { $$ = OP_LT; } | T_GT { $$ = OP_GT; } | T_LTE { $$ = OP_LTE; } | T_GTE { $$ = OP_GTE; };
additive_op: T_PLUS { $$ = OP_PLUS; } | T_MINUS { $$ = OP_MINUS; };
multiplicative_op: T_MULTIPLY { $$ = OP_MULTIPLY; } | T_DIVIDE { $$ = OP_DIVIDE; };
logical_and_op: T_AND { $$ = OP_AND; };
logical_or_op: T_OR { $$ = OP_OR; };

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error (Line %d): %s near token '%s'\n", yylineno, s, yytext ? yytext : "<unknown>");
}
