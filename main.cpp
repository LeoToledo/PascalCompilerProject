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
        cout << "Programa:\n\n";
        lexico.le_programa(argv[1]);
        if (lexico.programa == "ERRO")
        {
            return -1;
        }
        else
        {
            cout << lexico.programa << "\n\nComecou:\n\n";
            lexico.insere_hash("simbolos_reservados.txt","tokens_reservados.txt");
            lexico.insere_char_values("chars.txt");
            /*for (int i = 0; i < lexico.programa.size(); i++)
            {
                cout << lexico.checa_automato() << endl;
            }*/
            while (lexico.indice < lexico.programa.size())
            {
                lexico.checa_automato();
            }
            if(lexico.parenteses_bool)
                    cout << "Erro - Parenteses aberto !";
            for (int i = 0; i < lexico.buffer_id.size(); i++)
            {
                cout << "\n" << lexico.buffer_id[i] << ", " << lexico.buffer_token[i];
            }
            cout << endl;
        }
    }

    return 0;
}