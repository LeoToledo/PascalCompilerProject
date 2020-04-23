#include <iostream>
#include "lexico.h"

using namespace std;
using namespace lexico;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "Argument not passed !" << endl;
        return -1;
    }
    else
    {
        LexicoPascalCompiler lexico;
        lexico.le_programa(argv[1]);
        if (lexico.programa == "ERRO")
        {
            return -1;
        }
        else
        {
            cout << lexico.programa << endl;
            cout << "\nTesting Table Hash:" << endl;
            vector<string> simb_program;
            simb_program.push_back("program");
            simb_program.push_back("simb_program");
            cout << "Input : { " << simb_program[0] << ", " << simb_program[1] << " }\n";
            int key = lexico.funcao_hash(simb_program[0]);
            cout << "Hash Key : " << key << endl;
            cout << "Adding element ..." << endl;
            lexico.SetIdentificador(simb_program[0], simb_program[1]);
            lexico.insere_hash("simbolos_reservados.txt", "tokens_reservados.txt");
            vector<string> aux = lexico.GetIdentificador("for");
            if (aux[0] != "ERRO")
            {
                cout << "Element is present !" << endl;
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