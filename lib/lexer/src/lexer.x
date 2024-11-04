%{
#include "arena.h"
#include "ast.h"
#include "parser.tab.h"

#define YY_DECL int yylex(YYSTYPE* yylval, YYLTYPE* yylloc, AST* ast)
%}

%option caseless

alpha      [_a-zA-Z]
digit      [0-9]
id         {alpha}({alpha}|{digit})*
number     {digit}+(\.{digit}+)?
string     \"([^\\"]|\\.)*\"
whitespace [ \t\n\r]+
comment    ("//".*\n|"/*"([^*]|\*+[^*/])*\*+"/")

%% 

"if"           { return TT_IF; }
"else"         { return TT_ELSE; }
"elseif"       { return TT_ELSEIF; }
"when"         { return TT_WHEN; }
"while"        { return TT_WHILE; }
"for"          { return TT_FOR; }
"in"           { return TT_IN; }
"do"           { return TT_DO; }
"return"       { return TT_RETURN; }
"null"         { return TT_NULL; }
"true"         { return TT_TRUE; }
"false"        { return TT_FALSE; }
"main"         { return TT_MAIN; }
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
{comment}      ;
{id}           { return TT_IDENTIFIER; }
{number}       { yylval.num = atoi(yytext); return TT_NUMBER; }
{string}       { return TT_STRING_LIT; }

.              { /* Ignore any other character */ }

%%
