#include "util.h"
#include "parser.tab.h"

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

static int spaces = 0;

void _printSpaces(){
	for(int i = 0; i < spaces; i++)
		printf(" ");
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