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
            //cout << lexico.programa << endl;
            lexico.insere_hash("simbolos_reservados.txt","tokens_reservados.txt");
            lexico.insere_char_values("chars.txt");

            for(int j = 0; j < 5; j++)
            {
                lexico.checa_automato();
                
            }
            /*   
            for (int i = 0; i < lexico.buffer.size(); i+=1)
            {
                cout << "\n" << lexico.buffer[i]; " ";
            }
            cout << "\n" << endl;        
            */
        }
    } 
    return 0;
}