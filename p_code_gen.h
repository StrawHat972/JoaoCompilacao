#pragma once
#include "util.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

typedef enum{UNDEFINED, OP, NUM, VAR, P_READ, P_WRITE, P_ASSIGN, JUMP, LABEL} Inst;

typedef struct
{
    Inst type_inst;
    std::string code;
}p_node;

// std::vector<std::vector<std::string>> generate_p_code(TreeNode* v);
void print_p_code(TreeNode *t);
void gen_p_code(TreeNode *t);