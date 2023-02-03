#include "util.h"
#include "analyzer.h"
#include "parser.tab.h"
#include "p_code_gen.h"

using namespace std;

int lineno = 0;
int Error = FALSE;
FILE* source;
unordered_map<string, int> symTab;

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("[!] Invalid number of arguments\n");
		return 1;
	}
	source = fopen(argv[1], "r");
	TreeNode* SyntaxTree = parser();
	fclose(source);

	if(!Error){
		printTree(SyntaxTree);
		analyze(SyntaxTree);
	}
	if(!Error)
	{
		cout << "\nDFS:\n";
		print_p_code(SyntaxTree);
		cout << "\n";
		printSymTab();
	}
		
	deleteTree(&SyntaxTree);
	return 0;
}