#ifndef YY_PARSER_TAB_H_INCLUDED
#define YY_PARSER_TAB_H_INCLUDED

#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype {
    TT_IDENTIFIER = 258,

    TT_NUMBER = 259,
    TT_REAL = 260,
    TT_STRING_LIT = 261,

    TT_VAR = 262,
    TT_PLUS = 263,
    TT_MINUS = 264,
    TT_STAR = 265,
    TT_SLASH = 266,

    TT_LPAREN = 267,
    TT_RPAREN = 268,
    TT_LBRACE = 269,
    TT_RBRACE = 270,

    TT_IF = 271,
    TT_ELSE = 272,
    TT_ELSEIF = 273,
    TT_WHILE = 274,
    TT_FOR = 275,
    TT_FUN = 276,
    TT_RETURN = 277,

    TT_NULL = 278,
    TT_TRUE = 279,
    TT_FALSE = 280,

    TT_EQUALS = 281,
    TT_NOT_EQUALS = 282,
    TT_LTHAN = 283,
    TT_GTHAN = 284,
    TT_LEQUALS = 285,
    TT_GEQUALS = 286,

    TT_SEMICOLON = 287,
    TT_COMMA = 288,
    TT_COLON = 289,
    TT_ASSIGN = 290,
    TT_MAIN = 291,

    TT_BYTE = 292,
    TT_SHORT = 293,
    TT_INT = 294,
    TT_LONG = 295,
    TT_FLOAT = 296,
    TT_DOUBLE = 297,
    TT_BOOLEAN = 298,
    TT_CHAR = 299,

    TT_IMPORT = 300
    TT_FUN = 301,
    TT_ENUM = 302,
    TT_VAL = 303,
    
    TT_INCR = 304,
    TT_DECR = 305,
    TT_EQUALS_PLUS = 306,
    TT_EQUALS_MINUS = 307,
    TT_EQUALS_MUL = 305,
    TT_EQUALS_DIV = 306

    TT_DO = 307,
    TT_WHEN = 308,
    TT_IN = 309,

    TT_ARROW = 310,
    TT_DOT = 311,

    TT_STRING = 312,
    TT_ANY = 313,

    TT_BANG = 314,
    TT_AND = 315,
    TT_OR = 316,

    TT_LPARENRECT = 317,
    TT_RPARENRECT = 318
};
;
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE {
    int num;
} YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_PARSER_TAB_H_INCLUDED */
