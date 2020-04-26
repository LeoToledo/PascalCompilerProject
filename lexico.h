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
            
        public:
            //Variável que guarda o indice atual de leitura da string programa
            int indice = 0;

            //Variável que diz a linha atual que se está analisando 
            int linha_atual = 1;

            //String que guardo o programa lido do txt
            std::string programa ;

            //Buffer que guarda os elementos ja identificados
            std::vector<std::string> buffer_id;

            //Buffer que guarda os tokens dos elementos identificados
            std::vector<std::string> buffer_token;

            //Variavel que e true se tiver parenteses abertos
            bool parenteses_bool = false;

            //Retorna o indice atual de leitura do programa
            int GetIndice();

            //A partir de um identificador como parâmetro (ex:program) retorna vetor de string com o identificador
            //na posicao 0 e o seu token na posicao 1. Se o identificador nao existe na tabela retorna um vetor com "ERRO" na posicao 0
            std::vector<std::string> GetIdentificador(std::string identificador);

            //Acrescenta um identificador na tabela de identificadores passando como parametro o identificador
            //e seu respectivo token
            void SetIdentificador(std::string identificador, std::string token);

            //Retorna o valor de um char na nossa configuracao de valores (tabela hash char_value)
            int GetChar(char c);

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
            //Método do autômato que reconhece números
            int number_automaton();
            //Método do autômato que reconhece identificadores
            int indentificador_automaton();
            //Método do autônoma de ;
            int pont_virg_automaton();
            //Método do autônomo de simbolos proibidos
            int proibido_automaton();
            //Método autômato para sinais 
            int sinal_automaton();
            //Método autômato para parênteses
            int parentese_automaton();
            //Método para autômato de comentário
            int comentario_automaton();


    };
}

#endif