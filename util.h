#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHILDREN 3
#define MAXTOKENLEN 50

typedef int TokenType;

typedef enum {StmtK, ExpK} NodeKind;
typedef enum {IfK, RepeatK, AssignK, ReadK, WriteK} StmtKind;
typedef enum {OpK, ConstK, IdK} ExpKind;

typedef enum {Void, Integer, Boolean} ExpType;

typedef struct treeNode {
    struct treeNode* child[MAXCHILDREN];
    struct treeNode* sibling;
    NodeKind nodeK;
    union {StmtKind stmt; ExpKind exp;} kind;
    union {TokenType op; int val; char* name;} attr;
    ExpType type;
} TreeNode;

extern char tokenStr[MAXTOKENLEN+1];

TreeNode* newStmtNode(StmtKind kind);
TreeNode* newExpNode(ExpKind kind);
TreeNode* parser();
char* copyStr(char* str);
void _deleteNode(TreeNode* node);
void deleteTree(TreeNode** root);


void printTree( TreeNode * );