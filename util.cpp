#include "util.h"
#include "parser.tab.h"
#include <stack>
#include <map>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <queue>
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

string _get_op(TokenType op){
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
				return "REPEAT";
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
				return _get_op(tree->attr.op) + " ";
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

void _printOp(TokenType op){
	switch(op){
		case LT:
			printf("<\n"); break;
		case EQ:
			printf("=\n"); break;
		case GT:
			printf(">\n"); break;
		case PLUS:
			printf("+\n"); break;
		case MINUS:
			printf("-\n"); break;
		case TIMES:
			printf("*\n"); break;
		case OVER:
			printf("/\n"); break;
		default:
			printf("Unknown operation\n"); break;
	}
}

void printTree(TreeNode* tree){
	spaces += 2;
	while(tree != NULL){
		_printSpaces();
		if(tree->nodeK == StmtK){
			switch(tree->kind.stmt){
				case IfK:
					printf("If\n"); break;
				case RepeatK:
					printf("Repeat\n"); break;
				case AssignK:
					printf("Assign to: %s\n", tree->attr.name); break;
				case ReadK:
					printf("Read: %s\n", tree->attr.name); break;
				case WriteK:
					printf("Write\n"); break;
				default:
					printf("Unknown StmtNode kind\n"); break;
			}
		}
		else if(tree->nodeK == ExpK){
			switch(tree->kind.exp){
				case OpK:
					printf("Op: "); _printOp(tree->attr.op); break;
				case ConstK:
					printf("Const: %d\n", tree->attr.val); break;
				case IdK:
					printf("Id: %s\n", tree->attr.name); break;
				default:
					printf("Unknown ExpNode kind\n"); break;
			}
		}
		else
			printf("Unknown node kind\n");

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
vector<string> cmd;
vector<vector<string>> cmds;

void dfs(TreeNode* v)
{
	cmd.push_back(_print_node(v));
	visited[v] = true;

	
	if(v->kind.stmt != IfK && v->kind.stmt != RepeatK)
	{
		for(int i = MAXCHILDREN-1; i >= 0; i--)
		{	
			if(v->child[i] != NULL && (! visited.count(v->child[i])))
				dfs(v->child[i]);
		}
	}else if(v->kind.stmt == RepeatK)
	{
		for(int i = 0; i < MAXCHILDREN; i++)
		{		
			if(v->child[i] != NULL && ! visited.count(v->child[i]))
			{
				dfs(v->child[i]);
			}

			if(i == 0)
				cmd.push_back("JUMP TO REPEAT LABEL");
		}
	}
	else
	{
		int indexes[3] = {1,2,0};

		for(int i = 0; i < MAXCHILDREN; i++)
		{
			if(v->child[indexes[i]] != NULL && ! visited.count(v->child[indexes[i]]))
			{
				dfs(v->child[indexes[i]]);
			}

			if (v->child[1] != NULL && v->child[2] == NULL && i == 1)
				cmd.push_back("IF LABEL");
			if (i == 1)
				cmd.push_back("JUMP TO IF LABEL");
			if (v->child[1] != NULL && v->child[2] != NULL && i == 0)
				cmd.push_back("IF LABEL");
		}
		
	}

	if (v->sibling != NULL)
	{
		reverse(cmd.begin(), cmd.end());
		cmds.push_back(cmd);
		cmd.clear();
		dfs(v->sibling);
	}
}

void generate_p_code(TreeNode* v)
{
	dfs(v);
	

	vector<vector<string>> p_code;

	int k = 1;
	for(vector<string> i : cmds) 
	{
		for(string j : i)
		{
			if(j == "REPEAT")
			{
				reverse(i.begin(), i.end());
			}
		}
		p_code.push_back(i);
	}
		
	for(auto i: p_code)
	{
		cout << "\nInst: " << k++ << endl << endl;
		for(auto j: i)
			cout << j << endl;

		
	}
		
	// 	cmds.clear();

	// 	v = v->sibling;
	// }
}