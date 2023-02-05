#include "codeGen.h"

using namespace std;

Code::Code(vector<p_node> p_code, string path) {
	this->p_code = p_code;

	out_string = ".text\n";

	op_map["+"] = "add";
	op_map["-"] = "sub";
	op_map["*"] = "mul";
	op_map["/"] = "div";
	op_map["<"] = "slt";
	op_map[">"] = "slt";
	op_map["="] = "sub";

	out_string += "\taddi sp sp -" + to_string(symTab.size() * 4) + "\n";
	out_string += "\tmv tp sp\n";
	out_string += "\tli t0 0\n";

	for (unsigned int i = 0; i < symTab.size(); i++)
		out_string += "\tsw t0 " + to_string(i*4) + "(tp)\n";

	gen_code();
	return_0();
	save_file(path);
}

void Code::gen_code() {
	for (unsigned int i = 0; i < p_code.size(); i++) {
		p_node node = p_code[i];
		switch(node.type_inst) {
			case NUM:
				immediate(atoi(node.code.c_str()));
				save_stack();
				break;
			case VAR:
				variable(node.code);
				save_stack();
				break;
			case OP:
				load_two_stack();
				operation(node.code);
				if(node.code == "=" || node.code == ">") 
					comp();
				save_stack();
				break;
			case P_READ:
				read();
				assign(node.code);
				break;
			case P_WRITE:
				load_one_stack();
				write();
				break;
			case P_ASSIGN:
				load_one_stack();
				assign(node.code);
				break;
			case LABEL:
				label(node.code);
				break;
			case JUMP:
				load_one_stack();
				jump(node.code);
				break;
			case IN_JUMP:
				load_one_stack();
				in_jump(node.code);
				break;
			case RU_JUMP:
				load_one_stack();
				ru_jump(node.code);
				break;
			default:
				break;
		}
	}
}

void Code::save_stack() {
	out_string += "\taddi sp sp -4\n";
	out_string += "\tsw t0 0(sp)\n";
}

void Code::immediate(int number) {
	out_string += "\tli t0 " + to_string(number) + "\n";
}

void Code::variable(string var) {
	out_string += "\tlw t0 " + to_string(symTab[var]) + "(tp)\n";
}

void Code::load_one_stack() {
	out_string += "\tlw t0 0(sp)\n";
	out_string += "\taddi sp sp 4\n";
}

void Code::load_two_stack() {
	out_string += "\tlw t1 0(sp)\n";
	out_string += "\taddi sp sp 4\n";
	out_string += "\tlw t0 0(sp)\n";
	out_string += "\taddi sp sp 4\n";
}

void Code::operation(string op_symbol) {
	out_string += "\t" + op_map[op_symbol] + " t0 t0 t1\n";
}

void Code::comp() {
	out_string += "\tseqz t0 t0\n";
}

void Code::assign(string var) {
	out_string += "\tsw t0 " + to_string(symTab[var]) + "(tp)\n";
}

void Code::read() {
	out_string += "\tli a7 5\n";
	out_string += "\tecall\n";
	out_string += "\tmv t0 a0\n";
}

void Code::write() {
	out_string += "\tmv a0 t0\n";
	out_string += "\tli a7 1\n";
	out_string += "\tecall\n";
	out_string += "\tli a0 10\n";
	out_string += "\tli a7 11\n";
	out_string += "\tecall\n";
}

void Code::label(string label) {
	out_string += label + ":\n";
}

void Code::jump(string label) {
	out_string += "\tli t1 1\n";
	out_string += "\tbeq t0 t1 " + label + "\n";
}

void Code::ru_jump(string label) {
	out_string += "\tli t1 0\n";
	out_string += "\tbeq t0 t1 " + label + "\n";
}

void Code::in_jump(string label) {
	out_string += "\tj " + label + "\n";
}

void Code::return_0(){
	out_string += "\taddi tp tp " + to_string(symTab.size() * 4) + "\n";
	out_string += "\tmv sp tp\n";
	out_string += "\tli a7 10\n";
	out_string += "\tecall";
}

void Code::save_file(string path) {
	ofstream file;
	file.open(path);
	file << out_string;
	file.close();
}