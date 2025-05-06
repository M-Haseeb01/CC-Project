/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_FLOWSCRIPT_TAB_H_INCLUDED
# define YY_YY_FLOWSCRIPT_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_NUMBER = 258,                /* T_NUMBER  */
    T_IDENTIFIER = 259,            /* T_IDENTIFIER  */
    T_PRINT = 260,                 /* T_PRINT  */
    T_FUNC = 261,                  /* T_FUNC  */
    T_RETURN = 262,                /* T_RETURN  */
    T_IF = 263,                    /* T_IF  */
    T_ELSE = 264,                  /* T_ELSE  */
    T_FOR = 265,                   /* T_FOR  */
    T_EACH = 266,                  /* T_EACH  */
    T_RANGE = 267,                 /* T_RANGE  */
    T_PIPE = 268,                  /* T_PIPE  */
    T_ASSIGN = 269,                /* T_ASSIGN  */
    T_PLUS = 270,                  /* T_PLUS  */
    T_MINUS = 271,                 /* T_MINUS  */
    T_MULTIPLY = 272,              /* T_MULTIPLY  */
    T_DIVIDE = 273,                /* T_DIVIDE  */
    T_EQ = 274,                    /* T_EQ  */
    T_NEQ = 275,                   /* T_NEQ  */
    T_LT = 276,                    /* T_LT  */
    T_GT = 277,                    /* T_GT  */
    T_LTE = 278,                   /* T_LTE  */
    T_GTE = 279,                   /* T_GTE  */
    T_AND = 280,                   /* T_AND  */
    T_OR = 281,                    /* T_OR  */
    T_NOT = 282,                   /* T_NOT  */
    T_LPAREN = 283,                /* T_LPAREN  */
    T_RPAREN = 284,                /* T_RPAREN  */
    T_LBRACE = 285,                /* T_LBRACE  */
    T_RBRACE = 286,                /* T_RBRACE  */
    T_COMMA = 287,                 /* T_COMMA  */
    T_SEMICOLON = 288,             /* T_SEMICOLON  */
    T_IFX = 289                    /* T_IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "flowscript.y"

    int ival;
    char *sval;
    struct ASTNode *node; // Primary type for AST nodes
    struct {
        void **arr; // Can hold char* for params, or ASTNode* for args
        int count;
    } generic_array;
    OperatorType op_type;

#line 109 "flowscript.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_FLOWSCRIPT_TAB_H_INCLUDED  */
