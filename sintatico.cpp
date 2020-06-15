#include <iostream>
#include <fstream>
#include <cmath>
#include "lexico.h"
#include "sintatico.h"
#include <typeinfo>
#include <vector>
#include <algorithm> 

using namespace std;
using namespace lexico;
using namespace sintatico;

void SintaticoPascalCompiler::set_simbolo(vector<string> simb)
{
    for (int i = 0; i < simb.size(); i++)
    {
        simbolo.push_back(simb[i]);
    }
}

void SintaticoPascalCompiler::add_current_pos(int profundidade)
{
    current_pos++;
    cout << simbolo[current_pos] << " " << profundidade << endl;
}
int SintaticoPascalCompiler::get_current_pos()
{
    return current_pos;
}

void SintaticoPascalCompiler::ASD()
{
    int profundidade = 0;
    procedimento_programa(profundidade);
}

string SintaticoPascalCompiler::get_next_simb()
{
    //add_current_pos(profundidade);
    return simbolo[current_pos];
}

void SintaticoPascalCompiler::procedimento_programa(int profundidade)
{
    cout << "--- procedimento_programa() --- " << profundidade << endl;
    profundidade++;

    if (simbolo[current_pos] == "program")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == "ident")
        {
            add_current_pos(profundidade);

            if (simbolo[current_pos] == ";")
            {
                add_current_pos(profundidade);

                procedimento_corpo(profundidade);


                if (simbolo[current_pos] == ".")
                {
                    printf("Sucesso");
                    return;
                }
                else
                {
                    cout << "Erro no procedimento_programa, não é . e sim:   " << simbolo[current_pos] << endl;
                }
            }
            else
            {
                cout << "Erro no procedimento_programa, não é ; e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_programa, não é ident e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        cout << "Erro no procedimento_programa, não é program e sim:   " << simbolo[current_pos] << endl;
    }
}

//2. <corpo> ::= <dc> begin <comandos> end
void SintaticoPascalCompiler::procedimento_corpo(int profundidade)
{
    cout << "--- procedimento_corpo() ---" << profundidade << endl;
    profundidade++;
    procedimento_dc(profundidade);

    if (simbolo[current_pos] == "begin")
    {
        add_current_pos(profundidade);

        procedimento_comandos(profundidade);

        if (simbolo[current_pos] == "end")
        {
            add_current_pos(profundidade);
            return;
        }
        else
        {
            cout << "Erro no procedimento_corpo, não é end e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        cout << "Erro no procedimento_corpo, não é begin e sim:   " << simbolo[current_pos] << endl;
    }
}

//3. <dc> ::= <dc_c> <dc_v> <dc_p>
void SintaticoPascalCompiler::procedimento_dc(int profundidade)
{
    cout << "--- procedimento_dc() ---" << profundidade << endl;
    profundidade++;
    procedimento_dc_c(profundidade);
    //add_current_pos(profundidade);
    procedimento_dc_v(profundidade);
    //add_current_pos(profundidade);
    procedimento_dc_p(profundidade);
}

//4. <dc_c> ::= const ident = <numero> ; <dc_c> | λ
void SintaticoPascalCompiler::procedimento_dc_c(int profundidade)
{
    cout << "--- procedimento_dc_c() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "const")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == "ident")
        {
            add_current_pos(profundidade);

            if (simbolo[current_pos] == "=")
            {
                add_current_pos(profundidade);

                procedimento_fator(profundidade);

                if (simbolo[current_pos] == ";")
                {
                    add_current_pos(profundidade);
                    procedimento_dc_c(profundidade);
                }
                else
                {
                    cout << "Erro no procedimento_dc_c, não é ; e sim:   " << simbolo[current_pos] << endl;
                }
            }
            else
            {
                cout << "Erro no procedimento_dc_c, não é = e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_dc_c, não é ident e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        return; //se não for const só sai da função (lambda)
    }
}

//5. <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
void SintaticoPascalCompiler::procedimento_dc_v(int profundidade)
{
    cout << "--- procedimento_dc_v() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "var")
    {
        add_current_pos(profundidade);

        procedimento_variaveis(profundidade);

        if (simbolo[current_pos] == ":")
        {
            add_current_pos(profundidade);

            procedimento_tipo_var(profundidade);

            if (simbolo[current_pos] == ";")
            {
                add_current_pos(profundidade);
                procedimento_dc_v(profundidade);
            }
            else
            {
                cout << "Erro no procedimento_dc_v, não é ; e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_dc_v, não é : e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        return; //se não for var só sai da função (lambda)
    }
}

//9. <dc_p> ::= precedure ident <parametros> ; <corpo> <dc_p> | λ
void SintaticoPascalCompiler::procedimento_dc_p(int profundidade)
{
    cout << "--- procedimento_dc_p() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "procedure")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == "ident")
        {
            add_current_pos(profundidade);

            procedimento_parametros(profundidade);

            if (simbolo[current_pos] == ";")
            {
                add_current_pos(profundidade);

                procedimento_corpo_p(profundidade);
                procedimento_dc_p(profundidade);
            }
            else
            {
                cout << "Erro no procedimento_dc_p, não é ; e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_dc_p, não é ident e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        return; //se não for procedure só sai da função (lambda)
    }
}

//6. <tipo_var> ::= real | integer
void SintaticoPascalCompiler::procedimento_tipo_var(int profundidade)
{
    cout << "--- procedimento_tipo_var() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "real")
    {
        add_current_pos(profundidade);

        return;
    }
    else if (simbolo[current_pos] == "integer")
    {
        add_current_pos(profundidade);

        return;
    }
    else
    {
        cout << "Erro no procedimento_tipo_var, não é real nem integer e sim:   " << simbolo[current_pos] << endl;
    }
}

//7. <variaveis> ::= ident <mais_var> com
//8. <mais_var> ::= , <variaveis> | λ

//ident ,variaveis
void SintaticoPascalCompiler::procedimento_variaveis(int profundidade)
{
    cout << "--- procedimento_variaveis() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "ident")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == ",")
        {
            add_current_pos(profundidade);
            procedimento_variaveis(profundidade);
        }
        else
        {
            return; //se não for vírgula só sai da função (lambda)
        }
    }
    else
    {
        cout << "Erro no procedimento_variaveis, não é ident e sim:   " << simbolo[current_pos] << endl;
    }
}

//10- <parametros> ::= ( <lista_par> ) | lambda
void SintaticoPascalCompiler::procedimento_parametros(int profundidade)
{
    cout << "--- procedimento_parametros() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "(")
    {
        add_current_pos(profundidade);
        procedimento_lista_par(profundidade);

        if (simbolo[current_pos] == ")")
        {
            add_current_pos(profundidade);
            return;
        }
        else
        {
            cout << "Erro no procedimento_parametros, não é ) e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        return; //se não for "(", sai da função (lambda)
    }
}

//11- <lista_par> ::= <variaveis> : <tipo_var> <mais_par>
//12 -<mais_par> ::= ; <lista_par> | lambda
void SintaticoPascalCompiler::procedimento_lista_par(int profundidade)
{
    cout << "--- procedimento_lista_par() ---" << profundidade << endl;
    profundidade++;
    procedimento_variaveis(profundidade);

    if (simbolo[current_pos] == ":")
    {
        add_current_pos(profundidade);
        procedimento_tipo_var(profundidade);

        if (simbolo[current_pos] == ";")
        {
            add_current_pos(profundidade);
            procedimento_lista_par(profundidade);
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "Erro no procedimento_lista_par, não é : e sim:   " << simbolo[current_pos] << endl;
    }
}

//13. <corpo_p> ::= <dc_loc> begin <comandos> end ; com
//14. <dc_loc> ::= <dc_v>
void SintaticoPascalCompiler::procedimento_corpo_p(int profundidade)
{
    cout << "--- procedimento_corpo_p() ---" << profundidade << endl;
    profundidade++;
    procedimento_dc_v(profundidade);

    if (simbolo[current_pos] == "begin")
    {
        add_current_pos(profundidade);
        procedimento_comandos(profundidade);

        if (simbolo[current_pos] == "end")
        {
            add_current_pos(profundidade);

            if (simbolo[current_pos] == ";")
            {
                add_current_pos(profundidade);
                return;
            }
            else
            {
                cout << "Erro no procedimento_corpo_p, não é ; e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_corpo_p, não é end e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        cout << "Erro no procedimento_corpo_p, não é begin e sim:   " << simbolo[current_pos] << endl;
    }
}

//15. <lista_arg> ::= ( <argumentos> ) | λ
void SintaticoPascalCompiler::procedimento_lista_arg(int profundidade)
{
    cout << "--- procedimento_lista_arg() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "(")
    {
        add_current_pos(profundidade);
        procedimento_argumentos(profundidade);

        if (simbolo[current_pos] == ")")
        {
            add_current_pos(profundidade);
            return;
        }
        else
        {
            cout << "Erro no procedimento_lista_arg, não é ) e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        return; //se não for "(", sai da função (lambda)
    }
}

//16. <argumentos> ::= ident <mais_ident> com
//17. <mais_ident> ::= ; <argumentos> | λ
void SintaticoPascalCompiler::procedimento_argumentos(int profundidade)
{
    cout << "--- procedimento_argumentos() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "ident")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == ";")
        {
            add_current_pos(profundidade);
            cout << "Função procedimento_argumentos:   " << simbolo[current_pos] << endl;
            procedimento_argumentos(profundidade);
        }
        else
        {
            add_current_pos(profundidade);
            return;
        }
    }
    else
    {
        cout << "Erro no procedimento_argumentos, não é ident e sim:   " << simbolo[current_pos] << endl;
    }
}

//18. <pfalsa> ::= else <cmd> | λ
void SintaticoPascalCompiler::procedimento_pfalsa(int profundidade)
{
    if (simbolo[current_pos] == "else")
    {
        add_current_pos(profundidade);
        procedimento_cmd(profundidade);
        return;
    }
    else
    {
        return; //se não for "else", sai da função (lambda)
    }
}

//19. <comandos> ::= <cmd> ; <comandos> | λ
void SintaticoPascalCompiler::procedimento_comandos(int profundidade)
{
    cout << "--- procedimento_comandos() ---" << profundidade << endl;
    if (simbolo[current_pos] == "read" || simbolo[current_pos] == "write" || simbolo[current_pos] == "while" || simbolo[current_pos] == "if" || simbolo[current_pos] == "ident" || simbolo[current_pos] == "begin" || simbolo[current_pos] == "for")
    {
        procedimento_cmd(profundidade);

        if (simbolo[current_pos] == ";")
        {

            add_current_pos(profundidade);
            procedimento_comandos(profundidade);
            return;
        }
        else
        {
            cout << "Erro no procedimento_comandos, não é ; e sim:   " << simbolo[current_pos] << endl;
        }
    }
    else
    {
        return;
    }
}

//15. <lista_arg> ::= ( <argumentos> ) | λ

//20  <cmd> ::= read (<variaveis>) |
//                write (<variaveis>) |
//                while (<condicao>) do <cmd> |
//                if <condicao> then <cmd> <pfalsa> |
//                ident <cmd_aux> |
//                begin <comandos> end |
//                for <variaveis> := numero_int to numero_int do
//    <cmd_aux’> ::= := <expressao> | <lista_arg>

void SintaticoPascalCompiler::procedimento_cmd(int profundidade)
{
    cout << "--- procedimento_cmd() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "read")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "(")
        {
            add_current_pos(profundidade);
            cout << "Função procedimento_cmd if read:   " << simbolo[current_pos] << endl;
            procedimento_variaveis(profundidade);
            if (simbolo[current_pos] == ")")
            {
                add_current_pos(profundidade);
                return;
            }
            else
            {
                cout << "Erro no procedimento_cmd, if-read, não há ) e sim:    " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_cmd, if-read, não há ( e sim:   " << simbolo[current_pos] << endl;
        }
    }

    if (simbolo[current_pos] == "write")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "(")
        {
            add_current_pos(profundidade);
            cout << "Função procedimento_cmd if write:   " << simbolo[current_pos] << endl;
            procedimento_variaveis(profundidade);
            if (simbolo[current_pos] == ")")
            {
                add_current_pos(profundidade);
                return;
            }
            else
            {
                cout << "Erro no procedimento_cmd, if-write, não há ) e sim:    " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_cmd, if-write, não há ( e sim:   " << simbolo[current_pos] << endl;
        }
    }

    else if (simbolo[current_pos] == "while")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "(")
        {
            add_current_pos(profundidade);
            cout << "Função procedimento_cmd if while:   " << simbolo[current_pos] << endl;
            procedimento_condicao(profundidade);
            if (simbolo[current_pos] == ")")
            {
                add_current_pos(profundidade);
                if (simbolo[current_pos] == "do")
                {
                    add_current_pos(profundidade);
                    procedimento_cmd(profundidade);
                }
                else
                {
                    cout << "Erro no procedimento_cmd, if-while, não há do e sim:   " << simbolo[current_pos] << endl;
                }
            }
            else
            {
                cout << "Erro no procedimento_cmd, if-write, não há ) e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_cmd, if-write, não há ( e sim:   " << simbolo[current_pos] << endl;
        }
        
    }

    else if (simbolo[current_pos] == "ident")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == ":=")
        {
            add_current_pos(profundidade);
            cout << "Função procedimento_cmd ident if:   " << simbolo[current_pos] << endl;
            procedimento_expressao(profundidade);
            return;
        }
        else if (simbolo[current_pos] == "(")
        {
            add_current_pos(profundidade);
            cout << "Função procedimento_cmd ident else if:   " << simbolo[current_pos] << endl;
            procedimento_argumentos(profundidade);
            add_current_pos(profundidade);

            if (simbolo[current_pos] == ")")
            {
                add_current_pos(profundidade);
                return;
            }
            else
            {
                cout << "Erro no procedimento_cmd ident else if - if, não há ) e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            return; //se não for ":" nem "(", sai da função (lambda)
        }
    }

    else if (simbolo[current_pos] == "begin")
    {
        add_current_pos(profundidade);
        procedimento_comandos(profundidade);

        if (simbolo[current_pos] == "end")
        {
            add_current_pos(profundidade);
            return;
        }
        else
        {
            cout << "Erro no procedimento_cmd begin, não é end e sim:   " << simbolo[current_pos] << endl;
        }
    }

    else if (simbolo[current_pos] == "if")
    {
        add_current_pos(profundidade);
        cout << "Função procedimento_cmd if:   " << simbolo[current_pos] << endl;
        procedimento_condicao(profundidade);

        if (simbolo[current_pos] == "then")
        {
            add_current_pos(profundidade);
            cout << "Função procedimento_cmd if primeiro if ***:   " << simbolo[current_pos] << endl;
            procedimento_cmd(profundidade);
            cout << "Função procedimento_cmd if primeiro if +++:   " << simbolo[current_pos] << endl;
            procedimento_pfalsa(profundidade);
        }
        else
        {
            cout << "Erro no procedimento_cmd if, não é then e sim:   " << simbolo[current_pos] << endl;
        }
        
    }

    else if (simbolo[current_pos] == "for")
    {
        add_current_pos(profundidade);
        cout << "Função procedimento_cmd for:   " << simbolo[current_pos] << endl;
        procedimento_variaveis(profundidade);
        cout << "Função procedimento_cmd for 2:   " << simbolo[current_pos] << endl;

        if (simbolo[current_pos] == ":=")
        {
            add_current_pos(profundidade);

            if (simbolo[current_pos] == "numero_int")
            {
                add_current_pos(profundidade);

                if (simbolo[current_pos] == "to")
                {
                    add_current_pos(profundidade);

                    if (simbolo[current_pos] == "numero_int")
                    {
                        add_current_pos(profundidade);

                        if (simbolo[current_pos] == "do")
                        {
                            add_current_pos(profundidade);
                            procedimento_cmd(profundidade);
                        }
                        else
                        {
                            cout << "Erro no procedimento_cmd for, não é do e sim:   " << simbolo[current_pos] << endl;
                        }
                    }
                    else
                    {
                        cout << "Erro no procedimento_cmd for, não é numero_int e sim:   " << simbolo[current_pos] << endl;
                    }
                }
                else
                {
                    cout << "Erro no procedimento_cmd for, não é to e sim:   " << simbolo[current_pos] << endl;
                }
            }
            else
            {
                cout << "Erro no procedimento_cmd for, não é numero_int e sim:   " << simbolo[current_pos] << endl;
            }
        }
        else
        {
            cout << "Erro no procedimento_cmd for, não é := e sim:   " << simbolo[current_pos] << endl;
        }
    }

    else
    {
        cout << "Erro no procedimento_cmd, nenhuma regra foi utilizada, simbolo:   " << simbolo[current_pos] << endl;
    }
}

//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_expressao(int profundidade)
{
    cout << "--- procedimento_expressao() ---" << profundidade << endl;
    cout << "Função procedimento_expressao:   " << simbolo[current_pos] << endl;
    procedimento_termo(profundidade);
    procedimento_outros_termos(profundidade);
}

//21. <condicao> ::= <expressao> <relacao> <expressao>
//22. <relacao> ::= = | <> | >= | <= | > | <
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_condicao(int profundidade)
{
    cout << "--- procedimento_condicao() ---" << profundidade << endl;
    procedimento_expressao(profundidade);
    if (simbolo[current_pos] == "=" || simbolo[current_pos] == "<>" || simbolo[current_pos] == ">=" || simbolo[current_pos] == "<=" || simbolo[current_pos] == ">" || simbolo[current_pos] == "<")
    {
        add_current_pos(profundidade);
        cout << "Função procedimento_condicao if:   " << simbolo[current_pos] << endl;
        procedimento_expressao(profundidade);
        return;
    }
    else
    {
        cout << "Erro no procedimento_condicao, não é  = | <> | >= | <= | > | <, e sim:   " << simbolo[current_pos] << endl;
    }
}

//24. <op_un> ::= + | - | λ com
//27. <termo> ::= <op_un> <fator> <mais_fatores>
void SintaticoPascalCompiler::procedimento_termo(int profundidade)
{
    cout << "--- procedimento_termo() ---" << profundidade << endl;
    if (simbolo[current_pos] == "+" || simbolo[current_pos] == "-")
    {

        add_current_pos(profundidade);
        cout << "Função procedimento_termo if:   " << simbolo[current_pos] << endl;
    }

    procedimento_fator(profundidade);
    procedimento_mais_fatores(profundidade);
}

//25. <outros_termos> ::= <op_ad><termo><outros_termos> | λ com
//26. <op_ad> ::= + | -
void SintaticoPascalCompiler::procedimento_outros_termos(int profundidade)
{   
    cout << "--- procedimento_outros_termos() ---" << profundidade << endl;
    if (simbolo[current_pos] == "+" ||simbolo[current_pos] == "-")
    {
        add_current_pos(profundidade);
        cout << "Função procedimento_outros_termos if:   " << simbolo[current_pos] << endl;
        procedimento_termo(profundidade);
        procedimento_outros_termos(profundidade);
    }
    else
    {
        return;
    }
}

//28. <mais_fatores> ::= <op_mul> <fator> <mais_fatores> | λ com
//29. <op_mul> ::= * | /
void SintaticoPascalCompiler::procedimento_mais_fatores(int profundidade)
{
    cout << "--- procedimento_mais_fatores() ---" << profundidade << endl;
    if (simbolo[current_pos] == "*" || simbolo[current_pos] == "/")
    {

        add_current_pos(profundidade);
        cout << "Função procedimento_mais_fatores if1:   " << simbolo[current_pos] << endl;
        procedimento_fator(profundidade);
        cout << "Função procedimento_mais_fatores if2:   " << simbolo[current_pos] << endl;
        procedimento_mais_fatores(profundidade);
    }
    else
    {
        return; //não é * ou /
    }
}

//30. <fator> ::= ident | <numero> | ( <expressao> )
//31. <numero> ::= numero_int | numero_real
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_fator(int profundidade)
{
    cout << "--- procedimento_fator() ---" << profundidade << endl;
    if (simbolo[current_pos] == "ident" || simbolo[current_pos] == "numero_int" || simbolo[current_pos] == "numero_real")
    {
        cout << "Função procedimento_fator if:   " << simbolo[current_pos] << endl;
        add_current_pos(profundidade); //simbolo "ident" ou "numero_int" ou "numero_real" é consumido
        return;                        //retorno é realizado
    }
    else if (simbolo[current_pos] == "(")
    {
        
        add_current_pos(profundidade);
        cout << "Função procedimento_fator else if:   " << simbolo[current_pos] << endl;
        procedimento_expressao(profundidade);

        if (simbolo[current_pos] == ")")
        {
            add_current_pos(profundidade); //simbolo ")" é consumido
            return;                        //retorno é realizado
        }
        else
        {
            cout << "Erro no procedimento_fator, não é ) e sim:   " << simbolo[current_pos] << endl;
        }
        
    }
    else
    {
        cout << "Erro no procedimento_fator, não é ident | numero_int | numero_real | ( e sim:   " << simbolo[current_pos] << endl;
    }
}

void SintaticoPascalCompiler::procedimento_ERRO(vector<string> seguidor, vector<string> seguidor_pai, int linha_atual)
{
    vector<string> token_sincronizacao = {"program", "var", "const", "procedure", "begin", "read", "write", "while", "if","end"};
    buffer_erro.push_back(simbolo[current_pos]);

    while (true)
    {
        add_current_pos(0);
        vector<string>::iterator t_seg = find(seguidor.begin(), seguidor.end(), simbolo[current_pos]);
        if(t_seg != seguidor.end()) //token atual e seguidor do token que deu erro
        {
            cout << "Achou o seguidor" << endl;
            break;
        }
        vector<string>::iterator t_pai = find(seguidor_pai.begin(), seguidor_pai.end(), simbolo[current_pos]);
        if(t_pai != seguidor_pai.end()) //token atual e seguidor do pai  token que deu erro
        {
            cout << "Achou o seguidor do pai" << endl;
            break;
        }
        vector<string>::iterator t_sinc = find(token_sincronizacao.begin(), token_sincronizacao.end(), simbolo[current_pos]);
        if(t_sinc != token_sincronizacao.end())
        {
            cout << "Achou palavra de sincronizacao" << endl;
            break;
        }
    }
    return;
}