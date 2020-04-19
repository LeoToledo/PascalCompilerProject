#include<iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
  string line[];
  ifstream myfile ("init_code.txt"); 

  if (myfile.is_open())    //Checa se a pasta foi aberta com sucesso
  {
	int i = 0;
    while (! myfile.eof() ) //enquanto end of file for false continua
    {
    	getline (myfile,line[i]); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha
		i++;
    }
	for(i = 0; i < len(i); i++)
	{
		cout << line << endl;
	}
	
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}