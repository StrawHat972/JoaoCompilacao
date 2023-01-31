#pragma once
#include "util.h"
#include <iostream>
#include <unordered_map>

extern std::unordered_map<std::string, int> symTab;

void analyze(TreeNode* tree);
void printSymTab();