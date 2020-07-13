%{
  #include "parser.tab.h"
%}

%option reentrant
%option bison-bridge
%option noyywrap nounput noinput

LITERAL [a-zA-Z0-9]
BYTE    \\x[0-9a-fA-F][0-9a-fA-F]

%%

{LITERAL}   { yylval->charval = yytext[0]; return LITERAL; }
{BYTE}      { yylval->strval = strdup(yytext); return BYTE; }
"["         { return BEGIN_BRACKET; }
"]"         { return END_BRACKET; }
"("         { return BEGIN_GROUP; }
"|"         { return BRANCH; }
")"         { return END_GROUP; }
"-"         { return TO; }
"."         { return ANY; }
.           { yylval->strval = strdup(yytext); return ERROR; }
%%
