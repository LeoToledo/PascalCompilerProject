#ifndef SINTATICO_H
#define SINTATICO_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <vector>

using namespace std;


namespace sintatico
{
    class SintaticoPascalCompiler
    {
        private:
            

            //Variável que guarda a posição corrente sendo analisada na fase sintática
            int current_pos = 0;
            
        public:
            string symbol="";

            vector<string> simbolo;
            vector<string> buffer_erro;   
            vector<int> linha_atual;

            //Pega a posição atual do simbolo sendo analisado
            int get_current_pos();
            //Avança a posição atual do símbolo sendo analisado
            void add_current_pos(int profundidade);

            //Pega o proximo simbolo sendo analisado
            string get_next_simb();

            //Seta o simbolo atual sendo analisado
            void set_simbolo(vector<string> simb);
            //Pega o valor do simbolo atual sendo analisado
            vector<string> get_simbolo()
            {
                return simbolo;
            }

            //Função que inicializa o analisador sintático
            void ASD();

            //Implementação do grafo sintático da regra de programa
            //Todos os métodos "procedimento" tem a mesma função
            //1. <programa> ::= program ident ; <corpo>
            void procedimento_programa(int profundidade);

            //2. <corpo> ::= <dc> begin <comandos> end
            void procedimento_corpo(int profundidade);

            //3. <dc> ::= <dc_c> <dc_v> <dc_p>
            void procedimento_dc(int profundidade);

            //4. <dc_c> ::= const ident = <numero> ; <dc_c> | λ
            void procedimento_dc_c(int profundidade);

            //5. <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
            void procedimento_dc_v(int profundidade);

            //9. <dc_p> ::= precedure ident <parametros> ; <corpo> <dc_p> | λ
            void procedimento_dc_p(int profundidade);

            //6. <tipo_var> ::= real | integer
            void procedimento_tipo_var(int profundidade);

            //7. <variaveis> ::= ident <mais_var> com
            //8. <mais_var> ::= , <variaveis> | λ
            //ident ,variaveis
            void procedimento_variaveis(int profundidade);

            //10- <parametros> ::= ( <lista_par> ) | lambda
            void procedimento_parametros(int profundidade);

            //11- <lista_par> ::= <variaveis> : <tipo_var> <mais_par>
            //12 -<mais_par> ::= ; <lista_par> | lambda
            void procedimento_lista_par(int profundidade);

            //13. <corpo_p> ::= <dc_loc> begin <comandos> end ; com
            //14. <dc_loc> ::= <dc_v>
            void procedimento_corpo_p(int profundidade);

            //15. <lista_arg> ::= ( <argumentos> ) | λ
            void procedimento_lista_arg(int profundidade);
            //int procedimento_lista_arg(simbolo){
            //    if(simbolo == "("){
            //        simbolo = get_next_simb(posicao_corrente);
            //        posicao_corrente = procedimento_argumentos(simbolo);
            //        simbolo = get_next_simb(posicao_corrente);
            //        if(simbolo == ")"){
            //            return posicao_corrente;
            //        }else{
            //            ERRO - não é igual a ")"
            //        }
            //    }else{
            //        return posicao_corrente; //se não for "(", sai da função (lambda)
            //    }
            //}

            //16. <argumentos> ::= ident <mais_ident> com
            //17. <mais_ident> ::= ; <argumentos> | λ
            void procedimento_argumentos(int profundidade);


            //18. <pfalsa> ::= else <cmd> | λ
            void procedimento_pfalsa(int profundidade);
            //int procedimento_pfalsa(simbolo){
            //    if(simbolo == "else"){
            //        simbolo = get_next_simb(posicao_corrente);
            //        posicao_corrente = procedimento_cmd(simbolo);
            //        return posicao_corrente;
            //    }else{
            //        return posicao_corrente; //se não for "else", sai da função (lambda)
            //    }
            //}
            //19. <comandos> ::= <cmd> ; <comandos> | λ
            void procedimento_comandos(int profundidade);

            //15. <lista_arg> ::= ( <argumentos> ) | λ
            //18. <pfalsa> ::= else <cmd> | λ
            //20  <cmd> ::= read (<variaveis>) |
            //                write (<variaveis>) |
            //                while (<condicao>) do <cmd> |
            //                if <condicao> then <cmd> <pfalsa> |
            //                ident <cmd_aux> |
            //                begin <comandos> end |
            //                for <variaveis> := numero_int to numero_int do
            //    <cmd_aux’> ::= := <expressao> | <lista_arg>
            void procedimento_cmd(int profundidade);

            //21. <condicao> ::= <expressao> <relacao> <expressao>
            //22. <relacao> ::= = | <> | >= | <= | > | <
            //23. <expressao> ::= <termo> <outros_termos>
            void procedimento_condicao(int profundidade);

            //23. <expressao> ::= <termo> <outros_termos>
            void procedimento_expressao(int profundidade);

            //24. <op_un> ::= + | - | λ com
            //27. <termo> ::= <op_un> <fator> <mais_fatores>
            void procedimento_termo(int profundidade);

            //25. <outros_termos> ::= <op_ad><termo><outros_termos> | λ com
            //26. <op_ad> ::= + | -
            void procedimento_outros_termos(int profundidade);

            //28. <mais_fatores> ::= <op_mul> <fator> <mais_fatores> | λ com
            //29. <op_mul> ::= * | /
            void procedimento_mais_fatores(int profundidade);

            //30. <fator> ::= ident | <numero> | ( <expressao> )
            //31. <numero> ::= numero_int | numero_real
            //23. <expressao> ::= <termo> <outros_termos>
            void procedimento_fator(int profundidade);
            
            //Procedimento para tratamento de erros
            void procedimento_ERRO(vector<string> seguidor, vector<string> seguidor_pai, int linha_atual);

            

    };
}

#endif

