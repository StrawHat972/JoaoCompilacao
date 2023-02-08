#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "pCodeGen.h"
#include "../analysis/analyzer.h"

class Code {
	public:

	std::vector<p_node> p_code;
	std::string out_string;
	std::map<std::string, std::string> op_map;

	Code(std::vector<p_node>, std::string);

	void save_stack();
	void immediate(int);
	void comp();
	void variable(std::string);

	void load_one_stack();
	void load_two_stack();
	void load_two_invert();

	void operation(std::string);
	void read();
	void write();

	void label(std::string);
	void jump(std::string);
	void in_jump(std::string);
	void ru_jump(std::string);

	void assign(std::string);
	void return_0();

	void gen_code();
	void save_file(std::string);
};