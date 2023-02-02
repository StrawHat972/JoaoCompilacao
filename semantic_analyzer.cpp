#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <map>

using namespace std;

vector<string> string_split (string input, string delim = "\n")
{
		int len = input.length();
		char cmd[len + 1];
		strcpy(cmd, input.c_str());

		len = delim.length();
		char delimiter[len + 1];
		strcpy(delimiter, delim.c_str());

	char *ptr = strtok(cmd, delimiter);

	vector<string> inst;

	while(ptr != NULL)
	{
			string tmp = ptr;
			inst.push_back(tmp);
			ptr = strtok(NULL, delimiter);
	}

	return inst;
}

void passage_one(string code)
{
    // vector<string> lines = string_split(code, "\n");

    // for(unsigned int i = 0; i < lines.size(); i++)
    // {
    //     vector<string> tokens = string_split(lines[i], " ");
    // }
    

}

void semantic_analyzer(string file_name)
{
    ifstream file(file_name);

	if (file.fail())
	{
		cout << "Nao foi possivel abrir o arquivo " + file_name + ", verifique sua existencia e os privilegios do programa e tente novamente!" << endl;
		exit(1);
	}

	stringstream buffer;
	buffer << file.rdbuf();

	string str = buffer.str();
    cout << str << endl;

    passage_one(str)
}


void help()
{
	cout << "Exemplo de uso do programa:" << endl;
	cout << "Analisador Semantico: ./semantic_analyzer.exe <nome do codigo> <nome do executavel>" << endl;
}

int main (int argc, char** argv) 
{
	vector<string> args(argc);

	if(argc != 3)
	{
		cout << "Quantidade de parametros informados errada!\n" << endl;
		help();
		exit(1);
	}

	for (int i = 0; i < argc; i++)
	{
		args[i] = (string) argv[i];
	}
    /*
    args[1] = nome do codigo
    args[2] = nome do executável
     */
    //Analise Lexica
    //Analise Sintática
    //Análise Semântica
    semantic_analyzer(args[1]);
    //Geração de Código

    

	
	return 0;
}