#include <iostream>
#include "lexico.h"
#include "sintatico.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace lexico;
using namespace sintatico;

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
        SintaticoPascalCompiler sintatico;

        lexico.le_programa(argv[1]);
        if (lexico.programa == "ERRO")
        {
            return -1;
        }
        else
        {
            //cout << lexico.programa << "\n\nComecou:\n\n";
            
            lexico.insere_hash("simbolos_reservados.txt","tokens_reservados.txt");
            
            lexico.insere_char_values("chars.txt");
            
            /*for (int i = 0; i < lexico.programa.size(); i++)
            {
                cout << lexico.checa_automato() << endl;
            }*/

            vector<string> simbolo; 
            int i = 0;

            //Loop que percorre o código de entrada e chama a análise léxica
            while (lexico.indice < lexico.programa.size())
            {   
                //Variável para checar se o simbolo a ser analisado mudou na iteração atual
                int size_anterior = lexico.buffer_id.size();
                lexico.checa_automato();

                //Condicional para pegar um novo simbolo a cada iteração
                if(lexico.buffer_id.size() != size_anterior)
                {
                    sintatico.simbolo.push_back(lexico.buffer_token[i]);
                    sintatico.simb_msg.push_back(lexico.buffer_id[i]);
                    sintatico.linha_atual.push_back(lexico.linha_atual);
                    //cout << sintatico.simbolo[i] << " " << sintatico.linha_atual[i] << endl;
                    i++;
                } 
            }

            //Escrevendo no arquivo de saida do lexico
            ofstream outputFile_lexico;
            outputFile_lexico.open("output_lexico.txt");
            for(int i = 0; i < lexico.buffer_id.size(); i++)
            {
                outputFile_lexico << lexico.buffer_id[i] << ", " << lexico.buffer_token[i] << endl;
            }
            
            sintatico.ASD();
            
            //Escrevendo no arquivo de saida do sintatico
            ofstream outputFile_sintatico;
            outputFile_sintatico.open("output_sintatico.txt");
            cout << "\n\nTXT SAIDA" << endl;
            for (int i = 0; i < sintatico.buffer_erro.size(); i++)
            {
                cout << sintatico.buffer_erro[i] << endl;
                outputFile_sintatico << sintatico.buffer_erro[i] << endl;
            }
            if(sintatico.buffer_erro.size() == 0)
            {
                cout << "Sucesso !" << endl;
                outputFile_sintatico << "Sucesso !" << endl;
            }
        }
    }

    return 0;
}