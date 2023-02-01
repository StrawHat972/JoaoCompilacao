/* Analisador Sintatico */
%{
	#include <stdio.h>
	#include "util.h"

	extern int yylex();
	extern FILE* yyin;

	void yyerror(const char *str);

	#define YYSTYPE TreeNode*

	static char* savedName;
	static TreeNode* savedTree;
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
%token LT
%token EQ
%token GT
%token LPAREN
%token RPAREN
%token SEMICOL
%token ASSIGN

%token NUMBER
%token ID

%%
program
	: stmt-seq
		{savedTree = $1;}
	| /* empty */
		{printf("[!] No command found in input file\n");
		 Error = TRUE;}
	;
stmt-seq
	: stmt-seq SEMICOL stmt
		{TreeNode* node = $1;
		 if(node != NULL){
			while(node->sibling != NULL)
				node = node->sibling;
			node->sibling = $3;
			$$ = $1;
		 } else $$ = $3;
		}
	| stmt
		{$$ = $1;}
	;
stmt
	: if-stmt
		{$$ = $1;}
	| repeat-stmt
		{$$ = $1;}
	| assign-stmt
		{$$ = $1;}
	| read-stmt
		{$$ = $1;}
	| write-stmt
		{$$ = $1;}
	| error
		{$$ = NULL;}
	;
if-stmt
	: IF exp THEN stmt-seq END
		{$$ = newStmtNode(IfK);
         $$->child[0] = $2;
         $$->child[1] = $4;}
	| IF exp THEN stmt-seq ELSE stmt-seq END
		{$$ = newStmtNode(IfK);
         $$->child[0] = $2;
         $$->child[1] = $4;
		 $$->child[2] = $6;}
	;
repeat-stmt
	: REPEAT stmt-seq UNTIL exp
		{$$ = newStmtNode(RepeatK);
		 $$->child[0] = $2;
		 $$->child[1] = $4;}
	;
assign-stmt
	: ID
		{savedName = copyStr(tokenStr);}
	  ASSIGN exp
	  	{$$ = newStmtNode(AssignK);
		 $$->child[0] = $4;
		 $$->attr.name = savedName;}
	;
read-stmt
	: READ ID
		{$$ = newStmtNode(ReadK);
		 $$->attr.name = copyStr(tokenStr);}
	;
write-stmt
	: WRITE exp
		{$$ = newStmtNode(WriteK);
		 $$->child[0] = $2;}
    ;
exp
	: simple-exp LT simple-exp
		{$$ = newExpNode(OpK);
		 $$->child[0] = $1;
		 $$->child[1] = $3;
		 $$->attr.op = LT;}
	| simple-exp EQ simple-exp
		{$$ = newExpNode(OpK);
		 $$->child[0] = $1;
		 $$->child[1] = $3;
		 $$->attr.op = EQ;}
	| simple-exp GT simple-exp
		{$$ = newExpNode(OpK);
		 $$->child[0] = $1;
		 $$->child[1] = $3;
		 $$->attr.op = GT;}
	| simple-exp
		{$$ = $1;}
	;
simple-exp
	: simple-exp PLUS term
		{$$ = newExpNode(OpK);
		 $$->child[0] = $1;
		 $$->child[1] = $3;
		 $$->attr.op = PLUS;}
	| simple-exp MINUS term
		{$$ = newExpNode(OpK);
		 $$->child[0] = $1;
		 $$->child[1] = $3;
		 $$->attr.op = MINUS;}
	| term
		{$$ = $1;}
	;
term
	: term TIMES factor
		{$$ = newExpNode(OpK);
		 $$->child[0] = $1;
		 $$->child[1] = $3;
		 $$->attr.op = TIMES;}
	| term OVER factor
		{$$ = newExpNode(OpK);
		 $$->child[0] = $1;
		 $$->child[1] = $3;
		 $$->attr.op = OVER;}
	| factor
		{$$ = $1;}
	;
factor
	: LPAREN exp RPAREN
		{$$ = $2;}
	| NUMBER
		{$$ = newExpNode(ConstK);
		 $$->attr.val = atoi(tokenStr);}
	| ID
		{$$ = newExpNode(IdK);
		 $$->attr.name = copyStr(tokenStr);}
	| error
		{$$ = NULL;}
	;
%%

void yyerror(const char *str) {
	printf("[!] Syntax error on line %d\n", lineno);
	Error = TRUE;
}

TreeNode* parser(){
	yyin = source;
	lineno++;
	yyparse();
	return savedTree;
}