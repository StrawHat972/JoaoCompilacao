#include "pCodeGen.h"

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

int id_jump = 0;
vector<p_node> cmds;

p_node _expk_to_p(TreeNode *t)
{
	p_node p;
	p.type_inst = UNDEFINED;
	p.code = "";

	switch(t->kind.exp)
	{
		case OpK:
			p.type_inst = OP;
			p.code = _get_op(t->attr.op);
			return p;
		case IdK:
			p.type_inst = VAR;
			p.code = string(t->attr.name);
			return p;
		case ConstK:
			p.type_inst = NUM;
			p.code = to_string(t->attr.val);
			return p;
		default:
			break;
	}
	return p;
}

p_node _stmtk_to_p(TreeNode *t)
{
	p_node p;
	p.type_inst = UNDEFINED;
	p.code = "";
	switch(t->kind.stmt)
	{
		case WriteK:
			p.type_inst = P_WRITE;
			p.code = "";
			return p;
		case ReadK:
			p.type_inst = P_READ;
			p.code = string(t->attr.name);
			return p;
		case AssignK:
			p.type_inst = P_ASSIGN;
			p.code = string(t->attr.name);
		default:
			break;
	}
	return p;
}

void gen_p_code(TreeNode *t)
{
	if(t == NULL)
		return;

	if (t->nodeK == StmtK && t->kind.stmt == IfK)
	{
		p_node p;
		gen_p_code(t->child[0]);

		string jump = "J" + to_string(id_jump++);

		p.type_inst = JUMP;
		p.code = jump;
		cmds.push_back(p);

		gen_p_code(t->child[2]);
		string jump1 = "J" + to_string(id_jump++);
		p.type_inst = IN_JUMP;
		p.code = jump1;
		cmds.push_back(p);

		p.type_inst = LABEL;
		p.code = jump;
		cmds.push_back(p);

		gen_p_code(t->child[1]);
		p.type_inst = LABEL;
		p.code = jump1;
		cmds.push_back(p);
	}
	else if (t->nodeK == StmtK && t->kind.stmt == RepeatK)
	{
		p_node p;
		string jump = "J" + to_string(id_jump++);
		p.type_inst = LABEL;
		p.code = jump;
		cmds.push_back(p);

		gen_p_code(t->child[0]);
		gen_p_code(t->child[1]);

		p.type_inst = RU_JUMP;
		p.code = jump;
		cmds.push_back(p);
	}else
	{
		for(int i = 0; i < MAXCHILDREN; i++)
			gen_p_code(t->child[i]);
	}

	p_node p;

	if(t->nodeK == StmtK)
	{
		p = _stmtk_to_p(t);
		if(p.type_inst != UNDEFINED)
			cmds.push_back(p);
	}else
	{
		p = _expk_to_p(t);
		if(p.type_inst != UNDEFINED)
			cmds.push_back(p);
	}

	gen_p_code(t->sibling);
}

void print_p_code()
{
	map<Inst, string> inst_map;
	inst_map[UNDEFINED] = "Undefined";
	inst_map[OP] 		= "Operation";
	inst_map[NUM] 		= "Number";
	inst_map[VAR] 		= "Identifier";
	inst_map[P_READ] 	= "Read";
	inst_map[P_WRITE] 	= "Write";
	inst_map[P_ASSIGN] 	= "Assign";
	inst_map[JUMP] 		= "Jump";
	inst_map[LABEL] 	= "Label";
	inst_map[IN_JUMP] 	= "In_Jump";
	inst_map[RU_JUMP] 	= "Ru_Jump";

	for(auto el: cmds)
		cout << "TYPE_INST: " << inst_map[el.type_inst] << "  \tCODE: " << el.code << endl;

}

vector<p_node> get_p_code(TreeNode *t) {
	gen_p_code(t);
	return cmds;
}