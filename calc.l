%{
#include <stdio.h>
%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

DIGIT      [0-9]
LETTER     [a-zA-Z_]
ID         {LETTER}({LETTER}|{DIGIT})*
NUM        {DIGIT}+

%%

"end"           { return END; }

{ID}            { return IDENTIFIER; }
{NUM}           { return NUM; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"="             { return '='; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
"["             { return '['; }
"]"             { return ']'; }
"{"             { return '{'; }
"}"             { return '}'; }

/* Whitespace */
[ \t\r\n]+      { }

/* Catch invalid characters */
.               { }

%%

