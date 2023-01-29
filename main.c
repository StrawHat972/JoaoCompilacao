#include "util.h"
#include "sintatico.tab.h"

int main(int argc, char *argv[]){
	TreeNode* SyntaxTree = parser();

	printTree(SyntaxTree);

	deleteTree(&SyntaxTree);
	return 0;
}