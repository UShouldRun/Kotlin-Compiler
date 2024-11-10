#ifndef YY_PARSER_TAB_H_INCLUDED
#define YY_PARSER_TAB_H_INCLUDED

#include "ast.h"

#ifndef YYTOKENTYPE
#define YYTOKENTYPE
  enum yytokentype {
    TT_IDENTIFIER = 258,

    TT_NUMBER = 259,
    TT_REAL = 260,
    TT_STRING_LIT = 261,

    TT_PLUS = 263,
    TT_MINUS = 264,
    TT_STAR = 265,
    TT_SLASH = 266,

    TT_EQUALS_PLUS = 267,
    TT_EQUALS_MINUS = 268,
    TT_EQUALS_MUL = 269,
    TT_EQUALS_DIV = 270,

    TT_INCR = 271,
    TT_DECR = 272,

    TT_LPAREN = 273,
    TT_RPAREN = 274,
    TT_LBRACE = 275,
    TT_RBRACE = 276,
    TT_LPARENRECT = 277,
    TT_RPARENRECT = 278,

    TT_VAR = 279,
    TT_VAL = 280,
    TT_IF = 281,
    TT_ELSE = 282,
    TT_ELSEIF = 283,
    TT_WHILE = 284,
    TT_FOR = 285,
    TT_DO = 286,
    TT_WHEN = 287,
    TT_RETURN = 288,
    TT_IMPORT = 289,
    TT_FUN = 300,
    TT_ENUM = 301,

    TT_NULL = 302,
    TT_TRUE = 303,
    TT_FALSE = 304,
    TT_EQUALS = 305,
    TT_NOT_EQUALS = 306,
    TT_LTHAN = 307,
    TT_GTHAN = 308,
    TT_LEQUALS = 309,
    TT_GEQUALS = 310,
    TT_BANG = 311,
    TT_AND = 312,
    TT_OR = 313,

    TT_SEMICOLON = 314,
    TT_COMMA = 315,
    TT_COLON = 316,
    TT_ASSIGN = 317,
    TT_ARROW = 318,
    TT_DOT = 319, 
    TT_MAIN = 320,

    TT_BYTE = 321,
    TT_SHORT = 322,
    TT_INT = 323,
    TT_LONG = 324,
    TT_FLOAT = 325,
    TT_DOUBLE = 326,
    TT_BOOLEAN = 327,
    TT_CHAR = 328,
    TT_STRING = 329,
    TT_ANY = 330, 
    
    // TT_IN = 309,
};
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#endif
extern YYLTYPE yylloc;

int yyparse(void);

#endif /* !YY_PARSER_TAB_H_INCLUDED */
