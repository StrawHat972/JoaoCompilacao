#pragma once
#include <map>
#include <string>
#include <vector>
#include <format>
#include <regex>
#include "analyzer.h"

class Code {
  public:
  
  std::vector<std::vector<std::string>> p_code;
  std::string out_string;
  std::map<std::string, std::string> op_map;

  Code(std::vector<std::vector<std::string>>);

  void save_stack();
  void immediate(int);
  void variable(std::string);

  void load_one_stack();
  void load_two_stack();

  void operation(std::string);
  void read();
  void write();

  void assign(std::string);

  void gen_code();

  private:
  std::vector<std::string> string_split(std::string, std::string);

  bool is_number(std::string);
  bool is_var(std::string);
  bool is_op(std::string);

};