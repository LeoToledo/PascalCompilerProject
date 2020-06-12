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
            vector<string> simbolo; 
            

            //Variável que guarda a posição corrente sendo analisada na fase sintática
            int current_pos = 0;
            
        public:
            string symbol="";   

            //Pega a posição atual do simbolo sendo analisado
            int get_current_pos();
            //Avança a posição atual do símbolo sendo analisado
            void add_current_pos();

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
            void ASD(vector<string> symbol);

            //Implementação do grafo sintático da regra de programa
            //Todos os métodos "procedimento" tem a mesma função
            //1. <programa> ::= program ident ; <corpo>
            void procedimento_programa();

            //2. <corpo> ::= <dc> begin <comandos> end
            void procedimento_corpo();

            //3. <dc> ::= <dc_c> <dc_v> <dc_p>
            void procedimento_dc();

            //4. <dc_c> ::= const ident = <numero> ; <dc_c> | λ
            void procedimento_dc_c();

            //5. <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
            void procedimento_dc_v();

            //9. <dc_p> ::= precedure ident <parametros> ; <corpo> <dc_p> | λ
            void procedimento_dc_p();

            //6. <tipo_var> ::= real | integer
            void procedimento_tipo_var();

            //7. <variaveis> ::= ident <mais_var> com
            //8. <mais_var> ::= , <variaveis> | λ
            //ident ,variaveis
            void procedimento_variaveis();

            //10- <parametros> ::= ( <lista_par> ) | lambda
            void procedimento_parametros();

            //11- <lista_par> ::= <variaveis> : <tipo_var> <mais_par>
            //12 -<mais_par> ::= ; <lista_par> | lambda
            void procedimento_lista_par();

            //13. <corpo_p> ::= <dc_loc> begin <comandos> end ; com
            //14. <dc_loc> ::= <dc_v>
            void procedimento_corpo_p();

            //15. <lista_arg> ::= ( <argumentos> ) | λ
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
            void procedimento_argumentos();


            //18. <pfalsa> ::= else <cmd> | λ
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
            void procedimento_comandos();

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
            void procedimento_cmd();

            //21. <condicao> ::= <expressao> <relacao> <expressao>
            //22. <relacao> ::= = | <> | >= | <= | > | <
            //23. <expressao> ::= <termo> <outros_termos>
            void procedimento_condicao();

            //23. <expressao> ::= <termo> <outros_termos>
            void procedimento_expressao();

            //24. <op_un> ::= + | - | λ com
            //27. <termo> ::= <op_un> <fator> <mais_fatores>
            void procedimento_termo();

            //25. <outros_termos> ::= <op_ad><termo><outros_termos> | λ com
            //26. <op_ad> ::= + | -
            void procedimento_outros_termos();

            //28. <mais_fatores> ::= <op_mul> <fator> <mais_fatores> | λ com
            //29. <op_mul> ::= * | /
            void procedimento_mais_fatores();

            //30. <fator> ::= ident | <numero> | ( <expressao> )
            //31. <numero> ::= numero_int | numero_real
            //23. <expressao> ::= <termo> <outros_termos>
            void procedimento_fator();

            

    };
}

#endif


