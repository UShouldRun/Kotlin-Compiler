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

#ifndef YY_YY_LIB_PARSER_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_LIB_PARSER_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 21 "lib/parser/src/parser.y"

  #include "ast.h"

#line 53 "lib/parser/build/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TT_IDENTIFIER = 258,           /* TT_IDENTIFIER  */
    TT_VAR = 259,                  /* TT_VAR  */
    TT_VAL = 260,                  /* TT_VAL  */
    TT_STRING_LIT = 261,           /* TT_STRING_LIT  */
    TT_NUMBER = 262,               /* TT_NUMBER  */
    TT_REAL = 263,                 /* TT_REAL  */
    TT_TRUE = 264,                 /* TT_TRUE  */
    TT_FALSE = 265,                /* TT_FALSE  */
    TT_BYTE = 266,                 /* TT_BYTE  */
    TT_SHORT = 267,                /* TT_SHORT  */
    TT_INT = 268,                  /* TT_INT  */
    TT_LONG = 269,                 /* TT_LONG  */
    TT_FLOAT = 270,                /* TT_FLOAT  */
    TT_DOUBLE = 271,               /* TT_DOUBLE  */
    TT_BOOLEAN = 272,              /* TT_BOOLEAN  */
    TT_CHAR = 273,                 /* TT_CHAR  */
    TT_STRING = 274,               /* TT_STRING  */
    TT_ANY = 275,                  /* TT_ANY  */
    TT_INCR = 276,                 /* TT_INCR  */
    TT_DECR = 277,                 /* TT_DECR  */
    TT_EQUALS_PLUS = 278,          /* TT_EQUALS_PLUS  */
    TT_EQUALS_MINUS = 279,         /* TT_EQUALS_MINUS  */
    TT_EQUALS_MUL = 280,           /* TT_EQUALS_MUL  */
    TT_EQUALS_DIV = 281,           /* TT_EQUALS_DIV  */
    TT_LPAREN = 282,               /* TT_LPAREN  */
    TT_RPAREN = 283,               /* TT_RPAREN  */
    TT_LBRACE = 284,               /* TT_LBRACE  */
    TT_RBRACE = 285,               /* TT_RBRACE  */
    TT_LPARENRECT = 286,           /* TT_LPARENRECT  */
    TT_RPARENRECT = 287,           /* TT_RPARENRECT  */
    TT_SEMICOLON = 288,            /* TT_SEMICOLON  */
    TT_COLON = 289,                /* TT_COLON  */
    TT_COMMA = 290,                /* TT_COMMA  */
    TT_ASSIGN = 291,               /* TT_ASSIGN  */
    TT_ARROW = 292,                /* TT_ARROW  */
    TT_DOT = 293,                  /* TT_DOT  */
    TT_IF = 294,                   /* TT_IF  */
    TT_ELSE = 295,                 /* TT_ELSE  */
    TT_ELSEIF = 296,               /* TT_ELSEIF  */
    TT_WHEN = 297,                 /* TT_WHEN  */
    TT_WHILE = 298,                /* TT_WHILE  */
    TT_FOR = 299,                  /* TT_FOR  */
    TT_IN = 300,                   /* TT_IN  */
    TT_DO = 301,                   /* TT_DO  */
    TT_FUN = 302,                  /* TT_FUN  */
    TT_RETURN = 303,               /* TT_RETURN  */
    TT_NULL = 304,                 /* TT_NULL  */
    TT_ENUM = 305,                 /* TT_ENUM  */
    TT_EQUALS = 306,               /* TT_EQUALS  */
    TT_NOT_EQUALS = 307,           /* TT_NOT_EQUALS  */
    TT_LTHAN = 308,                /* TT_LTHAN  */
    TT_GTHAN = 309,                /* TT_GTHAN  */
    TT_LEQUALS = 310,              /* TT_LEQUALS  */
    TT_GEQUALS = 311,              /* TT_GEQUALS  */
    TT_AND = 312,                  /* TT_AND  */
    TT_OR = 313,                   /* TT_OR  */
    TT_PLUS = 314,                 /* TT_PLUS  */
    TT_MINUS = 315,                /* TT_MINUS  */
    TT_STAR = 316,                 /* TT_STAR  */
    TT_SLASH = 317,                /* TT_SLASH  */
    TT_BANG = 318                  /* TT_BANG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "lib/parser/src/parser.y"

  int64_t       num;
  double        real;
  const char*   str;
  AST           root;
  ASTN_Obj      obj;
  ASTN_EnumVal  enum_values;
  ASTN_FunArg   fun_args;
  ASTN_FunRet   fun_ret;
  ASTN_Stmt     stmt;
  ASTN_Expr     expr;
  ASTN_ExprList expr_list;
  ASTN_Token    token;
  ASTN_KType    ktype;
  ASTN_KTypeDefault ktype_default;

#line 150 "lib/parser/build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (void);


#endif /* !YY_YY_LIB_PARSER_BUILD_PARSER_TAB_H_INCLUDED  */
