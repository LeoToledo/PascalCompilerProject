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

//Checa em qual autômato iremos começar
//String programa é a string que contém o código inteiro
//int init_pos é a posição atual na análise
void checa_automato(string programa, int init_pos)
{
  //Guarda o valor da tabela ascii do primeiro caractere
  int valor_ascii = programa[init_pos];

  //Variável temporária - ignorar
  int automato;

  //Faixa 65-90: A-Z, Faixa 97-122:a-z
  if( (valor_ascii >= 65 && valor_ascii <= 90) || (valor_ascii >= 97 && valor_ascii <= 122) )
  {
    automato = 1;
    //Posteriormente, substituiremos a variável automato pela
    //Chamada da função do automato que será utilizado
    //Ex: idenfier_automaton(programa, init_pos)
  }

  //Faixa 48-57: 0-9
  else if(valor_ascii >= 48 && valor_ascii <= 57)
  {
    automato = 2;
  }
  //Faixa 13,32: espaço e enter
  else if(valor_ascii == 13 || valor_ascii == 32)
  {
    automato = 3;
  }
  //Faixa 42,43,45,47,58,60,61,62: *,+,-,/,:,<,=,>
  else if(valor_ascii == 42 || valor_ascii == 43 || valor_ascii == 45 || valor_ascii == 47
          || valor_ascii == 58 || valor_ascii == 60 || valor_ascii == 61 || valor_ascii == 62)
  {
    automato = 4;
  }
  //Faixa 123: {
  else if(valor_ascii == 123)
  {
    automato = 5;
  }
  //Faixa 44: ,
  else if(valor_ascii == 44)
  {
    automato = 6;
  }
  //Faixa 59: ;
  else if(valor_ascii == 59)
  {
    automato = 7;
  }
  //Faixa proibida
  else
  {
    automato = 8
  }

}
