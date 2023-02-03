#include "p_code_gen.h"
#include "parser.tab.h"

using namespace std;

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

map<TreeNode*, bool> visited;
vector<string> cmd;
vector<vector<string>> cmds;

void _dfs(TreeNode* v)
{
	cmd.push_back(_print_node(v));
	visited[v] = true;
	int indexes[3] = {1,2,0};
	
	if(v->nodeK == StmtK && v->kind.stmt == IfK)
		for(int i = 0; i < MAXCHILDREN; i++)
		{
			if(v->child[indexes[i]] != NULL && ! visited.count(v->child[indexes[i]]))
			{
				_dfs(v->child[indexes[i]]);
			}

			if (v->child[1] != NULL && v->child[2] == NULL && i == 1)
				cmd.push_back("IF LABEL");
			if (i == 1)
				cmd.push_back("JUMP TO IF LABEL");
				
			if (v->child[1] != NULL && v->child[2] != NULL && i == 0)
				cmd.push_back("IF LABEL");
		}
	else if(v->nodeK == StmtK && v->kind.stmt == RepeatK)
		for(int i = 0; i < MAXCHILDREN; i++)
		{		
			if(v->child[i] != NULL && ! visited.count(v->child[i]))
			{
				_dfs(v->child[i]);
			}

			if(i == 0)
			{
				cmds.push_back(cmd);
				cmd.clear();
				cmd.push_back("JUMP TO REPEAT LABEL");
			}
		}
	else
		for(int i = MAXCHILDREN-1; i >= 0; i--)
		{	
			if(v->child[i] != NULL && (! visited.count(v->child[i])))
				_dfs(v->child[i]);
		}
	
	if (v->sibling != NULL)
	{
		reverse(cmd.begin(), cmd.end());
		cmds.push_back(cmd);
		cmd.clear();
		_dfs(v->sibling);
	}
}

vector<vector<string>> generate_p_code(TreeNode* v)
{
	_dfs(v);
	reverse(cmd.begin(), cmd.end());
	cmds.push_back(cmd);
	cmd.clear();

	vector<vector<string>> p_code;

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

	int k = 1;
	for(auto i: p_code)
	{
		cout << "\nInst: " << k++ << endl << endl;
		for(auto j: i)
			cout << j << endl;
	}
    return p_code;
}