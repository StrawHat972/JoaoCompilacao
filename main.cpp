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
	if(argc < 2 || argc > 3){
		cout << "[!] Invalid number of arguments\n";
		return 1;
	}

	string inputFile;
	char cmd;
	if(argc == 2)
		inputFile = argv[1];
	else{
		cmd = argv[1][1];
		inputFile = argv[2];
	}

	source = fopen(inputFile.c_str(), "r");
	if(source == NULL){
		cout << "[!] Error in opening input file\n";
		return 1;
	}

	TreeNode* SyntaxTree = parser();
	fclose(source);

	if(!Error){
		if(cmd == 't' || cmd == 'a')
			printTree(SyntaxTree);
		analyze(SyntaxTree);
	}
	if(!Error){
		if(cmd == 's' || cmd == 'a')
			printSymTab();

		vector<p_node> p_code = get_p_code(SyntaxTree);
		if(cmd == 'p' || cmd == 'a')
			print_p_code();

		int i = inputFile.find(".tiny");
		string new_path = inputFile.substr(0, i) + ".s";

		Code(p_code, new_path);	
	}

	deleteTree(&SyntaxTree);
	return 0;
}
