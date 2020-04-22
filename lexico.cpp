#include <iostream>
#include <fstream>
#include <cmath>
#include "lexico.h"

using namespace std;
using namespace lexico;

int LexicoPascalCompiler::GetIndice()
{
  return indice; 
}

void LexicoPascalCompiler::SetIdentificador(string identificador, string token)
{
  vector<string> aux;
  aux.push_back(identificador);
  aux.push_back(token);
  int key = funcao_hash(aux[0]);
  symbol_table[key] = aux;
}

void LexicoPascalCompiler::le_programa(const char file_name[]) //Função que lerá o arquivo inicial
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
    return;
  }

  else cout << "Unable to open file!\n"; 
  programa = "ERRO";
  return;
}

long long LexicoPascalCompiler::funcao_hash(string const& s){ //Função responsável por calcular chave da tabela hash para um string
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

void LexicoPascalCompiler::insere_hash(const char file_element[], const char file_token[])
{
  string lineElem, lineToken; //Guardara cada linha lida do txt

  ifstream felem(file_element), ftoken(file_token); 

  if (felem.is_open() && ftoken.is_open())    //Checa se o txt foi aberto
  {
    int key; //recebe a chave hash calculada para cada elemento
    vector<string> aux; //vetor de string auxiliar para receber o elemento e seu token de cada txt
    int cont_elem = 0, cont_token = 0;
    while (!felem.eof() || !ftoken.eof() ) //enquanto end of file for false continua
    {
    	getline(felem,lineElem); //Leio linha do txt com simbolos resrvados
      getline(ftoken,lineToken); //Leio linha do txt com tokens reservados
		  //cout << "Elemento : " << lineElem << "\t\tToken: " << lineToken << endl;
      if(lineToken == "" || lineElem == "")
      {
        cout << "Erro - Arquivos de elmentos e tokens nao pareados !\nTente novamente" << endl;
        return;
      }
      aux.push_back(lineElem);
      aux.push_back(lineToken);
      key = funcao_hash(aux[0]); //Calcula a chave hash do elemento reservado
      symbol_table[key] = aux; //insere vetor com elemento e token na tabela hash
    }

    felem.close();
    ftoken.close();
  }

  else cout << "Unable to open file!\n"; 

}

void LexicoPascalCompiler::insere_char_values(const char file_chair[])
{
  string lineChair; //Guardara cada linha lida do txt

  ifstream fchair(file_chair); 

  if (fchair.is_open())    //Checa se o txt foi aberto
  {
    int value = 1; //recebe o valor para cada chave
    char aux[1];
    while (!fchair.eof()) //enquanto end of file for false continua
    {
    	getline(fchair,lineChair); //Leio linha do txt com simbolos resrvados
		  //cout << "Elemento : " << lineChair << "\tValue: " << value << endl;
      lineChair.copy(aux,lineChair.size()+1);
      char_value[aux[0]] = value;
      value++;
    }
    fchair.close();
  }

  else cout << "Unable to open file!\n"; 

}

//Checa em qual autômato iremos começar
//String programa é a string que contém o código inteiro
//int init_pos é a posição atual na análise
int LexicoPascalCompiler::checa_automato()
{
  //Guarda o valor da tabela ascii do primeiro caractere
  int valor_ascii = programa[indice];

  //Variável temporária - ignorar
  int automato;

  //Faixa 1-26: A-Z, Faixa 27-52:a-z
  if( (valor_ascii >= 1 && valor_ascii <= 52) )
  {
    automato = 1;
    //Posteriormente, substituiremos a variável automato pela
    //Chamada da função do automato que será utilizado
    //Ex: idenfier_automaton(programa, init_pos)
  }

  //Faixa 53-62: 0-9
  else if(valor_ascii >= 53 && valor_ascii <= 62)
  {
    automato = 2;
  }
  //Faixa 74,75: espaço e enter
  else if(valor_ascii == 74 || valor_ascii == 75)
  {
    automato = 3;
  }
  //Faixa   + 63| - 64| * 65| / 66| : 76| < 68| = 67| > 69
  else if(valor_ascii >= 63 && valor_ascii <= 69 || valor_ascii == 76)
  {
    automato = 4;
  }
  //Faixa 70: {
  else if(valor_ascii == 70)
  {
    automato = 5;
  }
  //Faixa 78: ,
  else if(valor_ascii == 78)
  {
    automato = 6;
  }
  //Faixa 79: ;
  else if(valor_ascii == 79)
  {
    automato = 7;
  }
  //Faixa proibida
  else
  {
    automato = 8;
  }
  return automato;

}
