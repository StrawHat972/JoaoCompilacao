#include "util.h"
#include "parser.tab.h"
#include <stack>
#include <map>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

TreeNode* newStmtNode(StmtKind kind){
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    if(node != NULL){
        for(int i = 0; i < MAXCHILDREN; i++)
            node->child[i] = NULL;
        node->sibling = NULL;
        node->nodeK = StmtK;
        node->kind.stmt = kind;
    }
    return node;
}

TreeNode* newExpNode(ExpKind kind){
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    if(node != NULL){
        for(int i = 0; i < MAXCHILDREN; i++)
            node->child[i] = NULL;
        node->sibling = NULL;
        node->nodeK = ExpK;
        node->kind.exp = kind;
        node->type = Void;
    }
    return node;
}

char* copyStr(char* s){
    if(s == NULL) return NULL;

    int n = strlen(s) + 1;
    char* t = (char*) malloc(n);
    if(t != NULL) strcpy(t, s);

    return t;
}

void _deleteNode(TreeNode* node){
    if(node == NULL) return;

    _deleteNode(node->sibling);
    _deleteNode(node->child[0]);
    _deleteNode(node->child[1]);
    _deleteNode(node->child[2]);

    if(node->nodeK == ExpK && node->kind.exp == IdK)
        free(node->attr.name);
    else if(node->nodeK == StmtK && (node->kind.stmt == ReadK || node->kind.stmt == AssignK))
        free(node->attr.name);
    free(node);
}

void deleteTree(TreeNode** tree){
	_deleteNode(*tree);
	*tree = NULL;
}

string _printOp(TokenType op){
	switch(op){
		case LT:
			return "<"; 
		case EQ:
			return "="; 
		case GT:
			return ">"; 
		case PLUS:
			return "+"; 
		case MINUS:
			return "-"; 
		case TIMES:
			return "*"; 
		case OVER:
			return "/"; 
		default:
			return "Unknown operation"; 
	}
}

static int spaces = 0;

void _printSpaces(){
	for(int i = 0; i < spaces; i++)
		printf(" ");
}

string _print_node(TreeNode * tree)
{
	if(tree->nodeK == StmtK){
		switch(tree->kind.stmt){
			case IfK:
				return "";	//IF retorna string vazia mesmo
			case RepeatK:
				return "REPEAT ";
			case AssignK:
				return "ASSIGN: " + string(tree->attr.name) + " ";
			case ReadK:
				return "READ: " + string(tree->attr.name) + " ";
			case WriteK:
				return "WRITE ";
			default:
				return "Unknown StmtNode kind\n";
		}
	}
	else if(tree->nodeK == ExpK){
		switch(tree->kind.exp){
			case OpK:
				return _printOp(tree->attr.op) + " ";
			case ConstK:
				return to_string(tree->attr.val) + " ";
			case IdK:
				return string(tree->attr.name) + " ";
			default:
				return "Unknown ExpNode kind\n"; 
		}
	}

	return ("Unknown node kind\n");
}

void printTree(TreeNode* tree){
	spaces += 2;
	while(tree != NULL){
		_printSpaces();
		
		_print_node(tree);

		for(int i = 0; i < MAXCHILDREN; i++)
			printTree(tree->child[i]);
		tree = tree->sibling;
	}
	spaces -= 2;
}

bool _no_child(TreeNode* v)
{
	return v->child[0] == NULL && v->child[1] == NULL && v->child[2] == NULL;
}

map<TreeNode*, bool> visited;
vector<string> cmds;
string helper = "";
int if_flag = 0;
bool flag_if1 = false;
bool flag_if2 = false;

void dfs(TreeNode* v)
{
	if(_no_child(v))
	{
		helper += _print_node(v);
	}
	else
	{
		cmds.push_back(helper);
		helper = "";
		helper += _print_node(v);
	}
	
	visited[v] = true;
	for(int i = MAXCHILDREN-1; i >= 0; i--)
	// for(int i = 0; i < MAXCHILDREN; i++)
	{
		if(v->child[i] != NULL && ! visited.count(v->child[i]))
		{
			dfs(v->child[i]);
		}

		if (v->kind.stmt == IfK && i == 0)
			cmds.push_back("IF");
	}
}

void generate_3_add_code(TreeNode* v)
{
	if_flag = 0;
	dfs(v);
	cmds.push_back(helper);
	helper = "";
	reverse(cmds.begin(), cmds.end());
	for(string i : cmds) 
  		cout << i << endl;
}