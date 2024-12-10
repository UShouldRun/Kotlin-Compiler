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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lib/parser/src/parser.y"

#include "arena.h"
#include "ast.h"
#include "parser.tab.h"

extern const char* filename;

// extern YYSTYPE yylval;
extern int yylineno, yyleng, current_column;
extern AST   ast;
extern Arena arena;

extern int yylex(YYSTYPE* yylval, YYLTYPE* yylloc);
void yyerror(YYLTYPE* yylloc, const char* error_msg);

#line 87 "lib/parser/build/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TT_IDENTIFIER = 3,              /* TT_IDENTIFIER  */
  YYSYMBOL_TT_VAR = 4,                     /* TT_VAR  */
  YYSYMBOL_TT_VAL = 5,                     /* TT_VAL  */
  YYSYMBOL_TT_STRING_LIT = 6,              /* TT_STRING_LIT  */
  YYSYMBOL_TT_NUMBER = 7,                  /* TT_NUMBER  */
  YYSYMBOL_TT_REAL = 8,                    /* TT_REAL  */
  YYSYMBOL_TT_TRUE = 9,                    /* TT_TRUE  */
  YYSYMBOL_TT_FALSE = 10,                  /* TT_FALSE  */
  YYSYMBOL_TT_BYTE = 11,                   /* TT_BYTE  */
  YYSYMBOL_TT_SHORT = 12,                  /* TT_SHORT  */
  YYSYMBOL_TT_INT = 13,                    /* TT_INT  */
  YYSYMBOL_TT_LONG = 14,                   /* TT_LONG  */
  YYSYMBOL_TT_FLOAT = 15,                  /* TT_FLOAT  */
  YYSYMBOL_TT_DOUBLE = 16,                 /* TT_DOUBLE  */
  YYSYMBOL_TT_BOOLEAN = 17,                /* TT_BOOLEAN  */
  YYSYMBOL_TT_CHAR = 18,                   /* TT_CHAR  */
  YYSYMBOL_TT_STRING = 19,                 /* TT_STRING  */
  YYSYMBOL_TT_ANY = 20,                    /* TT_ANY  */
  YYSYMBOL_TT_INCR = 21,                   /* TT_INCR  */
  YYSYMBOL_TT_DECR = 22,                   /* TT_DECR  */
  YYSYMBOL_TT_EQUALS_PLUS = 23,            /* TT_EQUALS_PLUS  */
  YYSYMBOL_TT_EQUALS_MINUS = 24,           /* TT_EQUALS_MINUS  */
  YYSYMBOL_TT_EQUALS_MUL = 25,             /* TT_EQUALS_MUL  */
  YYSYMBOL_TT_EQUALS_DIV = 26,             /* TT_EQUALS_DIV  */
  YYSYMBOL_TT_LPAREN = 27,                 /* TT_LPAREN  */
  YYSYMBOL_TT_RPAREN = 28,                 /* TT_RPAREN  */
  YYSYMBOL_TT_LBRACE = 29,                 /* TT_LBRACE  */
  YYSYMBOL_TT_RBRACE = 30,                 /* TT_RBRACE  */
  YYSYMBOL_TT_LPARENRECT = 31,             /* TT_LPARENRECT  */
  YYSYMBOL_TT_RPARENRECT = 32,             /* TT_RPARENRECT  */
  YYSYMBOL_TT_SEMICOLON = 33,              /* TT_SEMICOLON  */
  YYSYMBOL_TT_COLON = 34,                  /* TT_COLON  */
  YYSYMBOL_TT_COMMA = 35,                  /* TT_COMMA  */
  YYSYMBOL_TT_ASSIGN = 36,                 /* TT_ASSIGN  */
  YYSYMBOL_TT_ARROW = 37,                  /* TT_ARROW  */
  YYSYMBOL_TT_DOT = 38,                    /* TT_DOT  */
  YYSYMBOL_TT_IF = 39,                     /* TT_IF  */
  YYSYMBOL_TT_ELSE = 40,                   /* TT_ELSE  */
  YYSYMBOL_TT_ELSEIF = 41,                 /* TT_ELSEIF  */
  YYSYMBOL_TT_WHEN = 42,                   /* TT_WHEN  */
  YYSYMBOL_TT_WHILE = 43,                  /* TT_WHILE  */
  YYSYMBOL_TT_FOR = 44,                    /* TT_FOR  */
  YYSYMBOL_TT_IN = 45,                     /* TT_IN  */
  YYSYMBOL_TT_DO = 46,                     /* TT_DO  */
  YYSYMBOL_TT_FUN = 47,                    /* TT_FUN  */
  YYSYMBOL_TT_RETURN = 48,                 /* TT_RETURN  */
  YYSYMBOL_TT_NULL = 49,                   /* TT_NULL  */
  YYSYMBOL_TT_ENUM = 50,                   /* TT_ENUM  */
  YYSYMBOL_TT_EQUALS = 51,                 /* TT_EQUALS  */
  YYSYMBOL_TT_NOT_EQUALS = 52,             /* TT_NOT_EQUALS  */
  YYSYMBOL_TT_LTHAN = 53,                  /* TT_LTHAN  */
  YYSYMBOL_TT_GTHAN = 54,                  /* TT_GTHAN  */
  YYSYMBOL_TT_LEQUALS = 55,                /* TT_LEQUALS  */
  YYSYMBOL_TT_GEQUALS = 56,                /* TT_GEQUALS  */
  YYSYMBOL_TT_AND = 57,                    /* TT_AND  */
  YYSYMBOL_TT_OR = 58,                     /* TT_OR  */
  YYSYMBOL_TT_PLUS = 59,                   /* TT_PLUS  */
  YYSYMBOL_TT_MINUS = 60,                  /* TT_MINUS  */
  YYSYMBOL_TT_STAR = 61,                   /* TT_STAR  */
  YYSYMBOL_TT_SLASH = 62,                  /* TT_SLASH  */
  YYSYMBOL_TT_BANG = 63,                   /* TT_BANG  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_kotlin_input = 65,              /* kotlin_input  */
  YYSYMBOL_kotlin_program = 66,            /* kotlin_program  */
  YYSYMBOL_kotlin_enum_block = 67,         /* kotlin_enum_block  */
  YYSYMBOL_kotlin_fun_params = 68,         /* kotlin_fun_params  */
  YYSYMBOL_kotlin_parameter_list = 69,     /* kotlin_parameter_list  */
  YYSYMBOL_kotlin_return_type = 70,        /* kotlin_return_type  */
  YYSYMBOL_kotlin_return_type_list = 71,   /* kotlin_return_type_list  */
  YYSYMBOL_kotlin_type = 72,               /* kotlin_type  */
  YYSYMBOL_kotlin_type_default = 73,       /* kotlin_type_default  */
  YYSYMBOL_kotlin_stmt = 74,               /* kotlin_stmt  */
  YYSYMBOL_kotlin_stmt_var = 75,           /* kotlin_stmt_var  */
  YYSYMBOL_kotlin_while = 76,              /* kotlin_while  */
  YYSYMBOL_kotlin_do = 77,                 /* kotlin_do  */
  YYSYMBOL_kotlin_for = 78,                /* kotlin_for  */
  YYSYMBOL_kotlin_for_init = 79,           /* kotlin_for_init  */
  YYSYMBOL_kotlin_for_incr = 80,           /* kotlin_for_incr  */
  YYSYMBOL_kotlin_if = 81,                 /* kotlin_if  */
  YYSYMBOL_kotlin_elseif_else = 82,        /* kotlin_elseif_else  */
  YYSYMBOL_kotlin_when = 83,               /* kotlin_when  */
  YYSYMBOL_kotlin_when_branch = 84,        /* kotlin_when_branch  */
  YYSYMBOL_kotlin_return = 85,             /* kotlin_return  */
  YYSYMBOL_kotlin_expression = 86,         /* kotlin_expression  */
  YYSYMBOL_kotlin_token = 87,              /* kotlin_token  */
  YYSYMBOL_kotlin_number = 88,             /* kotlin_number  */
  YYSYMBOL_kotlin_identifier = 89,         /* kotlin_identifier  */
  YYSYMBOL_kotlin_fun_call = 90,           /* kotlin_fun_call  */
  YYSYMBOL_kotlin_expression_list = 91     /* kotlin_expression_list  */
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
typedef yytype_int16 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1317

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  180
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  363

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   103,   105,   107,   109,   111,   114,   116,
     118,   120,   122,   127,   129,   131,   133,   138,   140,   145,
     147,   152,   154,   156,   161,   163,   168,   181,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   210,   212,
     214,   216,   218,   220,   222,   224,   226,   228,   230,   232,
     234,   239,   241,   243,   245,   247,   249,   251,   253,   255,
     257,   259,   262,   264,   266,   268,   270,   272,   274,   276,
     278,   280,   282,   287,   289,   291,   293,   295,   297,   299,
     301,   306,   308,   310,   312,   314,   316,   321,   324,   326,
     328,   330,   332,   334,   336,   339,   341,   343,   345,   347,
     349,   351,   353,   358,   360,   362,   367,   369,   371,   373,
     375,   377,   379,   381,   383,   386,   388,   390,   392,   394,
     396,   398,   400,   402,   404,   406,   411,   413,   415,   417,
     430,   432,   434,   451,   453,   461,   463,   473,   478,   480,
     485,   487,   489,   491,   493,   495,   497,   499,   504,   506,
     511,   513,   515,   517,   520,   522,   524,   526,   528,   530,
     533,   535,   538,   541,   543,   546,   549,   552,   557,   565,
     573,   581,   589,   597,   601,   608,   619,   630,   632,   637,
     639
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TT_IDENTIFIER",
  "TT_VAR", "TT_VAL", "TT_STRING_LIT", "TT_NUMBER", "TT_REAL", "TT_TRUE",
  "TT_FALSE", "TT_BYTE", "TT_SHORT", "TT_INT", "TT_LONG", "TT_FLOAT",
  "TT_DOUBLE", "TT_BOOLEAN", "TT_CHAR", "TT_STRING", "TT_ANY", "TT_INCR",
  "TT_DECR", "TT_EQUALS_PLUS", "TT_EQUALS_MINUS", "TT_EQUALS_MUL",
  "TT_EQUALS_DIV", "TT_LPAREN", "TT_RPAREN", "TT_LBRACE", "TT_RBRACE",
  "TT_LPARENRECT", "TT_RPARENRECT", "TT_SEMICOLON", "TT_COLON", "TT_COMMA",
  "TT_ASSIGN", "TT_ARROW", "TT_DOT", "TT_IF", "TT_ELSE", "TT_ELSEIF",
  "TT_WHEN", "TT_WHILE", "TT_FOR", "TT_IN", "TT_DO", "TT_FUN", "TT_RETURN",
  "TT_NULL", "TT_ENUM", "TT_EQUALS", "TT_NOT_EQUALS", "TT_LTHAN",
  "TT_GTHAN", "TT_LEQUALS", "TT_GEQUALS", "TT_AND", "TT_OR", "TT_PLUS",
  "TT_MINUS", "TT_STAR", "TT_SLASH", "TT_BANG", "$accept", "kotlin_input",
  "kotlin_program", "kotlin_enum_block", "kotlin_fun_params",
  "kotlin_parameter_list", "kotlin_return_type", "kotlin_return_type_list",
  "kotlin_type", "kotlin_type_default", "kotlin_stmt", "kotlin_stmt_var",
  "kotlin_while", "kotlin_do", "kotlin_for", "kotlin_for_init",
  "kotlin_for_incr", "kotlin_if", "kotlin_elseif_else", "kotlin_when",
  "kotlin_when_branch", "kotlin_return", "kotlin_expression",
  "kotlin_token", "kotlin_number", "kotlin_identifier", "kotlin_fun_call",
  "kotlin_expression_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-278)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      73,    36,    36,    12,  -278,  -278,    43,    34,  -278,     6,
      27,    36,  -278,    74,    88,   780,    73,  1290,    94,   -22,
    -278,   855,    36,    36,    36,   780,   113,   116,   122,   123,
     124,   138,   125,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
     157,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  1272,     2,  -278,  -278,  -278,    73,   147,    36,
     126,   128,   127,   130,   129,   590,   590,   226,    15,    11,
    -278,  -278,  -278,  -278,  -278,   590,  -278,  -278,   590,   590,
     590,  1080,  -278,  -278,   137,  -278,   133,    73,   134,   135,
     590,   590,   590,   590,   289,   590,  -278,   142,   150,   780,
      73,  -278,   149,  -278,    36,   855,   780,   780,   780,   338,
     778,   159,   790,    36,    36,    36,   355,   153,  -278,    85,
     114,   160,   825,   -37,   -37,  -278,   590,   590,   590,   590,
     590,   590,   590,   590,   590,   590,   590,   590,   590,   516,
    -278,  -278,   780,   780,   914,   926,   956,   968,   156,   163,
     998,  -278,   855,   164,  -278,   161,  -278,   106,  -278,  -278,
    -278,   166,   170,   612,   173,   169,   172,   174,   176,  1010,
     590,   177,   178,   590,   590,   590,   590,   590,   184,   115,
    -278,  -278,    57,    57,    57,    57,    57,    57,    57,    57,
     -37,   -37,  -278,  -278,  -278,   189,  -278,  -278,   780,   780,
     780,   780,   780,   186,   780,  -278,    73,    36,   780,   590,
     640,   524,   780,   192,   668,   855,    23,    23,     9,    77,
    1040,    23,    23,  1092,  1120,  1132,  1160,  1172,   532,   196,
    -278,  -278,  -278,  -278,  -278,  -278,   780,  -278,  -278,  -278,
    -278,  1052,   582,   194,   188,   198,  1212,  -278,   780,   780,
     201,    40,    36,  -278,  -278,   210,   780,    39,   213,    23,
    -278,  -278,    23,    23,    23,    23,    23,   193,   837,   590,
    -278,   780,   214,   215,  -278,   780,   582,   216,   780,   217,
    -278,  -278,   780,    25,   590,   218,   780,  -278,   780,   780,
      67,   219,  -278,  -278,  -278,  -278,  -278,   780,   211,   872,
    -278,   780,   590,  -278,  -278,   780,   696,  -278,   724,  -278,
    -278,  1200,   855,  -278,   220,  -278,   780,   780,    68,  -278,
     780,   222,   227,   884,  -278,   524,   229,   524,   230,    25,
     212,   780,   236,  -278,   780,   780,  -278,   780,  -278,   238,
    -278,   524,  -278,   524,  -278,   590,  -278,   780,   239,  -278,
    -278,   752,  -278,  -278,  1185,  -278,   780,    42,   240,  -278,
    -278,    42,  -278
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,   176,     0,     0,     1,     0,
       0,     0,    18,     0,     0,     0,    11,     0,     0,    16,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    45,    47,    46,    48,    49,    50,
       0,     6,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     0,     0,    23,    26,    27,    12,     0,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     171,   175,   172,   168,   169,     0,   149,   170,     0,     0,
       0,   180,   167,   173,   174,   166,     0,    10,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,    25,     0,
       9,     7,     0,    14,     0,     0,    71,    72,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,     0,     0,   163,   164,   162,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     148,     5,    69,    70,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     4,    15,    19,     0,    60,    61,
      42,     0,     0,     0,     0,     0,   124,   125,     0,     0,
       0,   122,   123,     0,     0,     0,     0,     0,     0,     0,
     165,   179,   154,   155,   158,   159,   156,   157,   160,   161,
     150,   151,   152,   153,   178,     0,    58,    59,    65,    66,
      67,    68,    41,     0,    64,    24,     8,     0,    63,     0,
       0,     0,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   117,     0,     0,
     177,    54,    55,    56,    57,    40,    39,    53,     3,    13,
      52,     0,     0,     0,     0,     0,     0,    76,    78,    79,
       0,   116,     0,   113,   114,     0,   102,     0,     0,     0,
     111,   112,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    62,     0,     0,   129,   132,   131,     0,   139,     0,
      74,    75,    77,     0,     0,     0,   101,    94,     0,   100,
       0,     0,   107,   108,   109,   110,   106,    86,     0,     0,
      51,     0,     0,   128,   127,   130,     0,   138,     0,    73,
     104,   115,     0,    93,     0,    92,     0,    99,     0,    83,
      85,     0,     0,     0,   126,   147,     0,   143,     0,     0,
     116,    97,     0,    91,     0,    98,    82,    84,   137,     0,
     146,   145,   141,   142,   103,     0,    89,    96,     0,    90,
      81,     0,   144,   140,   115,    88,    95,   136,     0,    87,
     134,   135,   133
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -278,  -278,   -14,   -55,  -278,   145,  -278,   104,   -10,  -278,
     131,  -278,  -278,  -278,  -278,  -277,    91,  -278,  -273,  -278,
    -256,  -278,   379,  -278,   221,    -1,  -278,   -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     3,     4,    18,    10,    13,    53,    97,    98,    55,
      32,    33,    34,    35,    36,   117,   118,    37,   275,    38,
     245,    39,   246,    82,    83,    40,    85,    86
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       6,     7,    41,   305,   103,    58,   310,    54,    14,     5,
      19,    60,     8,    59,     5,    22,    56,   149,     5,   113,
      56,    61,    62,    63,   137,   138,     5,   252,     5,   113,
      84,    99,    23,    24,    12,   100,   114,   115,   255,     5,
      25,   120,   256,   101,   114,   115,   114,   115,   116,   181,
      26,    56,   344,    27,    28,    29,    15,    30,    19,    31,
      16,    17,   195,    11,    84,    84,    84,   119,   288,   340,
       9,   342,   289,   141,    84,   283,   284,    84,    84,    84,
       5,   252,   272,   273,   360,   352,   154,   353,   362,    84,
      84,    84,    84,    84,    84,   157,   316,   334,   114,   115,
     317,   335,    20,    14,    56,   257,   171,   172,   173,   174,
     175,   176,   165,   166,   167,    84,   135,   136,   137,   138,
       1,   177,    21,     2,    57,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,   208,
      65,     5,   209,    66,    70,    71,    72,    73,    74,    67,
      68,    56,   239,    69,    71,    87,    64,   178,   229,   108,
     106,   104,   105,   107,   139,    75,   140,   142,   143,    84,
     151,    76,    84,    84,    84,    84,    84,   155,    88,    89,
      90,    91,    92,    93,    94,   152,   170,    77,   163,   202,
     179,   203,   238,    95,   206,   210,   207,    78,    79,   211,
     121,    80,   214,   215,   218,   251,    19,   216,    84,   217,
      84,   228,   221,   222,    56,   119,   119,   230,   119,   236,
     119,   119,   248,   269,   276,   277,   297,    84,   278,     5,
     153,   282,    70,    71,    72,    73,    74,   158,   159,   160,
     286,   290,   302,   301,   320,   306,   308,   318,   345,   156,
     331,   285,   312,    75,   111,   337,   205,   338,   119,   341,
     343,   119,   119,   119,   119,   119,   347,   351,    84,   356,
     361,     0,     0,   196,   197,    77,     0,     0,     0,   102,
       0,     0,   119,    84,     0,    78,    79,     0,     0,    80,
       0,     0,     5,     0,   213,    70,    71,    72,    73,    74,
       0,    84,   330,     0,     0,     0,     0,   253,   254,     0,
     258,    56,   260,   261,     0,     0,    75,   148,     0,     0,
       0,     0,     0,     0,    84,     0,    84,     0,   119,   231,
     232,   233,   234,   235,     0,   237,     0,     0,    77,   240,
      84,   243,    84,   247,    84,   250,     0,     0,    78,    79,
     291,     0,    80,   292,   293,   294,   295,   296,     5,     0,
       0,    70,    71,    72,    73,    74,   161,   270,     0,     0,
       0,     0,     0,   274,     0,     0,     0,     0,     0,   280,
     281,     0,    75,     0,     0,     0,     0,   287,   168,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,     0,   300,     0,    77,     0,   303,   304,     0,   307,
      81,     0,     0,   309,    78,    79,     0,   313,    80,   314,
     315,     0,     0,     0,     0,     0,     0,     0,   319,     0,
       0,     0,   322,     0,     0,     0,   324,   326,     0,   328,
       0,     0,     0,     0,   109,   110,   112,   332,   333,     0,
       0,   336,     0,     0,   122,     0,     0,   123,   124,   125,
       0,     0,   346,     0,     0,   348,   349,     0,   350,   144,
     145,   146,   147,    81,   150,     0,     0,     0,   355,     0,
       0,     0,   358,     0,     0,     0,     0,   359,     0,     0,
       0,     0,     0,     0,     0,   169,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,    81,     5,
       0,     0,    70,    71,    72,    73,    74,     5,     0,     0,
      70,    71,    72,    73,    74,     5,     0,     0,    70,    71,
      72,    73,    74,    75,   194,     0,     0,     0,     0,   220,
       0,    75,   223,   224,   225,   226,   227,     0,     0,    75,
     267,     0,     0,     0,   244,    77,     0,     0,     0,     0,
       0,     0,     0,    77,     0,    78,    79,     0,     0,    80,
       0,    77,     0,    78,    79,     5,    22,    80,   241,     0,
       0,    78,    79,     5,     0,    80,    70,    71,    72,    73,
      74,     0,     0,    23,    24,     0,     0,   268,     0,     0,
       0,    25,     0,     0,     0,     5,    22,    75,     0,     0,
       0,    26,   272,   273,    27,    28,    29,     0,    30,     0,
      31,     0,     0,    23,    24,     0,     0,     0,     0,    77,
       0,    25,   212,     5,    22,     0,     0,     0,   299,    78,
      79,    26,     0,    80,    27,    28,    29,     0,    30,     0,
      31,    23,    24,   311,     0,     0,     0,     0,     0,    25,
     242,     5,    22,     0,     0,     0,     0,     0,     0,    26,
       0,   323,    27,    28,    29,     0,    30,     0,    31,    23,
      24,     0,     0,     0,     0,     0,     0,    25,   249,     5,
      22,     0,     0,     0,     0,     0,     0,    26,     0,     0,
      27,    28,    29,     0,    30,     0,    31,    23,    24,     0,
       0,     0,     0,     0,   354,    25,   325,     5,    22,     0,
       0,     0,     0,     0,     0,    26,     0,     0,    27,    28,
      29,     0,    30,     0,    31,    23,    24,     0,     0,     0,
       0,     0,     0,    25,   327,     5,    22,     0,     0,     0,
       0,     0,     0,    26,     0,     0,    27,    28,    29,     0,
      30,     0,    31,    23,    24,     0,     0,     0,     0,     0,
       0,    25,   357,     5,    22,     0,     0,     0,     0,     0,
       0,    26,     0,     0,    27,    28,    29,     0,    30,     0,
      31,    23,    24,     0,     0,     0,   162,     0,     0,    25,
       0,     0,     0,     0,     0,     0,     0,     0,   164,    26,
       0,     0,    27,    28,    29,     0,    30,     0,    31,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   180,     0,     0,     0,     0,     5,     0,
       0,     0,     0,     0,     0,   298,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     321,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   198,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   199,
       0,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,     0,     0,     0,     0,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   204,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,     0,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   259,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   271,     0,     0,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   262,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   263,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   264,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   265,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   266,     0,     0,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   329,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,     0,   279,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,     5,     0,     0,     0,     0,
       0,     0,     0,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,     5,     0,     0,     0,     0,     0,     0,
      96,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,     0,     0,     0,     0,     0,     0,    52
};

static const yytype_int16 yycheck[] =
{
       1,     2,    16,   276,    59,    27,   283,    17,     9,     3,
      11,    21,     0,    35,     3,     4,    17,    94,     3,     4,
      21,    22,    23,    24,    61,    62,     3,     4,     3,     4,
      31,    29,    21,    22,    28,    33,    21,    22,    29,     3,
      29,    30,    33,    57,    21,    22,    21,    22,    33,   126,
      39,    52,   329,    42,    43,    44,    29,    46,    59,    48,
      33,    34,   139,    29,    65,    66,    67,    68,    29,   325,
      27,   327,    33,    87,    75,    35,    36,    78,    79,    80,
       3,     4,    40,    41,   357,   341,   100,   343,   361,    90,
      91,    92,    93,    94,    95,   105,    29,    29,    21,    22,
      33,    33,    28,   104,   105,    28,    21,    22,    23,    24,
      25,    26,   113,   114,   115,   116,    59,    60,    61,    62,
      47,    36,    34,    50,    30,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,    33,
      27,     3,    36,    27,     6,     7,     8,     9,    10,    27,
      27,   152,   207,    29,     7,    30,    25,    43,    43,    30,
      33,    35,    34,    33,    27,    27,    33,    33,    33,   170,
      28,    33,   173,   174,   175,   176,   177,    28,    21,    22,
      23,    24,    25,    26,    27,    35,    33,    49,    29,    33,
      30,    28,   206,    36,    30,    29,    35,    59,    60,    29,
      69,    63,    29,    34,    28,   215,   207,    35,   209,    35,
     211,    27,    35,    35,   215,   216,   217,    28,   219,    33,
     221,   222,    30,    27,    30,    37,    33,   228,    30,     3,
      99,    30,     6,     7,     8,     9,    10,   106,   107,   108,
      30,    28,    27,    29,    33,    29,    29,    28,    36,   104,
      30,   252,    34,    27,    28,    33,   152,    30,   259,    30,
      30,   262,   263,   264,   265,   266,    30,    29,   269,    30,
      30,    -1,    -1,   142,   143,    49,    -1,    -1,    -1,    58,
      -1,    -1,   283,   284,    -1,    59,    60,    -1,    -1,    63,
      -1,    -1,     3,    -1,   163,     6,     7,     8,     9,    10,
      -1,   302,   312,    -1,    -1,    -1,    -1,   216,   217,    -1,
     219,   312,   221,   222,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,   325,    -1,   327,    -1,   329,   198,
     199,   200,   201,   202,    -1,   204,    -1,    -1,    49,   208,
     341,   210,   343,   212,   345,   214,    -1,    -1,    59,    60,
     259,    -1,    63,   262,   263,   264,   265,   266,     3,    -1,
      -1,     6,     7,     8,     9,    10,    28,   236,    -1,    -1,
      -1,    -1,    -1,   242,    -1,    -1,    -1,    -1,    -1,   248,
     249,    -1,    27,    -1,    -1,    -1,    -1,   256,    33,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,   271,    -1,    49,    -1,   275,   276,    -1,   278,
      31,    -1,    -1,   282,    59,    60,    -1,   286,    63,   288,
     289,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   297,    -1,
      -1,    -1,   301,    -1,    -1,    -1,   305,   306,    -1,   308,
      -1,    -1,    -1,    -1,    65,    66,    67,   316,   317,    -1,
      -1,   320,    -1,    -1,    75,    -1,    -1,    78,    79,    80,
      -1,    -1,   331,    -1,    -1,   334,   335,    -1,   337,    90,
      91,    92,    93,    94,    95,    -1,    -1,    -1,   347,    -1,
      -1,    -1,   351,    -1,    -1,    -1,    -1,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,     3,
      -1,    -1,     6,     7,     8,     9,    10,     3,    -1,    -1,
       6,     7,     8,     9,    10,     3,    -1,    -1,     6,     7,
       8,     9,    10,    27,    28,    -1,    -1,    -1,    -1,   170,
      -1,    27,   173,   174,   175,   176,   177,    -1,    -1,    27,
      28,    -1,    -1,    -1,    40,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    59,    60,    -1,    -1,    63,
      -1,    49,    -1,    59,    60,     3,     4,    63,   209,    -1,
      -1,    59,    60,     3,    -1,    63,     6,     7,     8,     9,
      10,    -1,    -1,    21,    22,    -1,    -1,   228,    -1,    -1,
      -1,    29,    -1,    -1,    -1,     3,     4,    27,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    44,    -1,    46,    -1,
      48,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    49,
      -1,    29,    30,     3,     4,    -1,    -1,    -1,   269,    59,
      60,    39,    -1,    63,    42,    43,    44,    -1,    46,    -1,
      48,    21,    22,   284,    -1,    -1,    -1,    -1,    -1,    29,
      30,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,   302,    42,    43,    44,    -1,    46,    -1,    48,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,     3,
       4,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      42,    43,    44,    -1,    46,    -1,    48,    21,    22,    -1,
      -1,    -1,    -1,    -1,   345,    29,    30,     3,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    43,
      44,    -1,    46,    -1,    48,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,     3,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    42,    43,    44,    -1,
      46,    -1,    48,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,     3,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    42,    43,    44,    -1,    46,    -1,
      48,    21,    22,    -1,    -1,    -1,    28,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    39,
      -1,    -1,    42,    43,    44,    -1,    46,    -1,    48,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    28,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    35,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    37,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,    50,    65,    66,     3,    89,    89,     0,    27,
      68,    29,    28,    69,    89,    29,    33,    34,    67,    89,
      28,    34,     4,    21,    22,    29,    39,    42,    43,    44,
      46,    48,    74,    75,    76,    77,    78,    81,    83,    85,
      89,    66,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    27,    70,    72,    73,    89,    30,    27,    35,
      72,    89,    89,    89,    74,    27,    27,    27,    27,    29,
       6,     7,     8,     9,    10,    27,    33,    49,    59,    60,
      63,    86,    87,    88,    89,    90,    91,    30,    21,    22,
      23,    24,    25,    26,    27,    36,    28,    71,    72,    29,
      33,    66,    88,    67,    35,    34,    33,    33,    30,    86,
      86,    28,    86,     4,    21,    22,    33,    79,    80,    89,
      30,    74,    86,    86,    86,    86,    35,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    27,
      33,    66,    33,    33,    86,    86,    86,    86,    28,    91,
      86,    28,    35,    74,    66,    28,    69,    72,    74,    74,
      74,    28,    28,    29,    28,    89,    89,    89,    33,    86,
      33,    21,    22,    23,    24,    25,    26,    36,    43,    30,
      28,    91,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    28,    91,    74,    74,    33,    33,
      33,    33,    33,    28,    33,    71,    30,    35,    33,    36,
      29,    29,    30,    74,    29,    34,    35,    35,    28,    33,
      86,    35,    35,    86,    86,    86,    86,    86,    27,    43,
      28,    74,    74,    74,    74,    74,    33,    74,    66,    67,
      74,    86,    30,    74,    40,    84,    86,    74,    30,    30,
      74,    72,     4,    80,    80,    29,    33,    28,    80,    33,
      80,    80,    35,    35,    35,    35,    35,    28,    86,    27,
      74,    33,    40,    41,    74,    82,    30,    37,    30,    37,
      74,    74,    30,    35,    36,    89,    30,    74,    29,    33,
      28,    80,    80,    80,    80,    80,    80,    33,    28,    86,
      74,    29,    27,    74,    74,    82,    29,    74,    29,    74,
      79,    86,    34,    74,    74,    74,    29,    33,    28,    74,
      33,    28,    74,    86,    74,    30,    74,    30,    74,    35,
      72,    30,    74,    74,    29,    33,    74,    33,    30,    28,
      84,    30,    84,    30,    79,    36,    74,    30,    74,    74,
      74,    29,    84,    84,    86,    74,    30,    30,    74,    74,
      82,    30,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    67,    67,    67,    67,    68,    68,    69,
      69,    70,    70,    70,    71,    71,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    82,    82,    82,    83,    83,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    88,    89,    90,    90,    91,
      91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     9,     7,     7,     5,     6,     8,     6,
       6,     4,     5,     6,     3,     4,     1,     3,     2,     5,
       3,     3,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     6,     5,
       5,     4,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     8,     6,     5,     5,     5,     5,     5,     4,     4,
       4,     4,     7,     5,     4,     4,     4,     4,     4,     3,
       3,     3,     3,     8,     7,     7,     6,     7,     6,     6,
       5,    10,     9,     8,     9,     8,     7,    12,    11,    10,
      10,     9,     8,     8,     7,    11,    10,     9,     9,     8,
       7,     7,     6,     8,     6,     1,     5,     5,     5,     5,
       5,     4,     4,     4,     4,     6,     4,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     9,     8,     8,     7,
       8,     7,     7,     8,     7,     7,     6,     4,     8,     7,
       6,     5,     5,     4,     6,     5,     5,     4,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       1
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
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* kotlin_input: kotlin_program  */
#line 99 "lib/parser/src/parser.y"
    { ast = ast_create(arena, filename, (yyvsp[0].obj)); }
#line 1998 "lib/parser/build/parser.tab.c"
    break;

  case 3: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_LBRACE kotlin_stmt TT_RBRACE kotlin_program  */
#line 104 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-7].token), (yyvsp[-6].fun_args), (yyvsp[-4].fun_ret), (yyvsp[-2].stmt), (yyvsp[0].obj)); }
#line 2004 "lib/parser/build/parser.tab.c"
    break;

  case 4: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_SEMICOLON kotlin_program  */
#line 106 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-5].token), (yyvsp[-4].fun_args), (yyvsp[-2].fun_ret), NULL, (yyvsp[0].obj)); }
#line 2010 "lib/parser/build/parser.tab.c"
    break;

  case 5: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_LBRACE kotlin_stmt TT_RBRACE kotlin_program  */
#line 108 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-5].token), (yyvsp[-4].fun_args), NULL, (yyvsp[-2].stmt), (yyvsp[0].obj)); }
#line 2016 "lib/parser/build/parser.tab.c"
    break;

  case 6: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_SEMICOLON kotlin_program  */
#line 110 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-3].token), (yyvsp[-2].fun_args), NULL, NULL, (yyvsp[0].obj)); }
#line 2022 "lib/parser/build/parser.tab.c"
    break;

  case 7: /* kotlin_program: TT_ENUM kotlin_identifier TT_LBRACE kotlin_enum_block TT_RBRACE kotlin_program  */
#line 112 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_enum(arena, (yyvsp[-4].token), (yyvsp[-2].enum_values), (yyvsp[0].obj)); }
#line 2028 "lib/parser/build/parser.tab.c"
    break;

  case 8: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 115 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-6].token), (yyvsp[-5].fun_args), (yyvsp[-3].fun_ret), (yyvsp[-1].stmt), NULL); }
#line 2034 "lib/parser/build/parser.tab.c"
    break;

  case 9: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_SEMICOLON  */
#line 117 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-4].token), (yyvsp[-3].fun_args), (yyvsp[-1].fun_ret), NULL, NULL); }
#line 2040 "lib/parser/build/parser.tab.c"
    break;

  case 10: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 119 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-4].token), (yyvsp[-3].fun_args), NULL, (yyvsp[-1].stmt), NULL); }
#line 2046 "lib/parser/build/parser.tab.c"
    break;

  case 11: /* kotlin_program: TT_FUN kotlin_identifier kotlin_fun_params TT_SEMICOLON  */
#line 121 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_fun(arena, (yyvsp[-2].token), (yyvsp[-1].fun_args), NULL, NULL, NULL); }
#line 2052 "lib/parser/build/parser.tab.c"
    break;

  case 12: /* kotlin_program: TT_ENUM kotlin_identifier TT_LBRACE kotlin_enum_block TT_RBRACE  */
#line 123 "lib/parser/src/parser.y"
    { (yyval.obj) = astn_create_enum(arena, (yyvsp[-3].token), (yyvsp[-1].enum_values), NULL); }
#line 2058 "lib/parser/build/parser.tab.c"
    break;

  case 13: /* kotlin_enum_block: kotlin_identifier TT_LPAREN kotlin_number TT_RPAREN TT_COMMA kotlin_enum_block  */
#line 128 "lib/parser/src/parser.y"
    { (yyval.enum_values) = astn_create_enum_val(arena, (yyvsp[-5].token), (yyvsp[-3].token), true, (yyvsp[0].enum_values)); }
#line 2064 "lib/parser/build/parser.tab.c"
    break;

  case 14: /* kotlin_enum_block: kotlin_identifier TT_COMMA kotlin_enum_block  */
#line 130 "lib/parser/src/parser.y"
    { (yyval.enum_values) = astn_create_enum_val(arena, (yyvsp[-2].token), 0, false, (yyvsp[0].enum_values)); }
#line 2070 "lib/parser/build/parser.tab.c"
    break;

  case 15: /* kotlin_enum_block: kotlin_identifier TT_LPAREN kotlin_number TT_RPAREN  */
#line 132 "lib/parser/src/parser.y"
    { (yyval.enum_values) = astn_create_enum_val(arena, (yyvsp[-3].token), (yyvsp[-1].token), true, NULL); }
#line 2076 "lib/parser/build/parser.tab.c"
    break;

  case 16: /* kotlin_enum_block: kotlin_identifier  */
#line 134 "lib/parser/src/parser.y"
    { (yyval.enum_values) = astn_create_enum_val(arena, (yyvsp[0].token), 0, false, NULL); }
#line 2082 "lib/parser/build/parser.tab.c"
    break;

  case 17: /* kotlin_fun_params: TT_LPAREN kotlin_parameter_list TT_RPAREN  */
#line 139 "lib/parser/src/parser.y"
    { (yyval.fun_args) = (yyvsp[-1].fun_args); }
#line 2088 "lib/parser/build/parser.tab.c"
    break;

  case 18: /* kotlin_fun_params: TT_LPAREN TT_RPAREN  */
#line 141 "lib/parser/src/parser.y"
    { (yyval.fun_args) = NULL; }
#line 2094 "lib/parser/build/parser.tab.c"
    break;

  case 19: /* kotlin_parameter_list: kotlin_identifier TT_COLON kotlin_type TT_COMMA kotlin_parameter_list  */
#line 146 "lib/parser/src/parser.y"
    { (yyval.fun_args) = astn_create_fun_args(arena, (yyvsp[-2].ktype), (yyvsp[-4].token), (yyvsp[0].fun_args)); }
#line 2100 "lib/parser/build/parser.tab.c"
    break;

  case 20: /* kotlin_parameter_list: kotlin_identifier TT_COLON kotlin_type  */
#line 148 "lib/parser/src/parser.y"
    { (yyval.fun_args) = astn_create_fun_args(arena, (yyvsp[0].ktype), (yyvsp[-2].token), NULL); }
#line 2106 "lib/parser/build/parser.tab.c"
    break;

  case 21: /* kotlin_return_type: TT_LPAREN kotlin_return_type_list TT_RPAREN  */
#line 153 "lib/parser/src/parser.y"
    { (yyval.fun_ret) = (yyvsp[-1].fun_ret); }
#line 2112 "lib/parser/build/parser.tab.c"
    break;

  case 22: /* kotlin_return_type: TT_LPAREN TT_RPAREN  */
#line 155 "lib/parser/src/parser.y"
    { (yyval.fun_ret) = NULL; }
#line 2118 "lib/parser/build/parser.tab.c"
    break;

  case 23: /* kotlin_return_type: kotlin_type  */
#line 157 "lib/parser/src/parser.y"
    { (yyval.fun_ret) = astn_create_fun_ret(arena, (yyvsp[0].ktype), NULL); }
#line 2124 "lib/parser/build/parser.tab.c"
    break;

  case 24: /* kotlin_return_type_list: kotlin_type TT_COMMA kotlin_return_type_list  */
#line 162 "lib/parser/src/parser.y"
    { (yyval.fun_ret) = astn_create_fun_ret(arena, (yyvsp[-2].ktype), (yyvsp[0].fun_ret)); }
#line 2130 "lib/parser/build/parser.tab.c"
    break;

  case 25: /* kotlin_return_type_list: kotlin_type  */
#line 164 "lib/parser/src/parser.y"
    { (yyval.fun_ret) = astn_create_fun_ret(arena, (yyvsp[0].ktype), NULL); }
#line 2136 "lib/parser/build/parser.tab.c"
    break;

  case 26: /* kotlin_type: kotlin_type_default  */
#line 169 "lib/parser/src/parser.y"
    {
      (yyval.ktype) = astn_create_ktype(
        arena,
        true,
        (yyvsp[0].ktype_default),
        NULL,
        (yylsp[0]).first_line,
        (yylsp[0]).last_line,
        (yylsp[0]).first_column,
        (yylsp[0]).last_column
      );
    }
#line 2153 "lib/parser/build/parser.tab.c"
    break;

  case 27: /* kotlin_type: kotlin_identifier  */
#line 182 "lib/parser/src/parser.y"
    {
      (yyval.ktype) = astn_create_ktype(
        arena,
        false,
        KOTLIN_NOT_DEFAULT,
        (yyvsp[0].token),
        (yylsp[0]).first_line,
        (yylsp[0]).last_line,
        (yylsp[0]).first_column,
        (yylsp[0]).last_column
      );
    }
#line 2170 "lib/parser/build/parser.tab.c"
    break;

  case 28: /* kotlin_type_default: TT_BYTE  */
#line 197 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_BYTE; }
#line 2176 "lib/parser/build/parser.tab.c"
    break;

  case 29: /* kotlin_type_default: TT_SHORT  */
#line 198 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_SHORT; }
#line 2182 "lib/parser/build/parser.tab.c"
    break;

  case 30: /* kotlin_type_default: TT_INT  */
#line 199 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_INT; }
#line 2188 "lib/parser/build/parser.tab.c"
    break;

  case 31: /* kotlin_type_default: TT_LONG  */
#line 200 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_LONG; }
#line 2194 "lib/parser/build/parser.tab.c"
    break;

  case 32: /* kotlin_type_default: TT_FLOAT  */
#line 201 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_FLOAT; }
#line 2200 "lib/parser/build/parser.tab.c"
    break;

  case 33: /* kotlin_type_default: TT_DOUBLE  */
#line 202 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_DOUBLE; }
#line 2206 "lib/parser/build/parser.tab.c"
    break;

  case 34: /* kotlin_type_default: TT_BOOLEAN  */
#line 203 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_BOOLEAN; }
#line 2212 "lib/parser/build/parser.tab.c"
    break;

  case 35: /* kotlin_type_default: TT_CHAR  */
#line 204 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_CHAR; }
#line 2218 "lib/parser/build/parser.tab.c"
    break;

  case 36: /* kotlin_type_default: TT_STRING  */
#line 205 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_STRING; }
#line 2224 "lib/parser/build/parser.tab.c"
    break;

  case 37: /* kotlin_type_default: TT_ANY  */
#line 206 "lib/parser/src/parser.y"
                { (yyval.ktype_default) = KOTLIN_ANY; }
#line 2230 "lib/parser/build/parser.tab.c"
    break;

  case 38: /* kotlin_stmt: kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 211 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_fcall(arena, (yyvsp[-5].token), (yyvsp[-3].expr_list), (yyvsp[0].stmt)); }
#line 2236 "lib/parser/build/parser.tab.c"
    break;

  case 39: /* kotlin_stmt: kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN TT_SEMICOLON  */
#line 213 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_fcall(arena, (yyvsp[-4].token), (yyvsp[-2].expr_list), NULL); }
#line 2242 "lib/parser/build/parser.tab.c"
    break;

  case 40: /* kotlin_stmt: kotlin_identifier TT_LPAREN TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 215 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_fcall(arena, (yyvsp[-4].token), NULL, (yyvsp[0].stmt)); }
#line 2248 "lib/parser/build/parser.tab.c"
    break;

  case 41: /* kotlin_stmt: kotlin_identifier TT_LPAREN TT_RPAREN TT_SEMICOLON  */
#line 217 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_fcall(arena, (yyvsp[-3].token), NULL, NULL); }
#line 2254 "lib/parser/build/parser.tab.c"
    break;

  case 42: /* kotlin_stmt: TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt  */
#line 219 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_block(arena, (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2260 "lib/parser/build/parser.tab.c"
    break;

  case 43: /* kotlin_stmt: TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 221 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_block(arena, (yyvsp[-1].stmt), NULL); }
#line 2266 "lib/parser/build/parser.tab.c"
    break;

  case 44: /* kotlin_stmt: kotlin_stmt_var  */
#line 223 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2272 "lib/parser/build/parser.tab.c"
    break;

  case 45: /* kotlin_stmt: kotlin_while  */
#line 225 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2278 "lib/parser/build/parser.tab.c"
    break;

  case 46: /* kotlin_stmt: kotlin_for  */
#line 227 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2284 "lib/parser/build/parser.tab.c"
    break;

  case 47: /* kotlin_stmt: kotlin_do  */
#line 229 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2290 "lib/parser/build/parser.tab.c"
    break;

  case 48: /* kotlin_stmt: kotlin_if  */
#line 231 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2296 "lib/parser/build/parser.tab.c"
    break;

  case 49: /* kotlin_stmt: kotlin_when  */
#line 233 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2302 "lib/parser/build/parser.tab.c"
    break;

  case 50: /* kotlin_stmt: kotlin_return  */
#line 235 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2308 "lib/parser/build/parser.tab.c"
    break;

  case 51: /* kotlin_stmt_var: TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_SEMICOLON kotlin_stmt  */
#line 240 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, (yyvsp[-6].token), (yyvsp[-4].ktype), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2314 "lib/parser/build/parser.tab.c"
    break;

  case 52: /* kotlin_stmt_var: TT_VAR kotlin_identifier TT_COLON kotlin_type TT_SEMICOLON kotlin_stmt  */
#line 242 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL, (yyvsp[-4].token), (yyvsp[-2].ktype), NULL, (yyvsp[0].stmt)); }
#line 2320 "lib/parser/build/parser.tab.c"
    break;

  case 53: /* kotlin_stmt_var: kotlin_identifier TT_ASSIGN kotlin_expression TT_SEMICOLON kotlin_stmt  */
#line 244 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2326 "lib/parser/build/parser.tab.c"
    break;

  case 54: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_PLUS kotlin_expression TT_SEMICOLON kotlin_stmt  */
#line 246 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2332 "lib/parser/build/parser.tab.c"
    break;

  case 55: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_MINUS kotlin_expression TT_SEMICOLON kotlin_stmt  */
#line 248 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2338 "lib/parser/build/parser.tab.c"
    break;

  case 56: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_MUL kotlin_expression TT_SEMICOLON kotlin_stmt  */
#line 250 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2344 "lib/parser/build/parser.tab.c"
    break;

  case 57: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_DIV kotlin_expression TT_SEMICOLON kotlin_stmt  */
#line 252 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2350 "lib/parser/build/parser.tab.c"
    break;

  case 58: /* kotlin_stmt_var: kotlin_identifier TT_INCR TT_SEMICOLON kotlin_stmt  */
#line 254 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, (yyvsp[-3].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2356 "lib/parser/build/parser.tab.c"
    break;

  case 59: /* kotlin_stmt_var: kotlin_identifier TT_DECR TT_SEMICOLON kotlin_stmt  */
#line 256 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, (yyvsp[-3].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2362 "lib/parser/build/parser.tab.c"
    break;

  case 60: /* kotlin_stmt_var: TT_INCR kotlin_identifier TT_SEMICOLON kotlin_stmt  */
#line 258 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, (yyvsp[-2].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2368 "lib/parser/build/parser.tab.c"
    break;

  case 61: /* kotlin_stmt_var: TT_DECR kotlin_identifier TT_SEMICOLON kotlin_stmt  */
#line 260 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, (yyvsp[-2].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2374 "lib/parser/build/parser.tab.c"
    break;

  case 62: /* kotlin_stmt_var: TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_SEMICOLON  */
#line 263 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, (yyvsp[-5].token), (yyvsp[-3].ktype), (yyvsp[-1].expr), NULL); }
#line 2380 "lib/parser/build/parser.tab.c"
    break;

  case 63: /* kotlin_stmt_var: TT_VAR kotlin_identifier TT_COLON kotlin_type TT_SEMICOLON  */
#line 265 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL, (yyvsp[-3].token), (yyvsp[-1].ktype), NULL, NULL); }
#line 2386 "lib/parser/build/parser.tab.c"
    break;

  case 64: /* kotlin_stmt_var: kotlin_identifier TT_ASSIGN kotlin_expression TT_SEMICOLON  */
#line 267 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, (yyvsp[-3].token), KOTLIN_DECL, (yyvsp[-1].expr), NULL); }
#line 2392 "lib/parser/build/parser.tab.c"
    break;

  case 65: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_PLUS kotlin_expression TT_SEMICOLON  */
#line 269 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, (yyvsp[-3].token), KOTLIN_DECL, (yyvsp[-1].expr), NULL); }
#line 2398 "lib/parser/build/parser.tab.c"
    break;

  case 66: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_MINUS kotlin_expression TT_SEMICOLON  */
#line 271 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, (yyvsp[-3].token), KOTLIN_DECL, (yyvsp[-1].expr), NULL); }
#line 2404 "lib/parser/build/parser.tab.c"
    break;

  case 67: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_MUL kotlin_expression TT_SEMICOLON  */
#line 273 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, (yyvsp[-3].token), KOTLIN_DECL, (yyvsp[-1].expr), NULL); }
#line 2410 "lib/parser/build/parser.tab.c"
    break;

  case 68: /* kotlin_stmt_var: kotlin_identifier TT_EQUALS_DIV kotlin_expression TT_SEMICOLON  */
#line 275 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, (yyvsp[-3].token), KOTLIN_DECL, (yyvsp[-1].expr), NULL); }
#line 2416 "lib/parser/build/parser.tab.c"
    break;

  case 69: /* kotlin_stmt_var: kotlin_identifier TT_INCR TT_SEMICOLON  */
#line 277 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, (yyvsp[-2].token), KOTLIN_DECL, NULL, NULL); }
#line 2422 "lib/parser/build/parser.tab.c"
    break;

  case 70: /* kotlin_stmt_var: kotlin_identifier TT_DECR TT_SEMICOLON  */
#line 279 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, (yyvsp[-2].token), KOTLIN_DECL, NULL, NULL); }
#line 2428 "lib/parser/build/parser.tab.c"
    break;

  case 71: /* kotlin_stmt_var: TT_INCR kotlin_identifier TT_SEMICOLON  */
#line 281 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, (yyvsp[-1].token), KOTLIN_DECL, NULL, NULL); }
#line 2434 "lib/parser/build/parser.tab.c"
    break;

  case 72: /* kotlin_stmt_var: TT_DECR kotlin_identifier TT_SEMICOLON  */
#line 283 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, (yyvsp[-1].token), KOTLIN_DECL, NULL, NULL); }
#line 2440 "lib/parser/build/parser.tab.c"
    break;

  case 73: /* kotlin_while: TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt  */
#line 288 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_while(arena, false, (yyvsp[-5].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2446 "lib/parser/build/parser.tab.c"
    break;

  case 74: /* kotlin_while: TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt  */
#line 290 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_while(arena, false, NULL, (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2452 "lib/parser/build/parser.tab.c"
    break;

  case 75: /* kotlin_while: TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt  */
#line 292 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2458 "lib/parser/build/parser.tab.c"
    break;

  case 76: /* kotlin_while: TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt  */
#line 294 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2464 "lib/parser/build/parser.tab.c"
    break;

  case 77: /* kotlin_while: TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 296 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_while(arena, false, (yyvsp[-4].expr), (yyvsp[-1].stmt), NULL); }
#line 2470 "lib/parser/build/parser.tab.c"
    break;

  case 78: /* kotlin_while: TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 298 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_while(arena, false, NULL, (yyvsp[-1].stmt), NULL); }
#line 2476 "lib/parser/build/parser.tab.c"
    break;

  case 79: /* kotlin_while: TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE  */
#line 300 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2482 "lib/parser/build/parser.tab.c"
    break;

  case 80: /* kotlin_while: TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE  */
#line 302 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2488 "lib/parser/build/parser.tab.c"
    break;

  case 81: /* kotlin_do: TT_DO TT_LBRACE kotlin_stmt TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 307 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_while(arena, true, (yyvsp[-3].expr), (yyvsp[-7].stmt), (yyvsp[0].stmt)); }
#line 2494 "lib/parser/build/parser.tab.c"
    break;

  case 82: /* kotlin_do: TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 309 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2500 "lib/parser/build/parser.tab.c"
    break;

  case 83: /* kotlin_do: TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 311 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2506 "lib/parser/build/parser.tab.c"
    break;

  case 84: /* kotlin_do: TT_DO TT_LBRACE kotlin_stmt TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON  */
#line 313 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_while(arena, true, (yyvsp[-2].expr), (yyvsp[-6].stmt), NULL); }
#line 2512 "lib/parser/build/parser.tab.c"
    break;

  case 85: /* kotlin_do: TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON  */
#line 315 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2518 "lib/parser/build/parser.tab.c"
    break;

  case 86: /* kotlin_do: TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN TT_RPAREN TT_SEMICOLON  */
#line 317 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2524 "lib/parser/build/parser.tab.c"
    break;

  case 87: /* kotlin_for: TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt  */
#line 323 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, (yyvsp[-9].stmt), (yyvsp[-7].expr), (yyvsp[-5].stmt), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2530 "lib/parser/build/parser.tab.c"
    break;

  case 88: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt  */
#line 325 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, NULL, (yyvsp[-7].expr), (yyvsp[-5].stmt), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2536 "lib/parser/build/parser.tab.c"
    break;

  case 89: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt  */
#line 327 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, NULL, (yyvsp[-6].expr), NULL, (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2542 "lib/parser/build/parser.tab.c"
    break;

  case 90: /* kotlin_for: TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 329 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, (yyvsp[-7].stmt), (yyvsp[-5].expr), (yyvsp[-3].stmt), NULL, (yyvsp[0].stmt)); }
#line 2548 "lib/parser/build/parser.tab.c"
    break;

  case 91: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 331 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, NULL, (yyvsp[-5].expr), (yyvsp[-3].stmt), NULL, (yyvsp[0].stmt)); }
#line 2554 "lib/parser/build/parser.tab.c"
    break;

  case 92: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 333 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2560 "lib/parser/build/parser.tab.c"
    break;

  case 93: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt  */
#line 335 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2566 "lib/parser/build/parser.tab.c"
    break;

  case 94: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_SEMICOLON kotlin_stmt  */
#line 337 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2572 "lib/parser/build/parser.tab.c"
    break;

  case 95: /* kotlin_for: TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 340 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, (yyvsp[-8].stmt), (yyvsp[-6].expr), (yyvsp[-4].stmt), (yyvsp[-1].stmt), NULL); }
#line 2578 "lib/parser/build/parser.tab.c"
    break;

  case 96: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 342 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, NULL, (yyvsp[-6].expr), (yyvsp[-4].stmt), (yyvsp[-1].stmt), NULL); }
#line 2584 "lib/parser/build/parser.tab.c"
    break;

  case 97: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 344 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, NULL, (yyvsp[-5].expr), NULL, (yyvsp[-1].stmt), NULL); }
#line 2590 "lib/parser/build/parser.tab.c"
    break;

  case 98: /* kotlin_for: TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON  */
#line 346 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, (yyvsp[-6].stmt), (yyvsp[-4].expr), (yyvsp[-2].stmt), NULL, NULL); }
#line 2596 "lib/parser/build/parser.tab.c"
    break;

  case 99: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON  */
#line 348 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_for(arena, NULL, (yyvsp[-4].expr), (yyvsp[-2].stmt), NULL, NULL); }
#line 2602 "lib/parser/build/parser.tab.c"
    break;

  case 100: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_SEMICOLON  */
#line 350 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2608 "lib/parser/build/parser.tab.c"
    break;

  case 101: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_LBRACE TT_RBRACE  */
#line 352 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2614 "lib/parser/build/parser.tab.c"
    break;

  case 102: /* kotlin_for: TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_SEMICOLON  */
#line 354 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2620 "lib/parser/build/parser.tab.c"
    break;

  case 103: /* kotlin_for_init: TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_COMMA kotlin_for_init  */
#line 359 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, (yyvsp[-6].token), (yyvsp[-4].ktype), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2626 "lib/parser/build/parser.tab.c"
    break;

  case 104: /* kotlin_for_init: TT_VAR kotlin_identifier TT_COLON kotlin_type TT_COMMA kotlin_for_init  */
#line 361 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL, (yyvsp[-4].token), (yyvsp[-2].ktype), NULL, (yyvsp[0].stmt)); }
#line 2632 "lib/parser/build/parser.tab.c"
    break;

  case 105: /* kotlin_for_init: kotlin_for_incr  */
#line 363 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2638 "lib/parser/build/parser.tab.c"
    break;

  case 106: /* kotlin_for_incr: kotlin_identifier TT_ASSIGN kotlin_expression TT_COMMA kotlin_for_incr  */
#line 368 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2644 "lib/parser/build/parser.tab.c"
    break;

  case 107: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_PLUS kotlin_expression TT_COMMA kotlin_for_incr  */
#line 370 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2650 "lib/parser/build/parser.tab.c"
    break;

  case 108: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_MINUS kotlin_expression TT_COMMA kotlin_for_incr  */
#line 372 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2656 "lib/parser/build/parser.tab.c"
    break;

  case 109: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_MUL kotlin_expression TT_COMMA kotlin_for_incr  */
#line 374 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2662 "lib/parser/build/parser.tab.c"
    break;

  case 110: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_DIV kotlin_expression TT_COMMA kotlin_for_incr  */
#line 376 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, (yyvsp[-4].token), KOTLIN_DECL, (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2668 "lib/parser/build/parser.tab.c"
    break;

  case 111: /* kotlin_for_incr: kotlin_identifier TT_INCR TT_COMMA kotlin_for_incr  */
#line 378 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, (yyvsp[-3].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2674 "lib/parser/build/parser.tab.c"
    break;

  case 112: /* kotlin_for_incr: kotlin_identifier TT_DECR TT_COMMA kotlin_for_incr  */
#line 380 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, (yyvsp[-3].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2680 "lib/parser/build/parser.tab.c"
    break;

  case 113: /* kotlin_for_incr: TT_INCR kotlin_identifier TT_COMMA kotlin_for_incr  */
#line 382 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, (yyvsp[-2].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2686 "lib/parser/build/parser.tab.c"
    break;

  case 114: /* kotlin_for_incr: TT_DECR kotlin_identifier TT_COMMA kotlin_for_incr  */
#line 384 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, (yyvsp[-2].token), KOTLIN_DECL, NULL, (yyvsp[0].stmt)); }
#line 2692 "lib/parser/build/parser.tab.c"
    break;

  case 115: /* kotlin_for_incr: TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression  */
#line 387 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, (yyvsp[-4].token), (yyvsp[-2].ktype), (yyvsp[0].expr), NULL); }
#line 2698 "lib/parser/build/parser.tab.c"
    break;

  case 116: /* kotlin_for_incr: TT_VAR kotlin_identifier TT_COLON kotlin_type  */
#line 389 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECL, (yyvsp[-2].token), (yyvsp[0].ktype), NULL, NULL); }
#line 2704 "lib/parser/build/parser.tab.c"
    break;

  case 117: /* kotlin_for_incr: kotlin_identifier TT_ASSIGN kotlin_expression  */
#line 391 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, (yyvsp[-2].token), KOTLIN_DECL, (yyvsp[0].expr), NULL); }
#line 2710 "lib/parser/build/parser.tab.c"
    break;

  case 118: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_PLUS kotlin_expression  */
#line 393 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, (yyvsp[-2].token), KOTLIN_DECL, (yyvsp[0].expr), NULL); }
#line 2716 "lib/parser/build/parser.tab.c"
    break;

  case 119: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_MINUS kotlin_expression  */
#line 395 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, (yyvsp[-2].token), KOTLIN_DECL, (yyvsp[0].expr), NULL); }
#line 2722 "lib/parser/build/parser.tab.c"
    break;

  case 120: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_MUL kotlin_expression  */
#line 397 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, (yyvsp[-2].token), KOTLIN_DECL, (yyvsp[0].expr), NULL); }
#line 2728 "lib/parser/build/parser.tab.c"
    break;

  case 121: /* kotlin_for_incr: kotlin_identifier TT_EQUALS_DIV kotlin_expression  */
#line 399 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, (yyvsp[-2].token), KOTLIN_DECL, (yyvsp[0].expr), NULL); }
#line 2734 "lib/parser/build/parser.tab.c"
    break;

  case 122: /* kotlin_for_incr: kotlin_identifier TT_INCR  */
#line 401 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, (yyvsp[-1].token), KOTLIN_DECL, NULL, NULL); }
#line 2740 "lib/parser/build/parser.tab.c"
    break;

  case 123: /* kotlin_for_incr: kotlin_identifier TT_DECR  */
#line 403 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, (yyvsp[-1].token), KOTLIN_DECL, NULL, NULL); }
#line 2746 "lib/parser/build/parser.tab.c"
    break;

  case 124: /* kotlin_for_incr: TT_INCR kotlin_identifier  */
#line 405 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, (yyvsp[0].token), KOTLIN_DECL, NULL, NULL); }
#line 2752 "lib/parser/build/parser.tab.c"
    break;

  case 125: /* kotlin_for_incr: TT_DECR kotlin_identifier  */
#line 407 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, (yyvsp[0].token), KOTLIN_DECL, NULL, NULL); }
#line 2758 "lib/parser/build/parser.tab.c"
    break;

  case 126: /* kotlin_if: TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else kotlin_stmt  */
#line 412 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_IF, (yyvsp[-6].expr), (yyvsp[-3].stmt), (yyvsp[-1].stmt), (yyvsp[0].stmt)); }
#line 2764 "lib/parser/build/parser.tab.c"
    break;

  case 127: /* kotlin_if: TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt  */
#line 414 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_IF, (yyvsp[-5].expr), (yyvsp[-2].stmt), NULL, (yyvsp[0].stmt)); }
#line 2770 "lib/parser/build/parser.tab.c"
    break;

  case 128: /* kotlin_if: TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else kotlin_stmt  */
#line 416 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_IF, (yyvsp[-5].expr), NULL, (yyvsp[-1].stmt), (yyvsp[0].stmt)); }
#line 2776 "lib/parser/build/parser.tab.c"
    break;

  case 129: /* kotlin_if: TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt  */
#line 418 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2782 "lib/parser/build/parser.tab.c"
    break;

  case 130: /* kotlin_if: TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else  */
#line 431 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_IF, (yyvsp[-5].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), NULL); }
#line 2788 "lib/parser/build/parser.tab.c"
    break;

  case 131: /* kotlin_if: TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 433 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_IF, (yyvsp[-4].expr), (yyvsp[-1].stmt), NULL, NULL); }
#line 2794 "lib/parser/build/parser.tab.c"
    break;

  case 132: /* kotlin_if: TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else  */
#line 435 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_IF, (yyvsp[-4].expr), NULL, (yyvsp[0].stmt), NULL); }
#line 2800 "lib/parser/build/parser.tab.c"
    break;

  case 133: /* kotlin_elseif_else: TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else  */
#line 452 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_ELSEIF, (yyvsp[-5].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), NULL); }
#line 2806 "lib/parser/build/parser.tab.c"
    break;

  case 134: /* kotlin_elseif_else: TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else  */
#line 454 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_ELSEIF, (yyvsp[-4].expr), NULL, (yyvsp[0].stmt), NULL); }
#line 2812 "lib/parser/build/parser.tab.c"
    break;

  case 135: /* kotlin_elseif_else: TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 462 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_ELSEIF, (yyvsp[-4].expr), (yyvsp[-1].stmt), NULL, NULL); }
#line 2818 "lib/parser/build/parser.tab.c"
    break;

  case 136: /* kotlin_elseif_else: TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE  */
#line 464 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_ELSEIF, (yyvsp[-3].expr), NULL, NULL, NULL); }
#line 2824 "lib/parser/build/parser.tab.c"
    break;

  case 137: /* kotlin_elseif_else: TT_ELSE TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 474 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_ELSE, NULL, (yyvsp[-1].stmt), NULL, NULL); }
#line 2830 "lib/parser/build/parser.tab.c"
    break;

  case 138: /* kotlin_when: TT_WHEN TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_when_branch TT_RBRACE kotlin_stmt  */
#line 479 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_when(arena, (yyvsp[-5].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2836 "lib/parser/build/parser.tab.c"
    break;

  case 139: /* kotlin_when: TT_WHEN TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_when_branch TT_RBRACE  */
#line 481 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_when(arena, (yyvsp[-4].expr), (yyvsp[-1].stmt), NULL); }
#line 2842 "lib/parser/build/parser.tab.c"
    break;

  case 140: /* kotlin_when_branch: kotlin_expression TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE kotlin_when_branch  */
#line 486 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_CASE, (yyvsp[-5].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), NULL); }
#line 2848 "lib/parser/build/parser.tab.c"
    break;

  case 141: /* kotlin_when_branch: kotlin_expression TT_ARROW TT_LBRACE TT_RBRACE kotlin_when_branch  */
#line 488 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2854 "lib/parser/build/parser.tab.c"
    break;

  case 142: /* kotlin_when_branch: kotlin_expression TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 490 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_CASE, (yyvsp[-4].expr), (yyvsp[-1].stmt), NULL, NULL); }
#line 2860 "lib/parser/build/parser.tab.c"
    break;

  case 143: /* kotlin_when_branch: kotlin_expression TT_ARROW TT_LBRACE TT_RBRACE  */
#line 492 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2866 "lib/parser/build/parser.tab.c"
    break;

  case 144: /* kotlin_when_branch: TT_ELSE TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE kotlin_when_branch  */
#line 494 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_ELSE, NULL, (yyvsp[-2].stmt), (yyvsp[0].stmt), NULL); }
#line 2872 "lib/parser/build/parser.tab.c"
    break;

  case 145: /* kotlin_when_branch: TT_ELSE TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE  */
#line 496 "lib/parser/src/parser.y"
    { (yyval.stmt) = astn_create_stmt_if(arena, STMT_ELSE, NULL, (yyvsp[-1].stmt), NULL, NULL); }
#line 2878 "lib/parser/build/parser.tab.c"
    break;

  case 146: /* kotlin_when_branch: TT_ELSE TT_ARROW TT_LBRACE TT_RBRACE kotlin_when_branch  */
#line 498 "lib/parser/src/parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2884 "lib/parser/build/parser.tab.c"
    break;

  case 147: /* kotlin_when_branch: TT_ELSE TT_ARROW TT_LBRACE TT_RBRACE  */
#line 500 "lib/parser/src/parser.y"
    { (yyval.stmt) = NULL; }
#line 2890 "lib/parser/build/parser.tab.c"
    break;

  case 148: /* kotlin_return: TT_RETURN kotlin_expression_list TT_SEMICOLON  */
#line 505 "lib/parser/src/parser.y"
      { (yyval.stmt) = astn_create_stmt_ret(arena, (yyvsp[-1].expr_list), yylineno); }
#line 2896 "lib/parser/build/parser.tab.c"
    break;

  case 149: /* kotlin_return: TT_RETURN TT_SEMICOLON  */
#line 507 "lib/parser/src/parser.y"
      { (yyval.stmt) = astn_create_stmt_ret(arena, NULL, yylineno); }
#line 2902 "lib/parser/build/parser.tab.c"
    break;

  case 150: /* kotlin_expression: kotlin_expression TT_PLUS kotlin_expression  */
#line 512 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_ARIT_PLUS, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2908 "lib/parser/build/parser.tab.c"
    break;

  case 151: /* kotlin_expression: kotlin_expression TT_MINUS kotlin_expression  */
#line 514 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_ARIT_MINUS, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2914 "lib/parser/build/parser.tab.c"
    break;

  case 152: /* kotlin_expression: kotlin_expression TT_STAR kotlin_expression  */
#line 516 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_ARIT_MUL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2920 "lib/parser/build/parser.tab.c"
    break;

  case 153: /* kotlin_expression: kotlin_expression TT_SLASH kotlin_expression  */
#line 518 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_ARIT_DIV, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2926 "lib/parser/build/parser.tab.c"
    break;

  case 154: /* kotlin_expression: kotlin_expression TT_EQUALS kotlin_expression  */
#line 521 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_COMP_EQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2932 "lib/parser/build/parser.tab.c"
    break;

  case 155: /* kotlin_expression: kotlin_expression TT_NOT_EQUALS kotlin_expression  */
#line 523 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_COMP_NEQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2938 "lib/parser/build/parser.tab.c"
    break;

  case 156: /* kotlin_expression: kotlin_expression TT_LEQUALS kotlin_expression  */
#line 525 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_COMP_LEQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2944 "lib/parser/build/parser.tab.c"
    break;

  case 157: /* kotlin_expression: kotlin_expression TT_GEQUALS kotlin_expression  */
#line 527 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_COMP_GEQUAL, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2950 "lib/parser/build/parser.tab.c"
    break;

  case 158: /* kotlin_expression: kotlin_expression TT_LTHAN kotlin_expression  */
#line 529 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_COMP_LTHAN, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2956 "lib/parser/build/parser.tab.c"
    break;

  case 159: /* kotlin_expression: kotlin_expression TT_GTHAN kotlin_expression  */
#line 531 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_COMP_GTHAN, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2962 "lib/parser/build/parser.tab.c"
    break;

  case 160: /* kotlin_expression: kotlin_expression TT_AND kotlin_expression  */
#line 534 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_LOG_AND, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2968 "lib/parser/build/parser.tab.c"
    break;

  case 161: /* kotlin_expression: kotlin_expression TT_OR kotlin_expression  */
#line 536 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_bin(arena, OP_BIN_LOG_OR, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2974 "lib/parser/build/parser.tab.c"
    break;

  case 162: /* kotlin_expression: TT_BANG kotlin_expression  */
#line 539 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_un(arena, OP_UN_LOG_NOT, (yyvsp[0].expr)); }
#line 2980 "lib/parser/build/parser.tab.c"
    break;

  case 163: /* kotlin_expression: TT_PLUS kotlin_expression  */
#line 542 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_un(arena, OP_UN_ARIT_PLUS, (yyvsp[0].expr)); }
#line 2986 "lib/parser/build/parser.tab.c"
    break;

  case 164: /* kotlin_expression: TT_MINUS kotlin_expression  */
#line 544 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_un(arena, OP_UN_ARIT_MINUS, (yyvsp[0].expr)); }
#line 2992 "lib/parser/build/parser.tab.c"
    break;

  case 165: /* kotlin_expression: TT_LPAREN kotlin_expression TT_RPAREN  */
#line 547 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_un(arena, OP_UN_PAREN, (yyvsp[-1].expr)); }
#line 2998 "lib/parser/build/parser.tab.c"
    break;

  case 166: /* kotlin_expression: kotlin_fun_call  */
#line 550 "lib/parser/src/parser.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3004 "lib/parser/build/parser.tab.c"
    break;

  case 167: /* kotlin_expression: kotlin_token  */
#line 553 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_token(arena, (yyvsp[0].token)); }
#line 3010 "lib/parser/build/parser.tab.c"
    break;

  case 168: /* kotlin_token: TT_TRUE  */
#line 558 "lib/parser/src/parser.y"
      {
        (yyval.token) = astn_create_token(
          arena, TT_LIT_TRUE, NULL,
          filename, (yylsp[0]).first_line,
          (yylsp[0]).first_column, (yylsp[0]).last_column
        );
      }
#line 3022 "lib/parser/build/parser.tab.c"
    break;

  case 169: /* kotlin_token: TT_FALSE  */
#line 566 "lib/parser/src/parser.y"
      {
        (yyval.token) = astn_create_token(
          arena, TT_LIT_FALSE, NULL,
          filename, (yylsp[0]).first_line,
          (yylsp[0]).first_column, (yylsp[0]).last_column
        );
      }
#line 3034 "lib/parser/build/parser.tab.c"
    break;

  case 170: /* kotlin_token: TT_NULL  */
#line 574 "lib/parser/src/parser.y"
      {
        (yyval.token) = astn_create_token(
          arena, TT_LIT_NULL, NULL,
          filename, (yylsp[0]).first_line,
          (yylsp[0]).first_column, (yylsp[0]).last_column
        );
      }
#line 3046 "lib/parser/build/parser.tab.c"
    break;

  case 171: /* kotlin_token: TT_STRING_LIT  */
#line 582 "lib/parser/src/parser.y"
      {
        (yyval.token) = astn_create_token(
          arena, TT_LIT_STRING, (void*)yylval.str,
          filename, (yylsp[0]).first_line,
          (yylsp[0]).first_column, (yylsp[0]).last_column
        );
      }
#line 3058 "lib/parser/build/parser.tab.c"
    break;

  case 172: /* kotlin_token: TT_REAL  */
#line 590 "lib/parser/src/parser.y"
      {
        (yyval.token) = astn_create_token(
          arena, TT_LIT_REAL, (void*)&yylval.real,
          filename, (yylsp[0]).first_line,
          (yylsp[0]).first_column, (yylsp[0]).last_column
        );
      }
#line 3070 "lib/parser/build/parser.tab.c"
    break;

  case 173: /* kotlin_token: kotlin_number  */
#line 598 "lib/parser/src/parser.y"
      {
        (yyval.token) = (yyvsp[0].token);
      }
#line 3078 "lib/parser/build/parser.tab.c"
    break;

  case 174: /* kotlin_token: kotlin_identifier  */
#line 602 "lib/parser/src/parser.y"
      {
        (yyval.token) = (yyvsp[0].token);
      }
#line 3086 "lib/parser/build/parser.tab.c"
    break;

  case 175: /* kotlin_number: TT_NUMBER  */
#line 609 "lib/parser/src/parser.y"
      {
        (yyval.token) = astn_create_token(
          arena, TT_LIT_NUMBER, (void*)&yylval.num,
          filename, (yylsp[0]).first_line,
          (yylsp[0]).first_column, (yylsp[0]).last_column
        );
      }
#line 3098 "lib/parser/build/parser.tab.c"
    break;

  case 176: /* kotlin_identifier: TT_IDENTIFIER  */
#line 620 "lib/parser/src/parser.y"
      {
        (yyval.token) = astn_create_token(
          arena, TT_IDENT, (void*)yylval.str,
          filename, (yylsp[0]).first_line,
          (yylsp[0]).first_column, (yylsp[0]).last_column
        ); 
      }
#line 3110 "lib/parser/build/parser.tab.c"
    break;

  case 177: /* kotlin_fun_call: kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN  */
#line 631 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_fcall(arena, (yyvsp[-3].token), (yyvsp[-1].expr_list)); }
#line 3116 "lib/parser/build/parser.tab.c"
    break;

  case 178: /* kotlin_fun_call: kotlin_identifier TT_LPAREN TT_RPAREN  */
#line 633 "lib/parser/src/parser.y"
      { (yyval.expr) = astn_create_expr_fcall(arena, (yyvsp[-2].token), NULL); }
#line 3122 "lib/parser/build/parser.tab.c"
    break;

  case 179: /* kotlin_expression_list: kotlin_expression TT_COMMA kotlin_expression_list  */
#line 638 "lib/parser/src/parser.y"
      { (yyval.expr_list) = astn_create_expr_list(arena, (yyvsp[-2].expr), (yyvsp[0].expr_list)); }
#line 3128 "lib/parser/build/parser.tab.c"
    break;

  case 180: /* kotlin_expression_list: kotlin_expression  */
#line 640 "lib/parser/src/parser.y"
      { (yyval.expr_list) = astn_create_expr_list(arena, (yyvsp[0].expr), NULL); }
#line 3134 "lib/parser/build/parser.tab.c"
    break;


#line 3138 "lib/parser/build/parser.tab.c"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 643 "lib/parser/src/parser.y"


void yyerror(YYLTYPE* yylloc, const char* error_msg) {
  error_assert(error_unexp, yylloc != NULL);

  error_print_kotlin(error_parser, error_msg, filename, yylloc->first_line, yylloc->first_column);
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, ERROR_IO_SOURCE_FILE, filename);
    return;
  }
  char line[1024];
  for (
    int current_line = 1;
    fgets(line, sizeof(line), file) && current_line != yylloc->first_line;
    current_line++
  );
  fclose(file);

  fprintf(stderr, "%s", line);
  for (int i = 1; i < yylloc->first_column; i++)
    fprintf(stderr, " ");
  fprintf(stderr, "%s^", colors[RED]);
  uint32_t s_word = yylloc->last_column - yylloc->first_column + 1;
  for (int i = 1; i < s_word; i++)
    fprintf(stderr, "~");
  fprintf(stderr, "%s\n", colors[RESET]);
}
