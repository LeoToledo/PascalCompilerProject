#include<iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string le_arquivo(const char file_name[]);  //Função que lerá o arquivo inicial

int main(int argc, char const *argv[])
{
  if(argc < 2)
  {
    cout << "Argument not passed !" << endl;
    return -1;
  }
  else
  {
    string programa = le_arquivo(argv[1]);
    if(programa=="ERRO")
    {
      return -1;
    }
    else
    {
      cout << programa << endl;
    }
    
  }
  
  return 0;
}

string le_arquivo(const char file_name[])
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