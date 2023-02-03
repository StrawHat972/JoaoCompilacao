#include "gen_code.h"

using namespace std;

Code::Code(vector<p_node> p_code, string path) {
  this->p_code = p_code;

  out_string = ".text\n\n";

  op_map["+"] = "add";
  op_map["-"] = "sub";
  op_map["*"] = "mul";
  op_map["/"] = "div";
  op_map["<"] = "slt";
  op_map[">"] = "slt";
  op_map["="] = "sub";

  out_string += "\
    addi sp sp -" + to_string(symTab.size() * 4) + "\n\
    mv tp sp\n\
    li t0 0\n";

  for (unsigned int i = 0; i < symTab.size(); i++) {
    out_string += "\
      sw t0 " + to_string(i*4) + "(tp)\n";
  }

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
        cout << "CAIU NO DEFAULT PIRANHA" << endl;
        break;

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
    lw t0 " + to_string(symTab[var]) + "(tp)\n";
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
    " + op_map[op_symbol] + " t0 t0 t1\n";
}

void Code::comp() {
  out_string+="\
    seqz t0 t0\n";
}

void Code::assign(string var) {
  out_string += "\
    sw t0 " + to_string(symTab[var]) + "(tp)\n";
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
    ecall\n\
    li a0 10\n\
    li a7 11\n\
    ecall\n";
}

void Code::label(string label) {
  out_string += "\
    " + label + ":\n";
}

void Code::jump(string label) {
  out_string += "\
    li t1 1\n\
    beq t0 t1 " + label + "\n";
}

void Code::ru_jump(string label) {
  out_string += "\
    li t1 0\n\
    beq t0 t1 " + label + "\n";
}

void Code::in_jump(string label) {
  out_string += "\
    j " + label + "\n";
}

void Code::return_0(){
  out_string += "\
    addi tp tp " + to_string(symTab.size() * 4) + "\n\
    mv sp tp\n\
    li a7 10\n\
    ecall\n";
}

void Code::save_file(string path) {
  ofstream f;
  f.open(path);
  f << out_string;
  f.close();
}