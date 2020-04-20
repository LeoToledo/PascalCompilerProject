#include <iostream>
#include <fstream>
#include <cmath>
#include "lexico.h"

using namespace std;

string le_arquivo(const char file_name[]) //Função que lerá o arquivo inicial
{
  string programa = ""; //String que guarda o programa inteiro em um só elemento
  string lineAux;

  
  ifstream myfile (file_name); 

  if (myfile.is_open())    //Checa se a pasta foi aberta com sucesso
  {
    while (! myfile.eof() ) //enquanto end of file for false continua
    {
    	getline (myfile,lineAux); // como foi aberto em modo texto(padrão) e não binário(ios::bin) pega cada linha
		  programa += lineAux;
    }

    myfile.close();
    return programa;
  }

  else cout << "Unable to open file!\n"; 
  return "ERRO"; //Retorna -1 caso dê errado
}

long long funcao_hash(string const& s){ //Função responsável por calcular chave da tabela hash para um string
    int p = 13;
    long long m = pow(18, 3);
    long long hash;


    for(int i = 0; i < s.size() ; i++){
        //cout << int(s[i]) << " ";
        hash = s[i]*pow(p, i);
        

    }
    //cout << "\n" << hash;
    hash = hash % m;
    return hash;
}