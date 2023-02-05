/* Analisador Semantico */
#include "analyzer.h"

using namespace std;

static int memOffset = 0;

void _typeError(string msg){
	printf("[!] Type error: %s\n", msg.c_str());
	Error = TRUE;
}

void _insertNode(TreeNode* node){
	switch(node->nodeK){
		case StmtK:
			switch(node->kind.stmt){
				case AssignK:
				case ReadK:
					if(symTab.find(string(node->attr.name)) == symTab.end())
						symTab[string(node->attr.name)] = (memOffset++) * 4;
					break;
				default: break;
            }
			break;
		case ExpK:
			switch(node->kind.exp){
				case IdK:
					if(symTab.find(string(node->attr.name)) == symTab.end())
						_typeError("Variable '" + string(node->attr.name) + "' not declared");
					break;
				default: break;
			}
			break;
		default: break;
	}
}

void _checkNode(TreeNode* node){
	switch(node->nodeK){
		case ExpK:
			switch(node->kind.exp){
				case OpK:
					if(node->child[0]->type != Integer || node->child[1]->type != Integer)
						_typeError("Operation applied to non-integer");
					if(node->attr.op == LT || node->attr.op == EQ || node->attr.op == GT)
						node->type = Boolean;
					else
						node->type = Integer;
					break;
				case ConstK:
				case IdK:
					node->type = Integer;
					break;
				default: break;
			}
			break;
		case StmtK:
			switch(node->kind.stmt){
				case IfK:
					if(node->child[0]->type == Integer)
						_typeError("If test is not Boolean");
					break;
				case RepeatK:
					if(node->child[1]->type == Integer)
						_typeError("Repeat test is not Boolean");
					break;
				case AssignK:
					if(node->child[0]->type != Integer)
						_typeError("Assignment of non-Integer value");
					break;
				case WriteK:
					if(node->child[0]->type != Integer)
						_typeError("Write of non-Integer value");
					break;
				default: break;
			}
			break;
		default: break;
	}
}

void analyze(TreeNode* tree){
	if(tree != NULL){
		_insertNode(tree);
		for(int i = 0; i < MAXCHILDREN; i++)
			analyze(tree->child[i]);
		_checkNode(tree);
		analyze(tree->sibling);
	}
}

void printSymTab(){
	cout << "Symbol Table:\n";
	for(auto it = symTab.cbegin(); it != symTab.cend(); it++){
		cout << "  " << it->first << ":";
		cout << "\t  " << it->second << endl;
	}
}