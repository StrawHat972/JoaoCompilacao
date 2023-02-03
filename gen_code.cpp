#include "gen_code.h"

using namespace std;

Code::Code(vector<vector<string>> p_code) {
  this->p_code = p_code;

  out_string = ".text\n\n";

  op_map["+"] = "add";
  op_map["-"] = "sub";
  op_map["*"] = "mul";
  op_map["/"] = "div";
  op_map["<"] = "slt";
  op_map["/"] = "sgt";
  op_map["="] = "sub";

  out_string += "\
    addi sp sp -" + to_string(symTab.size() * 4) + "\n\
    addi fp sp 0\n\
    li t0 0\n";

  for (unsigned int i = 0; i < symTab.size(); i++) {
    out_string += "\
      sw t0 " + to_string((i+1)*4) + "(fp)\n";
  }

  gen_code();
}

void Code::gen_code() {
  for (unsigned int i = 0; i < p_code.size(); i++) {
    for (unsigned int j = 0; j < p_code[i].size(); j++) {
      switch(conclusao) {
        case IMM:
          immediate();
          save_stack();
          break;

        case VAR:
          variable();
          save_stack();
          break;

        case OPERATION:
          load_two_stack();
          operation(symbol);
          save_stack();
          break;

        case READ:
          read()
          assign(variable);
          break;

        case WRITE:
          load_one_stack();
          write();
          break;

        case ASSIGN:
          load_one_stack();
          assign(variable);
          break;

      }
    }
  }
}

void Code::save_stack() {
  out_string += "\
    addi sp sp -4\n\
    sw t0 0(sp)\n\
  ";
}

void Code::immediate(int number) {
  out_string += "\
    li t0 " + to_string(number) + "\n";
}

void Code::variable(string var) {
  out_string += "\
    lw t0 -" + to_string(symTab[var]) + "(fp)\n";
}

void Code::load_one_stack() {
  out_string += "\
    lw t0 0(sp)\n\
    addi sp sp 4\n";
}

void Code::load_two_stack() {
  out_string += "\
    lw t1 0(sp)\n\
    addi sp sp 4\n\
    lw t0 0(sp)\n\
    addi sp sp 4\n";
}

void Code::operation(string op_symbol) {
  out_string += "\
    " + op_map[op_symbol] + "t0 t0 t1\n";
}

void Code::assign(string var) {
  out_string += "\
    sw t0 -" + to_string(symTab[var]) + "(fp)\n";
}

void Code::read() {
  out_string += "\
    li a7 5\n\
    ecall\n\
    mv t0 a0\n";
}

void Code::write() {
  out_string += "\
    mv a0 t0\n\
    li a7 1\n\
    ecall\n";
}

vector<string> Code::string_split (string input, string delim = "\n")
{
  int len = input.length();
  char cmd[len + 1];
  strcpy(cmd, input.c_str());

  len = delim.length();
  char delimiter[len + 1];
  strcpy(delimiter, delim.c_str());

  char *ptr = strtok(cmd, delimiter);

  vector<string> inst;

  while(ptr != NULL) {
    string tmp = ptr;
    inst.push_back(tmp);
    ptr = strtok(NULL, delimiter);
  }

  return inst;
}

bool Code::is_number(string token) {
  
}