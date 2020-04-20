#include <iostream>
#include "lexico.h"

using namespace std;

unordered_map<int, vector<string>> symbol_table;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "Argument not passed !" << endl;
        return -1;
    }
    else
    {
        string programa = le_arquivo(argv[1]);
        if (programa == "ERRO")
        {
            return -1;
        }
        else
        {
            cout << programa << endl;
            cout << "\nTesting Table Hash:" << endl;
            vector<string> simb_program;
            simb_program.push_back("program");
            simb_program.push_back("simb_program");
            cout << "Input : { " << simb_program[0] << ", " << simb_program[1] << " }\n";
            int key = funcao_hash(simb_program[0]);
            cout << "Hash Key : " << key << endl;
            cout << "Adding element ..." << endl;
            symbol_table[key] = simb_program;
            unordered_map<int, vector<string>>::const_iterator got = symbol_table.find(key);
            if (symbol_table.find(key) != symbol_table.end())
            {
                cout << "Element is present !" << endl;
                vector<string> aux = symbol_table.at(key);
                cout << "Element : { " << aux[0] << ", " << aux[1] << " }";
            }
            else
            {
                cout << "Element is not present !";
            }
        }
    }

    return 0;
}