/* Analisador Lexico */
%{
  # include "sintatico.tab.h"
%}

number        [0-9]+
identifier    [a-zA-Z]+
comment       \/\/.*

%%
"if"          {return IF;}
"then"        {return THEN;}
"else"        {return ELSE;}
"end"         {return END;}
"repeat"      {return REPEAT;}
"until"       {return UNTIL;}
"read"        {return READ;}
"write"       {return WRITE;}

"+"           {return PLUS;}
"-"           {return MINUS;}
"*"           {return TIMES;}
"/"           {return OVER;}
"="           {return EQ;}
"<"           {return LT;}
"("           {return LPAREN;}
")"           {return RPAREN;}
";"           {return SEMICOL;}
":="          {return ASSIGN;}

{number}      {return NUMBER;}
{identifier}  {return ID;}

{comment}     {;}
[ \t]+        {;}
.|\n          {return yytext[0];}
%%

int yywrap() {
  return 1;
}