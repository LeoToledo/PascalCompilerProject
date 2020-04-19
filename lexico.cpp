#include<iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string le_arquivo(const string &file_name);  //Função que lerá o arquivo inicial

int main () 
{
  string programa = le_arquivo("meu_programa.txt");
  cout << programa << endl;
  return 0;
}

string le_arquivo(const string &file_name)
{
  //Convertendo a string para char
  char file_nameAux[file_name.size() + 1];
  file_name.copy(file_nameAux, file_name.size() + 1);
  file_nameAux[file_name.size()] = '\0';

  vector<string> line;  //String que lerá o arquivo
  string programa = ""; //String que guarda o programa inteiro em um só elemento
  string lineAux;

  
  ifstream myfile (file_nameAux); 

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

  else cout << "Unable to open file"; 
  return "ERRO"; //Retorna -1 caso dê errado
}