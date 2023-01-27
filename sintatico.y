/* Analisador Sintatico */
%{
    #include "stdio.h"

    int yyerror(const char *str);
    int yylex();
%}

%token IF
%token THEN
%token ELSE
%token END
%token REPEAT
%token UNTIL
%token READ
%token WRITE

%token PLUS
%token MINUS
%token TIMES
%token OVER
%token EQ
%token LT
%token LPAREN
%token RPAREN
%token SEMICOL
%token ASSIGN

%token NUMBER
%token ID

%%
input
        : /* empty */
        | input line
        ;
line
        : '\n' 
        | program '\n' {printf("Programa sintaticamente correto!\n");}
        ;
program
        : stmt-seq {;}
        ;
stmt-seq
        : stmt-seq SEMICOL stmt {;}
        | stmt                  {;}
        ;
stmt
        : if-stmt     {;}
        | repeat-stmt {;}
        | assign-stmt {;}
        | read-stmt   {;}
        | write-stmt  {;}
        ;
if-stmt
        : IF exp THEN stmt-seq END               {;}
        | IF exp THEN stmt-seq ELSE stmt-seq END {;}
        ;
repeat-stmt
        : REPEAT stmt-seq UNTIL exp {;}
        ;
assign-stmt
        : ID ASSIGN exp {;}
        ;
read-stmt
        : READ ID {;}
        ;
write-stmt
        : WRITE exp {;}
        ;
exp
        : simple-exp comp-op simple-exp {;}
        | simple-exp                    {;}
        ;
comp-op
        : LT {;}
        | EQ {;}
        ;
simple-exp
        : simple-exp addop term {;}
        | term                  {;}
        ;
addop
        : PLUS  {;}
        | MINUS {;}
        ;
term
        : term mulop factor {;}
        | factor            {;}
        ;
mulop
        : TIMES {;}
        | OVER  {;}
        ;
factor
        : LPAREN exp RPAREN {;}
        | NUMBER            {;}
        | ID                {;}
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