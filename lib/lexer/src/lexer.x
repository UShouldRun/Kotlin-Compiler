%{
#include "arena.h"
#include "parser.tab.h"

extern int yylex(YYSTYPE* yylval, YYLTYPE* yylloc);
extern Arena arena;

#define YY_DECL extern int yylex(YYSTYPE* yylval, YYLTYPE* yylloc)

uint32_t current_column = 1;
#define YY_USER_ACTION \
  yylloc->first_line   = yylineno; \
  yylloc->first_column = current_column; \
  yylloc->last_line    = yylineno; \
  yylloc->last_column  = current_column + yyleng - 1; \
  current_column += yyleng;
%}

%option yylineno
%option caseless
%option noinput nounput
%option noyywrap

alpha      [_a-zA-Z]
digit      [0-9]
hexa       ([0-9]|[a-f])
HEXA       ([0-9]|[A-F])
number_h   0(x{hexa}|X{HEXA})+
number     {digit}+
real       ({digit}+\.{digit}?|{digit}?\.{digit}+)(e((-)?{digit}+))?
id         {alpha}({alpha}|{digit})*
string     \"([^\\"]|\\.)*\"
whitespace [ \t\r]+
comment    ("//".*\n|"/*"([^*]|\*+[^*/])*\*+"/")

%% 

"if"           { return TT_IF; }
"else"         { return TT_ELSE; }
"else if"      { return TT_ELSEIF; }
"when"         { return TT_WHEN; }
"while"        { return TT_WHILE; }
"for"          { return TT_FOR; }
"do"           { return TT_DO; }
"return"       { return TT_RETURN; }
"null"         { return TT_NULL; }
"true"         { return TT_TRUE; }
"false"        { return TT_FALSE; }
"Byte"         { return TT_BYTE; }
"Short"        { return TT_SHORT; }
"Int"          { return TT_INT; }
"Long"         { return TT_LONG; }
"Float"        { return TT_FLOAT; }
"Double"       { return TT_DOUBLE; }
"Boolean"      { return TT_BOOLEAN; }
"Char"         { return TT_CHAR; }
"String"       { return TT_STRING; }
"fun"          { return TT_FUN; }
"enum"         { return TT_ENUM; }
"var"          { return TT_VAR; }
"val"          { return TT_VAL; }
"Any"          { return TT_ANY; }

"+"            { return TT_PLUS; }
"++"           { return TT_INCR; }
"-"            { return TT_MINUS; }
"--"           { return TT_DECR; }
"*"            { return TT_STAR; }
"/"            { return TT_SLASH; }
"("            { return TT_LPAREN; }
")"            { return TT_RPAREN; }
"{"            { return TT_LBRACE; }
"}"            { return TT_RBRACE; }
"["            { return TT_LPARENRECT; }
"]"            { return TT_RPARENRECT; }
"+="           { return TT_EQUALS_PLUS; }
"-="           { return TT_EQUALS_MINUS; }
"*="           { return TT_EQUALS_MUL; }
"/="           { return TT_EQUALS_DIV; }
"=="           { return TT_EQUALS; }
"!="           { return TT_NOT_EQUALS; }
"<"            { return TT_LTHAN; }
">"            { return TT_GTHAN; }
"<="           { return TT_LEQUALS; }
">="           { return TT_GEQUALS; }
"!"            { return TT_BANG; }
";"            { return TT_SEMICOLON; }
","            { return TT_COMMA; }
":"            { return TT_COLON; }
"="            { return TT_ASSIGN; }
"->"           { return TT_ARROW; }
"&&"           { return TT_AND; }
"||"           { return TT_OR; }
"."            { return TT_DOT; }

{whitespace}   ;
\n             { current_column = 1; }
{comment}      ;
{id}           { yylval->str  = arena_strdup(arena, yytext); return TT_IDENTIFIER; }
{number_h}     { yylval->num  = strtol(yytext, NULL, 16);    return TT_NUMBER; }
{number}       { yylval->num  = atoi(yytext);                return TT_NUMBER; }
{real}         { yylval->real = strtod(yytext, NULL);        return TT_REAL; }
{string}       { yylval->str  = arena_strdup(arena, yytext); return TT_STRING_LIT; }

.              ;

%%

/*
*/
/* string \"[^\"]*\" - may use this one*/
/* "in"           { return TT_IN; } */

