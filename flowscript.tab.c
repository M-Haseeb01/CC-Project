/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "flowscript.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h" // Included for ASTNode, OperatorType etc.

extern int yylex(void);
extern int yylineno;
extern FILE *yyin;
extern char *yytext; // To access the token text in yyerror
void yyerror(const char *s);




#line 87 "flowscript.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "flowscript.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_NUMBER = 3,                   /* T_NUMBER  */
  YYSYMBOL_T_IDENTIFIER = 4,               /* T_IDENTIFIER  */
  YYSYMBOL_T_PRINT = 5,                    /* T_PRINT  */
  YYSYMBOL_T_FUNC = 6,                     /* T_FUNC  */
  YYSYMBOL_T_RETURN = 7,                   /* T_RETURN  */
  YYSYMBOL_T_IF = 8,                       /* T_IF  */
  YYSYMBOL_T_ELSE = 9,                     /* T_ELSE  */
  YYSYMBOL_T_FOR = 10,                     /* T_FOR  */
  YYSYMBOL_T_EACH = 11,                    /* T_EACH  */
  YYSYMBOL_T_RANGE = 12,                   /* T_RANGE  */
  YYSYMBOL_T_PIPE = 13,                    /* T_PIPE  */
  YYSYMBOL_T_ASSIGN = 14,                  /* T_ASSIGN  */
  YYSYMBOL_T_PLUS = 15,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 16,                   /* T_MINUS  */
  YYSYMBOL_T_MULTIPLY = 17,                /* T_MULTIPLY  */
  YYSYMBOL_T_DIVIDE = 18,                  /* T_DIVIDE  */
  YYSYMBOL_T_EQ = 19,                      /* T_EQ  */
  YYSYMBOL_T_NEQ = 20,                     /* T_NEQ  */
  YYSYMBOL_T_LT = 21,                      /* T_LT  */
  YYSYMBOL_T_GT = 22,                      /* T_GT  */
  YYSYMBOL_T_LTE = 23,                     /* T_LTE  */
  YYSYMBOL_T_GTE = 24,                     /* T_GTE  */
  YYSYMBOL_T_AND = 25,                     /* T_AND  */
  YYSYMBOL_T_OR = 26,                      /* T_OR  */
  YYSYMBOL_T_NOT = 27,                     /* T_NOT  */
  YYSYMBOL_T_LPAREN = 28,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 29,                  /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 30,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 31,                  /* T_RBRACE  */
  YYSYMBOL_T_COMMA = 32,                   /* T_COMMA  */
  YYSYMBOL_T_SEMICOLON = 33,               /* T_SEMICOLON  */
  YYSYMBOL_T_IFX = 34,                     /* T_IFX  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_program = 36,                   /* program  */
  YYSYMBOL_statement_list = 37,            /* statement_list  */
  YYSYMBOL_statement = 38,                 /* statement  */
  YYSYMBOL_optional_semicolon = 39,        /* optional_semicolon  */
  YYSYMBOL_block = 40,                     /* block  */
  YYSYMBOL_assignment_statement = 41,      /* assignment_statement  */
  YYSYMBOL_function_definition = 42,       /* function_definition  */
  YYSYMBOL_param_list_opt = 43,            /* param_list_opt  */
  YYSYMBOL_param_list = 44,                /* param_list  */
  YYSYMBOL_non_empty_param_list = 45,      /* non_empty_param_list  */
  YYSYMBOL_expression = 46,                /* expression  */
  YYSYMBOL_term = 47,                      /* term  */
  YYSYMBOL_factor = 48,                    /* factor  */
  YYSYMBOL_primary_expression = 49,        /* primary_expression  */
  YYSYMBOL_function_call = 50,             /* function_call  */
  YYSYMBOL_arg_list_opt = 51,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 52,                  /* arg_list  */
  YYSYMBOL_non_empty_arg_list = 53,        /* non_empty_arg_list  */
  YYSYMBOL_range_call = 54,                /* range_call  */
  YYSYMBOL_pipeline_expression = 55,       /* pipeline_expression  */
  YYSYMBOL_piped_operation = 56,           /* piped_operation  */
  YYSYMBOL_print_operation = 57,           /* print_operation  */
  YYSYMBOL_if_statement = 58,              /* if_statement  */
  YYSYMBOL_for_statement = 59,             /* for_statement  */
  YYSYMBOL_return_statement = 60,          /* return_statement  */
  YYSYMBOL_comparison_op = 61,             /* comparison_op  */
  YYSYMBOL_additive_op = 62,               /* additive_op  */
  YYSYMBOL_multiplicative_op = 63,         /* multiplicative_op  */
  YYSYMBOL_logical_and_op = 64,            /* logical_and_op  */
  YYSYMBOL_logical_or_op = 65              /* logical_or_op  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    66,    67,    74,    75,    76,    77,    78,
      79,    80,    81,    84,    84,    87,    91,    95,   107,   108,
     112,   116,   121,   129,   130,   131,   132,   133,   137,   138,
     142,   143,   144,   148,   149,   150,   151,   152,   153,   157,
     166,   167,   171,   175,   180,   188,   194,   195,   199,   200,
     201,   206,   217,   227,   230,   240,   248,   249,   252,   252,
     252,   252,   252,   252,   253,   253,   254,   254,   255,   256
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_NUMBER",
  "T_IDENTIFIER", "T_PRINT", "T_FUNC", "T_RETURN", "T_IF", "T_ELSE",
  "T_FOR", "T_EACH", "T_RANGE", "T_PIPE", "T_ASSIGN", "T_PLUS", "T_MINUS",
  "T_MULTIPLY", "T_DIVIDE", "T_EQ", "T_NEQ", "T_LT", "T_GT", "T_LTE",
  "T_GTE", "T_AND", "T_OR", "T_NOT", "T_LPAREN", "T_RPAREN", "T_LBRACE",
  "T_RBRACE", "T_COMMA", "T_SEMICOLON", "T_IFX", "$accept", "program",
  "statement_list", "statement", "optional_semicolon", "block",
  "assignment_statement", "function_definition", "param_list_opt",
  "param_list", "non_empty_param_list", "expression", "term", "factor",
  "primary_expression", "function_call", "arg_list_opt", "arg_list",
  "non_empty_arg_list", "range_call", "pipeline_expression",
  "piped_operation", "print_operation", "if_statement", "for_statement",
  "return_statement", "comparison_op", "additive_op", "multiplicative_op",
  "logical_and_op", "logical_or_op", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -37,     8,    46,   -37,   -37,     1,   -11,    15,    75,    75,
       9,     7,    75,    75,    75,   -37,   -37,   -37,    -2,   -37,
      85,    28,   -37,    27,   -37,   -37,    -6,   -37,   -37,   -37,
      -2,    75,    75,    75,    20,    29,   162,   -37,   114,    17,
      75,   -37,   -37,   126,     6,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,    75,    75,
      75,    75,   -37,   -37,    75,    34,    34,   -37,   -37,   174,
     162,    14,   -37,    31,   138,    55,    56,    36,   100,   -37,
     -37,    28,    28,    28,    28,   -37,    29,    39,    58,   -37,
     -37,   -37,   -37,   -37,    75,   -37,   -37,    42,   -37,    40,
      36,   -37,    75,    48,    36,   162,    36,    71,   -37,   150,
     -37,   -37,   -37,   -37,   -37
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    33,    34,     0,     0,    57,     0,
       0,     0,     0,     0,     0,     3,     4,    12,    13,     6,
      13,    23,    28,    30,    36,    37,    13,    38,     9,    10,
      13,     0,    40,     0,     0,    34,    56,    30,     0,     0,
       0,    32,    31,     0,     0,    14,     5,    64,    65,    58,
      59,    60,    61,    62,    63,    68,    69,     8,     0,     0,
       0,     0,    66,    67,     0,     0,     0,     7,    11,    16,
      43,     0,    41,    42,     0,    18,    53,     0,     0,    35,
      15,    25,    24,    26,    27,    29,     0,     0,     0,    48,
      46,    49,    47,    39,     0,    52,    21,     0,    19,    20,
       0,    55,     0,     0,     0,    44,     0,     0,    54,     0,
      51,    50,    17,    22,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,    70,   -37,     0,   -36,   -37,   -37,   -37,   -37,
     -37,    -8,    23,    -9,     3,    -5,   -37,   -37,   -37,    78,
     -37,    26,   -37,    24,   -37,   -37,   -37,   -37,   -37,   -37,
     -37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    16,    46,    17,    18,    19,    97,    98,
      99,    20,    21,    22,    37,    24,    71,    72,    73,    25,
      26,    90,    27,    28,    29,    30,    58,    59,    64,    60,
      61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    38,    76,    41,    42,    23,    43,    66,     3,     4,
       5,     6,     7,     8,     9,    31,    10,    33,    11,    34,
      57,    11,    12,    69,    70,    74,    67,    45,    77,    32,
      68,    45,    78,    13,    14,    40,    15,    80,    86,    87,
      65,   101,     9,    93,    88,    62,    63,    23,    75,     4,
       5,     6,     7,     8,     9,    85,    10,    32,    11,    96,
      89,    89,    12,    94,   108,   100,    15,   103,   111,   104,
     112,   106,   107,    13,    14,   113,    15,   110,     4,    35,
       6,    81,    82,    83,    84,    44,   105,    11,    39,    91,
      91,    12,    92,     0,   109,     0,     0,     0,     0,     0,
      47,    48,    13,    14,    49,    50,    51,    52,    53,    54,
      55,    56,     0,     0,     0,    47,    48,     0,    45,    49,
      50,    51,    52,    53,    54,    55,    56,     0,     0,    47,
      48,     0,   102,    49,    50,    51,    52,    53,    54,    55,
      56,    47,    48,     0,    15,    49,    50,    51,    52,    53,
      54,    55,    56,    47,    48,    79,     0,    49,    50,    51,
      52,    53,    54,    55,    56,    47,    48,    95,     0,    49,
      50,    51,    52,    53,    54,    55,    56,    47,    48,   114,
       0,    49,    50,    51,    52,    53,    54,    55,    56,    47,
       0,     0,     0,    49,    50,    51,    52,    53,    54,    55,
      56
};

static const yytype_int8 yycheck[] =
{
       8,     9,    38,    12,    13,     2,    14,    13,     0,     3,
       4,     5,     6,     7,     8,    14,    10,    28,    12,     4,
      20,    12,    16,    31,    32,    33,    26,    33,    11,    28,
      30,    33,    40,    27,    28,    28,    30,    31,     4,     5,
      13,    77,     8,    29,    10,    17,    18,    44,    28,     3,
       4,     5,     6,     7,     8,    64,    10,    28,    12,     4,
      65,    66,    16,    32,   100,     9,    30,    28,   104,    11,
     106,    29,    32,    27,    28,     4,    30,    29,     3,     4,
       5,    58,    59,    60,    61,    15,    94,    12,    10,    65,
      66,    16,    66,    -1,   102,    -1,    -1,    -1,    -1,    -1,
      15,    16,    27,    28,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    15,    16,    -1,    33,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    15,
      16,    -1,    32,    19,    20,    21,    22,    23,    24,    25,
      26,    15,    16,    -1,    30,    19,    20,    21,    22,    23,
      24,    25,    26,    15,    16,    29,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    15,    16,    29,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    15,    16,    29,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    15,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,    37,     0,     3,     4,     5,     6,     7,     8,
      10,    12,    16,    27,    28,    30,    38,    40,    41,    42,
      46,    47,    48,    49,    50,    54,    55,    57,    58,    59,
      60,    14,    28,    28,     4,     4,    46,    49,    46,    54,
      28,    48,    48,    46,    37,    33,    39,    15,    16,    19,
      20,    21,    22,    23,    24,    25,    26,    39,    61,    62,
      64,    65,    17,    18,    63,    13,    13,    39,    39,    46,
      46,    51,    52,    53,    46,    28,    40,    11,    46,    29,
      31,    47,    47,    47,    47,    48,     4,     5,    10,    50,
      56,    58,    56,    29,    32,    29,     4,    43,    44,    45,
       9,    40,    32,    28,    11,    46,    29,    32,    40,    46,
      29,    40,    40,     4,    29
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    38,    38,
      38,    38,    38,    39,    39,    40,    41,    42,    43,    43,
      44,    45,    45,    46,    46,    46,    46,    46,    47,    47,
      48,    48,    48,    49,    49,    49,    49,    49,    49,    50,
      51,    51,    52,    53,    53,    54,    55,    55,    56,    56,
      56,    56,    57,    58,    58,    59,    60,    60,    61,    61,
      61,    61,    61,    61,    62,    62,    63,    63,    64,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     2,     2,     1,
       1,     2,     1,     0,     1,     3,     3,     6,     0,     1,
       1,     1,     3,     1,     3,     3,     3,     3,     1,     3,
       1,     2,     2,     1,     1,     3,     1,     1,     1,     4,
       0,     1,     1,     1,     3,     6,     3,     3,     1,     1,
       3,     3,     4,     3,     5,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statement_list  */
#line 62 "flowscript.y"
                   { ast_root = (yyvsp[0].node); }
#line 1237 "flowscript.tab.c"
    break;

  case 3: /* statement_list: %empty  */
#line 66 "flowscript.y"
                { (yyval.node) = create_statement_list_node(); }
#line 1243 "flowscript.tab.c"
    break;

  case 4: /* statement_list: statement_list statement  */
#line 67 "flowscript.y"
                               {
        add_statement_to_list((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1252 "flowscript.tab.c"
    break;

  case 5: /* statement: assignment_statement optional_semicolon  */
#line 74 "flowscript.y"
                                             { (yyval.node) = (yyvsp[-1].node); }
#line 1258 "flowscript.tab.c"
    break;

  case 6: /* statement: function_definition  */
#line 75 "flowscript.y"
                                             { (yyval.node) = (yyvsp[0].node); }
#line 1264 "flowscript.tab.c"
    break;

  case 7: /* statement: pipeline_expression optional_semicolon  */
#line 76 "flowscript.y"
                                             { (yyval.node) = (yyvsp[-1].node); }
#line 1270 "flowscript.tab.c"
    break;

  case 8: /* statement: expression optional_semicolon  */
#line 77 "flowscript.y"
                                             { (yyval.node) = (yyvsp[-1].node); }
#line 1276 "flowscript.tab.c"
    break;

  case 9: /* statement: if_statement  */
#line 78 "flowscript.y"
                                             { (yyval.node) = (yyvsp[0].node); }
#line 1282 "flowscript.tab.c"
    break;

  case 10: /* statement: for_statement  */
#line 79 "flowscript.y"
                                             { (yyval.node) = (yyvsp[0].node); }
#line 1288 "flowscript.tab.c"
    break;

  case 11: /* statement: return_statement optional_semicolon  */
#line 80 "flowscript.y"
                                             { (yyval.node) = (yyvsp[-1].node); }
#line 1294 "flowscript.tab.c"
    break;

  case 12: /* statement: block  */
#line 81 "flowscript.y"
                                             { (yyval.node) = (yyvsp[0].node); }
#line 1300 "flowscript.tab.c"
    break;

  case 15: /* block: T_LBRACE statement_list T_RBRACE  */
#line 87 "flowscript.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 1306 "flowscript.tab.c"
    break;

  case 16: /* assignment_statement: T_IDENTIFIER T_ASSIGN expression  */
#line 91 "flowscript.y"
                                     { (yyval.node) = create_assignment_node((yyvsp[-2].sval), (yyvsp[0].node)); free((yyvsp[-2].sval)); }
#line 1312 "flowscript.tab.c"
    break;

  case 17: /* function_definition: T_FUNC T_IDENTIFIER T_LPAREN param_list_opt T_RPAREN block  */
#line 95 "flowscript.y"
                                                               {
        // $4 is generic_array (char **arr), $6 is ASTNode* for block
        (yyval.node) = create_function_def_node((yyvsp[-4].sval), (char**)(yyvsp[-2].generic_array).arr, (yyvsp[-2].generic_array).count, (yyvsp[0].node));
        free((yyvsp[-4].sval)); // Free func name T_IDENTIFIER
        if ((yyvsp[-2].generic_array).arr) { // Free param names array and its contents
            for(int i=0; i<(yyvsp[-2].generic_array).count; ++i) if (((char**)(yyvsp[-2].generic_array).arr)[i]) free(((char**)(yyvsp[-2].generic_array).arr)[i]);
            free((yyvsp[-2].generic_array).arr);
        }
    }
#line 1326 "flowscript.tab.c"
    break;

  case 18: /* param_list_opt: %empty  */
#line 107 "flowscript.y"
                       { (yyval.generic_array).arr = NULL; (yyval.generic_array).count = 0; }
#line 1332 "flowscript.tab.c"
    break;

  case 19: /* param_list_opt: param_list  */
#line 108 "flowscript.y"
                       { (yyval.generic_array) = (yyvsp[0].generic_array); }
#line 1338 "flowscript.tab.c"
    break;

  case 20: /* param_list: non_empty_param_list  */
#line 112 "flowscript.y"
                         { (yyval.generic_array) = (yyvsp[0].generic_array); }
#line 1344 "flowscript.tab.c"
    break;

  case 21: /* non_empty_param_list: T_IDENTIFIER  */
#line 116 "flowscript.y"
                 { // $1 is char* from yylval.sval
        (yyval.generic_array).arr = (void**)malloc(sizeof(char*));
        ((char**)(yyval.generic_array).arr)[0] = (yyvsp[0].sval); // Store char*, create_function_def_node will dup
        (yyval.generic_array).count = 1;
    }
#line 1354 "flowscript.tab.c"
    break;

  case 22: /* non_empty_param_list: non_empty_param_list T_COMMA T_IDENTIFIER  */
#line 121 "flowscript.y"
                                                { // $1 is generic_array, $3 is char*
        (yyval.generic_array).arr = (void**)realloc((yyvsp[-2].generic_array).arr, ((yyvsp[-2].generic_array).count + 1) * sizeof(char*));
        ((char**)(yyval.generic_array).arr)[(yyvsp[-2].generic_array).count] = (yyvsp[0].sval); // Store char*
        (yyval.generic_array).count = (yyvsp[-2].generic_array).count + 1;
    }
#line 1364 "flowscript.tab.c"
    break;

  case 23: /* expression: term  */
#line 129 "flowscript.y"
                                           { (yyval.node) = (yyvsp[0].node); }
#line 1370 "flowscript.tab.c"
    break;

  case 24: /* expression: expression additive_op term  */
#line 130 "flowscript.y"
                                           { (yyval.node) = create_binary_op_node((yyvsp[-1].op_type), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1376 "flowscript.tab.c"
    break;

  case 25: /* expression: expression comparison_op term  */
#line 131 "flowscript.y"
                                           { (yyval.node) = create_binary_op_node((yyvsp[-1].op_type), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1382 "flowscript.tab.c"
    break;

  case 26: /* expression: expression logical_and_op term  */
#line 132 "flowscript.y"
                                           { (yyval.node) = create_binary_op_node((yyvsp[-1].op_type), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1388 "flowscript.tab.c"
    break;

  case 27: /* expression: expression logical_or_op term  */
#line 133 "flowscript.y"
                                           { (yyval.node) = create_binary_op_node((yyvsp[-1].op_type), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1394 "flowscript.tab.c"
    break;

  case 28: /* term: factor  */
#line 137 "flowscript.y"
                                           { (yyval.node) = (yyvsp[0].node); }
#line 1400 "flowscript.tab.c"
    break;

  case 29: /* term: term multiplicative_op factor  */
#line 138 "flowscript.y"
                                           { (yyval.node) = create_binary_op_node((yyvsp[-1].op_type), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1406 "flowscript.tab.c"
    break;

  case 30: /* factor: primary_expression  */
#line 142 "flowscript.y"
                                           { (yyval.node) = (yyvsp[0].node); }
#line 1412 "flowscript.tab.c"
    break;

  case 31: /* factor: T_NOT factor  */
#line 143 "flowscript.y"
                                           { (yyval.node) = create_unary_op_node(OP_NOT, (yyvsp[0].node)); }
#line 1418 "flowscript.tab.c"
    break;

  case 32: /* factor: T_MINUS factor  */
#line 144 "flowscript.y"
                                           { (yyval.node) = create_unary_op_node(OP_MINUS, (yyvsp[0].node)); }
#line 1424 "flowscript.tab.c"
    break;

  case 33: /* primary_expression: T_NUMBER  */
#line 148 "flowscript.y"
                                           { (yyval.node) = create_number_node((yyvsp[0].ival)); }
#line 1430 "flowscript.tab.c"
    break;

  case 34: /* primary_expression: T_IDENTIFIER  */
#line 149 "flowscript.y"
                                           { (yyval.node) = create_identifier_node((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 1436 "flowscript.tab.c"
    break;

  case 35: /* primary_expression: T_LPAREN expression T_RPAREN  */
#line 150 "flowscript.y"
                                           { (yyval.node) = (yyvsp[-1].node); }
#line 1442 "flowscript.tab.c"
    break;

  case 36: /* primary_expression: function_call  */
#line 151 "flowscript.y"
                                           { (yyval.node) = (yyvsp[0].node); }
#line 1448 "flowscript.tab.c"
    break;

  case 37: /* primary_expression: range_call  */
#line 152 "flowscript.y"
                                           { (yyval.node) = (yyvsp[0].node); }
#line 1454 "flowscript.tab.c"
    break;

  case 38: /* primary_expression: print_operation  */
#line 153 "flowscript.y"
                                           { (yyval.node) = (yyvsp[0].node); }
#line 1460 "flowscript.tab.c"
    break;

  case 39: /* function_call: T_IDENTIFIER T_LPAREN arg_list_opt T_RPAREN  */
#line 157 "flowscript.y"
                                                {
        // $3 is generic_array (ASTNode **arr)
        (yyval.node) = create_function_call_node((yyvsp[-3].sval), (ASTNode**)(yyvsp[-1].generic_array).arr, (yyvsp[-1].generic_array).count);
        free((yyvsp[-3].sval)); // Free func name T_IDENTIFIER
        if ((yyvsp[-1].generic_array).arr) free((yyvsp[-1].generic_array).arr); // Free the temporary array holding ASTNode pointers
    }
#line 1471 "flowscript.tab.c"
    break;

  case 40: /* arg_list_opt: %empty  */
#line 166 "flowscript.y"
                { (yyval.generic_array).arr = NULL; (yyval.generic_array).count = 0; }
#line 1477 "flowscript.tab.c"
    break;

  case 41: /* arg_list_opt: arg_list  */
#line 167 "flowscript.y"
                { (yyval.generic_array) = (yyvsp[0].generic_array); }
#line 1483 "flowscript.tab.c"
    break;

  case 42: /* arg_list: non_empty_arg_list  */
#line 171 "flowscript.y"
                       { (yyval.generic_array) = (yyvsp[0].generic_array); }
#line 1489 "flowscript.tab.c"
    break;

  case 43: /* non_empty_arg_list: expression  */
#line 175 "flowscript.y"
               { // $1 is ASTNode*
        (yyval.generic_array).arr = (void**)malloc(sizeof(ASTNode*));
        ((ASTNode**)(yyval.generic_array).arr)[0] = (yyvsp[0].node);
        (yyval.generic_array).count = 1;
    }
#line 1499 "flowscript.tab.c"
    break;

  case 44: /* non_empty_arg_list: non_empty_arg_list T_COMMA expression  */
#line 180 "flowscript.y"
                                            { // $1 is generic_array, $3 is ASTNode*
        (yyval.generic_array).arr = (void**)realloc((yyvsp[-2].generic_array).arr, ((yyvsp[-2].generic_array).count + 1) * sizeof(ASTNode*));
        ((ASTNode**)(yyval.generic_array).arr)[(yyvsp[-2].generic_array).count] = (yyvsp[0].node);
        (yyval.generic_array).count = (yyvsp[-2].generic_array).count + 1;
    }
#line 1509 "flowscript.tab.c"
    break;

  case 45: /* range_call: T_RANGE T_LPAREN expression T_COMMA expression T_RPAREN  */
#line 188 "flowscript.y"
                                                            {
        (yyval.node) = create_range_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 1517 "flowscript.tab.c"
    break;

  case 46: /* pipeline_expression: primary_expression T_PIPE piped_operation  */
#line 194 "flowscript.y"
                                              { (yyval.node) = create_pipeline_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1523 "flowscript.tab.c"
    break;

  case 47: /* pipeline_expression: pipeline_expression T_PIPE piped_operation  */
#line 195 "flowscript.y"
                                                 { (yyval.node) = create_pipeline_node((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1529 "flowscript.tab.c"
    break;

  case 48: /* piped_operation: function_call  */
#line 199 "flowscript.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1535 "flowscript.tab.c"
    break;

  case 49: /* piped_operation: if_statement  */
#line 200 "flowscript.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1541 "flowscript.tab.c"
    break;

  case 50: /* piped_operation: T_FOR T_EACH block  */
#line 201 "flowscript.y"
                         { // The 'for each block' part of a pipeline
        // The piped input (range) is on LHS of pipeline_expression.
        // Here $3 is the block (ASTNode* of type NODE_STATEMENT_LIST)
        (yyval.node) = create_for_loop_node(NULL, "item", (yyvsp[0].node)); // Range is set by pipeline node logic
    }
#line 1551 "flowscript.tab.c"
    break;

  case 51: /* piped_operation: T_PRINT T_LPAREN T_RPAREN  */
#line 206 "flowscript.y"
                                { // For `data |> print()`
        (yyval.node) = create_print_call_node(NULL); // NULL means use piped input
        // Note: T_PRINT token itself is not used here, maybe it should be.
        // If T_PRINT was an identifier, this would be a function_call.
        // To keep it distinct:
    }
#line 1562 "flowscript.tab.c"
    break;

  case 52: /* print_operation: T_PRINT T_LPAREN expression T_RPAREN  */
#line 217 "flowscript.y"
                                         {
        (yyval.node) = create_print_call_node((yyvsp[-1].node));
        free((yyvsp[-3].sval)); // Free the "print" string from lexer if T_PRINT returns sval
    }
#line 1571 "flowscript.tab.c"
    break;

  case 53: /* if_statement: T_IF expression block  */
#line 227 "flowscript.y"
                                      {
        (yyval.node) = create_if_else_node((yyvsp[-1].node), (yyvsp[0].node), NULL);
    }
#line 1579 "flowscript.tab.c"
    break;

  case 54: /* if_statement: T_IF expression block T_ELSE block  */
#line 230 "flowscript.y"
                                         {
        (yyval.node) = create_if_else_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1587 "flowscript.tab.c"
    break;

  case 55: /* for_statement: T_FOR range_call T_EACH block  */
#line 240 "flowscript.y"
                                  {
        // $2 is range_call (ASTNode*), $4 is block (ASTNode*)
        (yyval.node) = create_for_loop_node((yyvsp[-2].node), "item", (yyvsp[0].node));
    }
#line 1596 "flowscript.tab.c"
    break;

  case 56: /* return_statement: T_RETURN expression  */
#line 248 "flowscript.y"
                        { (yyval.node) = create_return_node((yyvsp[0].node)); }
#line 1602 "flowscript.tab.c"
    break;

  case 57: /* return_statement: T_RETURN  */
#line 249 "flowscript.y"
                        { (yyval.node) = create_return_node(NULL); }
#line 1608 "flowscript.tab.c"
    break;

  case 58: /* comparison_op: T_EQ  */
#line 252 "flowscript.y"
                    { (yyval.op_type) = OP_EQ; }
#line 1614 "flowscript.tab.c"
    break;

  case 59: /* comparison_op: T_NEQ  */
#line 252 "flowscript.y"
                                            { (yyval.op_type) = OP_NEQ; }
#line 1620 "flowscript.tab.c"
    break;

  case 60: /* comparison_op: T_LT  */
#line 252 "flowscript.y"
                                                                    { (yyval.op_type) = OP_LT; }
#line 1626 "flowscript.tab.c"
    break;

  case 61: /* comparison_op: T_GT  */
#line 252 "flowscript.y"
                                                                                           { (yyval.op_type) = OP_GT; }
#line 1632 "flowscript.tab.c"
    break;

  case 62: /* comparison_op: T_LTE  */
#line 252 "flowscript.y"
                                                                                                                   { (yyval.op_type) = OP_LTE; }
#line 1638 "flowscript.tab.c"
    break;

  case 63: /* comparison_op: T_GTE  */
#line 252 "flowscript.y"
                                                                                                                                            { (yyval.op_type) = OP_GTE; }
#line 1644 "flowscript.tab.c"
    break;

  case 64: /* additive_op: T_PLUS  */
#line 253 "flowscript.y"
                    { (yyval.op_type) = OP_PLUS; }
#line 1650 "flowscript.tab.c"
    break;

  case 65: /* additive_op: T_MINUS  */
#line 253 "flowscript.y"
                                                { (yyval.op_type) = OP_MINUS; }
#line 1656 "flowscript.tab.c"
    break;

  case 66: /* multiplicative_op: T_MULTIPLY  */
#line 254 "flowscript.y"
                              { (yyval.op_type) = OP_MULTIPLY; }
#line 1662 "flowscript.tab.c"
    break;

  case 67: /* multiplicative_op: T_DIVIDE  */
#line 254 "flowscript.y"
                                                               { (yyval.op_type) = OP_DIVIDE; }
#line 1668 "flowscript.tab.c"
    break;

  case 68: /* logical_and_op: T_AND  */
#line 255 "flowscript.y"
                      { (yyval.op_type) = OP_AND; }
#line 1674 "flowscript.tab.c"
    break;

  case 69: /* logical_or_op: T_OR  */
#line 256 "flowscript.y"
                    { (yyval.op_type) = OP_OR; }
#line 1680 "flowscript.tab.c"
    break;


#line 1684 "flowscript.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 258 "flowscript.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parse error (Line %d): %s near token '%s'\n", yylineno, s, yytext ? yytext : "<unknown>");
}
