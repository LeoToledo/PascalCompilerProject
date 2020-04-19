#include<iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main () {
  vector<string> line;  //String que lerá o arquivo
  string programa = ""; //String que guarda o programa inteiro em um só elemento
  string lineAux;

  ifstream myfile ("meu_programa.txt"); 

  if (myfile.is_open())    //Checa se a pasta foi aberta com sucesso
  {
    while (! myfile.eof() ) //enquanto end of file for false continua
    {
    	getline (myfile,lineAux); // como foi aberto em modo texto(padrão) e não binário(ios::bin) pega cada linha
		  programa += lineAux;
    }

	cout << programa << endl;

    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}