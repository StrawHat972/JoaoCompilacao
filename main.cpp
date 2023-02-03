#include "util.h"
#include "analyzer.h"
#include "parser.tab.h"
#include "p_code_gen.h"
#include "gen_code.h"

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
		printSymTab();
		vector<p_node> p_code = get_p_code(SyntaxTree);
		int i = string(argv[1]).find(".tiny");
		string new_path = string(argv[1]).substr(0, i) + ".s";

		Code(p_code, new_path);	

		print_p_code();
	}

	deleteTree(&SyntaxTree);
	return 0;
}