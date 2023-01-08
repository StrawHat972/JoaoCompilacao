/* Analisador Lexico */
%{
  # include "sintatico.tab.h"
%}

read read
write write
until until
repeat repeat
begin begin 
end end

int -?[0-9]+
var [_a-zA-Z][_a-zA-Z0-9]*
float -?(([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*)|([0-9]+))
comment \/\/.*
comp_op [>=<]
add_op [+-]
mul_op [\*\/]
assign_op :=

%%

{read}      {return READ;}
{write}     {return WRITE;}
{until}     {return UNTIL;}
{repeat}    {return REPEAT;}
{begin}     {return START;}
{end}       {return END;}

{int}       {return NUMBER;}
{var}       {return VAR;}
{float}     {return FLOAT;}
{comment}   {;}
{comp_op}   {return COMPOP;}
{add_op}    {return ADDOP;}
{mul_op}    {return MULOP;}
{assign_op} {return ASSIGNOP;}

[ \t]+      {;}
.|\n        {return yytext[0];}

%%

int yywrap() {
  return 1;
}