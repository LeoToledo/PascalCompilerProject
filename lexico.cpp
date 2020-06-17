#include <iostream>
#include <fstream>
#include <cmath>
#include "lexico.h"
#include <typeinfo>

using namespace std;
using namespace lexico;

int LexicoPascalCompiler::GetIndice()
{
  return indice;
}

std::vector<std::string> LexicoPascalCompiler::GetIdentificador(std::string identificador)
{
  vector<string> aux;
  int key = funcao_hash(identificador);
  if (symbol_table.find(key) != symbol_table.end())
  {
    aux = symbol_table.at(key);
    return aux;
  }
  aux.push_back("ERRO");
  return aux;
}

void LexicoPascalCompiler::SetIdentificador(string identificador, string token)
{
  vector<string> aux;
  aux.push_back(identificador);
  aux.push_back(token);
  int key = funcao_hash(aux[0]);
  symbol_table[key] = aux;
}

int LexicoPascalCompiler::GetChar(char c)
{
  int value;
  if (char_value.find(c) != char_value.end())
  {
    value = char_value.at(c);
    return value;
  }
  value = -1; //Elemento nao existe
  return value;
}

void LexicoPascalCompiler::le_programa(const char file_name[]) //Função que lerá o arquivo inicial
{
  programa = ""; //String que guarda o programa inteiro em um só elemento
  string lineAux;

  ifstream myfile(file_name);

  if (myfile.is_open()) //Checa se a pasta foi aberta com sucesso
  {
    while (!myfile.eof()) //enquanto end of file for false continua
    {
      getline(myfile, lineAux); // como foi aberto em modo texto(padrão) e não binário(ios::bin) pega cada linha
      //cout << lineAux;
      programa += lineAux + "\n";
    }

    myfile.close();
    return;
  }

  else
    cout << "Unable to open file!\n";
  programa = "ERRO";
  return;
}

long long LexicoPascalCompiler::funcao_hash(string const &s)
{ //Função responsável por calcular chave da tabela hash para um string
  int p = 13;
  long long m = pow(18, 3);
  long long hash = 0;

  for (int i = 0; i < s.size(); i++)
  {
    //cout << int(s[i]) << " ";
    hash += s[i] * pow(p, i);
  }
  //cout << "\n" << hash;
  hash = hash % m;
  return hash;
}

void LexicoPascalCompiler::insere_hash(const char file_element[], const char file_token[])
{
  string lineElem, lineToken; //Guardara cada linha lida do txt

  ifstream felem(file_element), ftoken(file_token);

  if (felem.is_open() && ftoken.is_open()) //Checa se o txt foi aberto
  {
    int key;            //recebe a chave hash calculada para cada elemento
    vector<string> aux; //vetor de string auxiliar para receber o elemento e seu token de cada txt
    int cont = 0;
    while (!felem.eof() || !ftoken.eof()) //enquanto end of file for false continua
    {
      getline(felem, lineElem);   //Leio linha do txt com simbolos resrvados
      getline(ftoken, lineToken); //Leio linha do txt com tokens reservados
                                  //cout << "Elemento : " << lineElem << "\t\tToken: " << lineToken << endl;
      if (lineToken == "" || lineElem == "")
      {
        cout << "Erro - Arquivos de elmentos e tokens nao pareados !\nTente novamente" << endl;
        return;
      }
      aux.push_back(lineElem);
      aux.push_back(lineToken);
      key = funcao_hash(aux[0]); //Calcula a chave hash do elemento reservado
      symbol_table[key] = aux;   //insere vetor com elemento e token na tabela hash
      aux.clear();
    }

    felem.close();
    ftoken.close();
  }

  else
    cout << "Unable to open file!\n";
}

void LexicoPascalCompiler::insere_char_values(const char file_chair[])
{
  string lineChair; //Guardara cada linha lida do txt

  ifstream fchair(file_chair);

  if (fchair.is_open()) //Checa se o txt foi aberto
  {
    int value = 1; //recebe o valor para cada chave
    //char aux[1];
    while (!fchair.eof()) //enquanto end of file for false continua
    {
      getline(fchair, lineChair); //Leio linha do txt com simbolos resrvados
      if(lineChair=="enter")
      {
        lineChair = "\n";
      }
      if(lineChair=="tab")
      {
        lineChair = "\t";
      }
      if(lineChair == "cr")
      {
        lineChair = "\r";
      }
      char_value[lineChair[0]] = value;
      //cout << value << " " << lineChair << endl;
      value++;
    }
    fchair.close();
  }

  else
    cout << "Unable to open file!\n";
}

//Checa em qual autômato iremos começar
//String programa é a string que contém o código inteiro
//int init_pos é a posição atual na análise
void LexicoPascalCompiler::checa_automato()
{
  //Guarda o valor da tabela ascii do primeiro caractere
  int valor_ascii = GetChar(programa[indice]);
  int real_val_asci = programa[indice];
  //cout << "asci: " << valor_ascii << " real asci: " << real_val_asci << " char: " << programa[indice] << endl;

  //Autômato de tabs, espaços e enters
  if((valor_ascii >= 74 && valor_ascii <= 76) || valor_ascii == 81) 
  {
    if(valor_ascii == 75)
    {
      linha_atual++;
    }
    this->indice++;
  }

  
  //Faixa 1-26: A-Z, Faixa 27-52:a-z
  else if ((valor_ascii >= 1 && valor_ascii <= 52))
  {
    indentificador_automaton();
    //Posteriormente, substituiremos a variável automato pela
    //Chamada da função do automato que será utilizado
    //Ex: idenfier_automaton(programa, init_pos)
  }

  //Faixa 53-62: 0-9
  else if (valor_ascii >= 53 && valor_ascii <= 62)
  {
    number_automaton();
  }
  //Faixa   + 63| - 64| * 65| / 66| < 68| = 67| > 69| : 77| . 78| , 79|
  else if ((valor_ascii >= 63 && valor_ascii <= 69) || (valor_ascii >= 77 && valor_ascii <= 79))
  {
    sinal_automaton();
  }
  //Faixa 70-71: {} Automato de comentario
  else if (valor_ascii == 70 || valor_ascii == 71)
  {
    comentario_automaton();
  }
  //Faixa 70: ()
  else if (valor_ascii == 72 || valor_ascii == 73)
  {
    parentese_automaton();
  }
  //Faixa 79: ;
  else if (valor_ascii == 80)
  {
    pont_virg_automaton();
  }
  //Faixa proibida
  else
  { 
    proibido_automaton();
  }
}

int LexicoPascalCompiler::number_automaton()
{
  //Define um vetor de chars para guardar a sentença sendo formada
  string buffer_aux = "";
  string real_aux = "";
  bool real = false;
  //Percorre até chegar no final do programa
  while(indice != (programa.size()) )
  { 
    //Se for um digito
    if(GetChar(programa[indice]) >= 53 && GetChar(programa[indice]) <= 62 && !real)
    { 
      //Adiciona o dígito atual no buffer
      buffer_aux += programa[indice];
      this->indice++;
    } 
    //Caso o número seja inteiro e tenha terminado
    //+ - * / = < > { } ( ) space enter tab : . ; (nada)
    else if( ( GetChar(programa[indice]) >= 63 && GetChar(programa[indice]) <= 78 ) || ( GetChar(programa[indice]) >= 80 && GetChar(programa[indice]) <= 81 ) )
    { 
      if(real_aux.size() > 37)
        {
          string aux = """Numero com casas decimais excedentes na linha " + to_string(linha_atual);
          this->buffer_id.push_back(aux);
          this->buffer_token.push_back("Erro_Lexico");
          return -2;
        }
      break;
    }
    //Caso seja um número com vírgula
    else if(GetChar(programa[indice]) == 79)
    {
      if(real) //Testa para ver se nao esta colocando mais de um ponto
      {
        break;
      }
      real = true;
      buffer_aux += programa[indice];
      this->indice++;
    }
    else if(real) //Continua checando por números depois da vírgula
    { 
      if(GetChar(programa[indice]) >= 53 && GetChar(programa[indice]) <= 62)
      {
        //Adiciona o dígito atual depois da virgula no buffer
        buffer_aux += programa[indice];
        real_aux += programa[indice];
        this->indice++;
      }
      //Caso tenha um erro depois da vírgula
      else
      {
        //Adiciona o erro no buffer_aux
        buffer_aux += programa[indice];
        //Forma a mensagem de erro
        string aux = """Numero real " + buffer_aux + " incorreto na linha " + to_string(linha_atual);
        //Adiciona a mensagem de erro no buffer de id e de token
        this->buffer_id.push_back(aux);
        this->buffer_token.push_back("Erro_Lexico");
        this->indice++;
        return -2;
      }
    }
    //Caso tenha um erro no número inteiro
    else
    {   
        //Adiciona o erro no buffer_aux
        buffer_aux += programa[indice];
        //Forma a mensagem de erro
        string aux = """Numero inteiro " +buffer_aux + " incorreto na linha " + to_string(linha_atual);
        //Adiciona a mensagem de erro no buffer de id e de token
        this->buffer_id.push_back(aux);
        this->buffer_token.push_back("Erro_Lexico");
        this->indice++;
        return -2;
    }
  }

  //Passando do buffer_aux para o buffer do objeto
  if(real)
  {
    this->buffer_id.push_back(buffer_aux);
    this->buffer_token.push_back("numero_real"); 
  }
  else
  {
    this->buffer_id.push_back(buffer_aux);
    this->buffer_token.push_back("numero_int"); 
  }

  return 1;
}

int LexicoPascalCompiler::indentificador_automaton()
{
  string aux_string = "";
  int aux;

  while (this->indice < programa.size())
  { //enquanto a string programa não estiver no fim
    aux = GetChar(programa[indice]);
    if (aux >= 1 && aux <= 62)
    {                             //se o char na posição n for uma letra maiuscula, minuscula ou numero
      aux_string += programa[indice]; //salva as letras do identificador no auxiliar
      this->indice++;
    }
    else if (aux >= 63 && aux <= 81)
    { //se o char na posição n for um caractere reservado
      vector<string> res;
      res = GetIdentificador(aux_string);
      if(res[0] == "ERRO") //identificador nao existe
      {
        if(aux_string.size() > 25)
        {
          string aux = """Identificador " + aux_string + " com tamanho excedido na linha " + to_string(linha_atual);
          this->buffer_id.push_back(aux);
          this->buffer_token.push_back("Erro_Lexico");
          return -2;
        }
        buffer_id.push_back(aux_string);
        buffer_token.push_back("id");
      }
      else
      {
        buffer_id.push_back(res[0]);
        buffer_token.push_back(res[1]);
      }
      return 1;
    }
    else
    {
      vector<string> res;
      res = GetIdentificador(aux_string);
      if(res[0] == "ERRO") //identificador nao existe
      {
        //aux_string += programa[indice];
        //buffer_id.push_back(aux_string);
        //buffer_token.push_back("id");
      }
      else
      {
        buffer_id.push_back(res[0]);
        buffer_token.push_back(res[1]);
      }
      //Adiciona o erro no buffer_aux
        aux_string += programa[indice];
        //Forma a mensagem de erro
        string aux = """Variavel " +aux_string + " incorreta na linha " + to_string(linha_atual);
        //Adiciona a mensagem de erro no buffer de id e de token
        this->buffer_id.push_back(aux);
        this->buffer_token.push_back("Erro_Lexico");
        return -2;
    }
  }
}

int LexicoPascalCompiler::pont_virg_automaton()
{
  this->indice++;
  //cout << "---- " << programa[indice] << "----- ";
  string aux_string = "";
  int aux = GetChar(programa[indice]);
  if( (aux >= 74 && aux <= 76) || aux == 70 || aux == 81)
  { 
    int aux;
    aux_string += programa[indice-1];
    buffer_id.push_back(aux_string);
    vector<string> res;
    res = GetIdentificador(aux_string);
    buffer_token.push_back(res[1]);
    return 1;
  }
  else
  {
    //Adiciona o erro no buffer_aux
        aux_string += programa[indice];
        //Forma a mensagem de erro
        string aux = "Ponto e virgula incorreto na linha " + to_string(linha_atual);
        //Adiciona a mensagem de erro no buffer de id e de token
        this->buffer_id.push_back(aux);
        this->buffer_token.push_back("Erro_Lexico");
    return -2;
  }
  
  
}

int LexicoPascalCompiler::proibido_automaton()
{
  string aux = "";
  aux += programa[indice];
  
  //Só conta erro solto no caso dos erros específicos não tratados
  if(GetChar(programa[indice-1]) >= 63 && GetChar(programa[indice-1] <= 81))
  { 
    string temp = "Caractere " +aux + " invalido na linha " + to_string(linha_atual);
    buffer_id.push_back(temp);
    buffer_token.push_back("Erro_Lexico");
    indice++;
    return -1;
  }
  else
  {
    indice++;
    return -1;
  }
  
  
  
}

int LexicoPascalCompiler::sinal_automaton()
{
  string aux_string = "";
  aux_string += programa[indice];
  vector<string> res;
  int aux = GetChar(programa[indice]);
  if(aux >= 63 && aux <= 67 || aux == 78 || aux == 79) // + - * / = . ,
  {
    res = GetIdentificador(aux_string);
    buffer_id.push_back(res[0]);
    buffer_token.push_back(res[1]);
    indice++;
    return 1;
  }
  else if(aux == 68) // <
  {
    indice++;
    int aux2 = GetChar(programa[indice]);
    if(aux2 == 67 || aux2 == 69)// <= ou <>
      aux_string += programa[indice];
    else
      indice--;
    res = GetIdentificador(aux_string);
    buffer_id.push_back(res[0]);
    buffer_token.push_back(res[1]);
    indice++;
    return 1;
  }
  else if(aux == 69) // >
  {
    indice++;
    int aux2 = GetChar(programa[indice]);
    if(aux2 == 67)// >=
      aux_string += programa[indice];
    else
      indice--;
    res = GetIdentificador(aux_string);
    buffer_id.push_back(res[0]);
    buffer_token.push_back(res[1]);
    indice++;
    return 1;
  }
  else if(aux == 77)// :
  {
    indice++;
    int aux2 = GetChar(programa[indice]);
    if(aux2 == 67)// :=
      aux_string += programa[indice];
    else
      indice--;
    res = GetIdentificador(aux_string);
    buffer_id.push_back(res[0]);
    buffer_token.push_back(res[1]);
    indice++;
    return 1;
  }
  
}

int LexicoPascalCompiler::parentese_automaton()
{
  string aux_string = "";
  aux_string += programa[indice];
  vector<string> res;
  int aux = GetChar(programa[indice]);
  if(aux == 72)
    parenteses_bool = true;
  else
    parenteses_bool = false;
  res = GetIdentificador(aux_string);
  buffer_id.push_back(res[0]);
  buffer_token.push_back(res[1]);
  indice++;
  return 1;
}

int LexicoPascalCompiler::comentario_automaton()
{ 
  while(GetChar(programa[indice]) != 71)
  {
    indice++;
    if(indice > programa.size())
    {
      string temp = "Comentario sem fechar na linha " + to_string(linha_atual);
      buffer_id.push_back(temp);
      buffer_token.push_back("Erro_Lexico");
      break;
    }
  }
  indice++;
  return 1;
}
