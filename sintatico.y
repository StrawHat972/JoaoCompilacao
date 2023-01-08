%{
    #include "stdio.h"

    int yyerror(const char *str);
    int yylex();
%}

%token NUMBER
%token VAR
%token FLOAT
%token START
%token END
%token REPEAT
%token UNTIL
%token READ
%token WRITE
%token COMPOP
%token ADDOP
%token MULOP
%token ASSIGNOP

%%
input:  /* empty */
        | input line
;
line:   '\n' 
        | program '\n' {printf("Programa sintaticamente correto!\n");}
;
program: START stmt-sequence END {;}
;
stmt-sequence:  statement                       {;} 
                | stmt-sequence ';' statement   {;}
;
statement:  repeat-stmt     {;}
            | assign-stmt   {;}
            | read-stmt     {;}
            | write-stmt    {;}
;
repeat-stmt: REPEAT stmt-sequence UNTIL exp {;}
;
assign-stmt: VAR ASSIGNOP exp {;}
;
read-stmt: READ VAR {;}
;
write-stmt: WRITE exp {;}
;
exp:    simple-exp COMPOP simple-exp {;}
        | simple-exp                 {;}
;
simple-exp: simple-exp ADDOP term   {;}
            | term                  {;}
;
term:   term MULOP factor   {;}
        | factor            {;}
;
factor: '(' exp ')' {;}
        | NUMBER    {;}
        | FLOAT     {;}
        | VAR       {;}
;
%%

int main(int argc, char *argv[]){
    yyparse();
    return 0;
}

int yyerror(const char *str) {
    printf("Problema com a analise sintatica!\n");
    return 0;
}