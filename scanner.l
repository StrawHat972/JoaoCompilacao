/* Analisador Lexico */
%{
	#include "parser.tab.h"
	#include "util.h"

	#define copyStr(a, b) strncpy(a, b, MAXTOKENLEN)
	char tokenStr[MAXTOKENLEN+1];
%}
%x SC_COMMENT

number	[0-9]+
id		[a-zA-Z]+

%%
"if"		{return IF;}
"then"		{return THEN;}
"else"		{return ELSE;}
"end"		{return END;}
"repeat"	{return REPEAT;}
"until"		{return UNTIL;}
"read"		{return READ;}
"write"		{return WRITE;}

"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return TIMES;}
"/"			{return OVER;}
"<"			{return LT;}
"="			{return EQ;}
">"			{return GT;}
"("			{return LPAREN;}
")"			{return RPAREN;}
";"			{return SEMICOL;}
":="		{return ASSIGN;}

{number}	{copyStr(tokenStr, yytext); return NUMBER;}
{id}		{copyStr(tokenStr, yytext); return ID;}

"{"			{BEGIN(SC_COMMENT);}
<SC_COMMENT>{
	"}"		{BEGIN(INITIAL);}
	\n 		{lineno++;}
	.		{;}
}

[ \t\r]+	{;}
\n			{lineno++;}
.			{return yytext[0];}
%%

int yywrap(){
	return 1;
}