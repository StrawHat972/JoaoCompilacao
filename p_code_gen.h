#pragma once
#include "util.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

typedef enum{UNDEFINED, OP, NUM, VAR, P_READ, P_WRITE, P_ASSIGN, JUMP, LABEL, IN_JUMP, RU_JUMP} Inst;

typedef struct
{
    Inst type_inst;
    std::string code;
}p_node;

void print_p_code();
void gen_p_code(TreeNode *t);
std::vector<p_node> get_p_code(TreeNode *t);