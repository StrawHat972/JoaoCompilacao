#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHILDREN 3
#define MAXTOKENLEN 50
#define FALSE 0
#define TRUE 1

typedef enum {StmtK, ExpK} NodeKind;
typedef enum {RepeatK, AssignK, ReadK, WriteK, IfK} StmtKind;
typedef enum {OpK, ConstK, IdK} ExpKind;
typedef enum {Void, Integer, Boolean} ExpType;

typedef int TokenType;

typedef struct treeNode {
	struct treeNode* child[MAXCHILDREN];
	struct treeNode* sibling;
	NodeKind nodeK;
	union {StmtKind stmt; ExpKind exp;} kind;
	union {TokenType op; int val; char* name;} attr;
	ExpType type;
} TreeNode;

extern char tokenStr[MAXTOKENLEN+1];
extern int lineno;
extern int Error;
extern FILE* source;

TreeNode* newStmtNode(StmtKind kind);
TreeNode* newExpNode(ExpKind kind);
TreeNode* parser();

char* copyStr(char* str);
void deleteTree(TreeNode** root);
void printTree(TreeNode* tree);
void generate_p_code(TreeNode* v);