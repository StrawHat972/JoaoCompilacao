#include "util.h"
#include "sintatico.tab.h"

int lineno = 0;
int Error = FALSE;
FILE* source;

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("[!] Quantidade inadequada de argumentos\n");
		return 1;
	}
	source = fopen(argv[1], "r");
	TreeNode* SyntaxTree = parser();
	fclose(source);

	if(!Error)
		printTree(SyntaxTree);
	deleteTree(&SyntaxTree);
	return 0;
}