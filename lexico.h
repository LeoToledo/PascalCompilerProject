#ifndef LEXICO_H
#define LEXICO_H

#include <string>
#include <unordered_map>
#include <vector>

namespace lexico
{
    class LexicoPascalCompiler
    {
        private:
            //Tabela hash que contém os identificadores reservados da linguagem P--
            std::unordered_map<int, std::vector<std::string>> symbol_table;
            //Tabela hash que contém os chars com seu respectivo valor organizado
            std::unordered_map<char, int> char_value;
            //Variável que guarda o indice atual de leitura da string programa
            int indice;
        public:
            //String que guardo o programa lido do txt
            std::string programa ;
            //Retorna o indice atual de leitura do programa
            int GetIndice();
            //Acrescenta um identificador na tabela de identificadores
            void SetIdentificador(std::string identificador, std::string token);
            //Retorna a chave de um identificador presente na tabela
            //Método que lê o programa em txt passando seu enderço com o nome por parâmetro
            //e salvando na string programa
            void le_programa(const char file_name[]);
            //Método que resecebe o nome do txt com os identificadores reservados em cada linha
            //e outro txt com seus respectivos tokens, inserindo os mesmos na tabela hash de identificadores
            void insere_hash(const char file_element[], const char file_token[]);
            //Método que recebe uma string e é calculado sua chave na tabela hash de identificadores
            long long funcao_hash(std::string const& s);
            //Método que recebe um txt com um char permitido (na linguagem) em cada linha
            //e é inserido na tabela hash de chairs
            void insere_char_values(const char file_chair[]);
            //Método que checa qual automato deve ser utilizado de acordo com o indice atual de leitura
            //do programa
            int checa_automato();

    };
}

#endif