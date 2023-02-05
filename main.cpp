#include "analysis/syntaxTree.h"
#include "analysis/analyzer.h"
#include "parser.tab.h"
#include "synthesis/pCodeGen.h"
#include "synthesis/codeGen.h"

using namespace std;

int lineno = 0;
int Error = FALSE;
FILE* source;
unordered_map<string, int> symTab;

int main(int argc, char *argv[]){
	if(argc != 2){
		cout << "[!] Invalid number of arguments\n";
		return 1;
	}

	source = fopen(argv[1], "r");
	if(source == NULL){
		cout << "[!] Error in opening input file\n";
		return 1;
	}

	TreeNode* SyntaxTree = parser();
	fclose(source);

	if(!Error){
		printTree(SyntaxTree);
		analyze(SyntaxTree);
	}
	if(!Error){
		printSymTab();

		vector<p_node> p_code = get_p_code(SyntaxTree);
		print_p_code();

		int i = string(argv[1]).find(".tiny");
		string new_path = string(argv[1]).substr(0, i) + ".s";

		Code(p_code, new_path);	
	}

	deleteTree(&SyntaxTree);
	return 0;
}