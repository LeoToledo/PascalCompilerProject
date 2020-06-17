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
    //cout << simbolo[current_pos] << " " << profundidade << endl;
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
    //cout << "--- procedimento_programa() --- " << profundidade << endl;
    profundidade++;

    if (simbolo[current_pos] == "simb_program")
    {
        add_current_pos(profundidade);
    }
    else
    {
        //cout << "Erro no procedimento_programa, não é program e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"id"};
        vector<string> seguidor_pai = {""};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ program “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    if (simbolo[current_pos] == "id")
    {
        add_current_pos(profundidade);
    }
    else
    {
        //cout << "Erro no procedimento_programa, não é id e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_pv"};
        vector<string> seguidor_pai = {""};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  identificador esperado na linha " + to_string(linha_atual[current_pos]));
    }
    if (simbolo[current_pos] == "simb_pv")
    {
        add_current_pos(profundidade);
    }
    else
    {
        if(linha_atual[current_pos] == 2)
        {
            current_pos--;
        }
        //cout << "Erro no procedimento_programa, não é ; e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_const", "simb_var", "simb_procedure"};
        vector<string> seguidor_pai = {""};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ; “ esperado na linha  " + to_string(linha_atual[current_pos]));
    }
    procedimento_corpo(profundidade);
    if (simbolo[current_pos] == "simb_p")
    {
        printf("Sucesso");
        return;
    }
    else
    {
        //cout << "Erro no procedimento_programa, não é . e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {""};
        vector<string> seguidor_pai = {""};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ . “ esperado na linha  " + to_string(linha_atual[current_pos]));
    }
}

//2. <corpo> ::= <dc> begin <comandos> end
void SintaticoPascalCompiler::procedimento_corpo(int profundidade)
{
    //cout << "--- procedimento_corpo() ---" << profundidade << endl;
    profundidade++;
    procedimento_dc(profundidade);

    if (simbolo[current_pos] == "simb_begin")
    {
        add_current_pos(profundidade);
    }
    else
    {
        if(linha_atual[current_pos] == linha_atual[current_pos+3])
        {
            //cout << "Erro no procedimento_corpo, não é var, procedure, const e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "simb_begin", "simb_if", "simb_for", "simb_end"};
            vector<string> seguidor_pai = {"simb_p"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “var“, “const“ ou “procedure“ esperado na linha " + to_string(linha_atual[current_pos]));
            add_current_pos(0);
        }
        else
        {
            //cout << "Erro no procedimento_corpo, não é begin e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for", "simb_end"};
            vector<string> seguidor_pai = {"simb_p"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “begin“ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        
        /*//cout << "Erro no procedimento_corpo, não é begin e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for", "simb_end"};
        vector<string> seguidor_pai = {"simb_p"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ begin “ esperado na linha " + to_string(linha_atual[current_pos]));*/
    }
    procedimento_comandos(profundidade);
    if (simbolo[current_pos] == "simb_end")
    {
        add_current_pos(profundidade);
        //cout << "Retornou do corpo" << endl;
        return;
    }
    else
    {
        if(current_pos < simbolo.size()-1)
        {
            add_current_pos(0);
        }
        if(simbolo[current_pos] == "simb_p")
        {
            //cout << "Erro no procedimento_corpo, não é end e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_p"};
            vector<string> seguidor_pai = {"simb_p"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ end “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        else
        {
            //cout << "Erro no procedimento_corpo, não é read | write | while | begin | for | if | id e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_p"};
            vector<string> seguidor_pai = {"simb_p"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: read | write | while | begin | for | if | id esperado na linha " + to_string(linha_atual[current_pos]));   
            add_current_pos(0);
        }
    }
}

//3. <dc> ::= <dc_c> <dc_v> <dc_p>
void SintaticoPascalCompiler::procedimento_dc(int profundidade)
{
    //cout << "--- procedimento_dc() ---" << profundidade << endl;
    profundidade++;
    procedimento_dc_c(profundidade);
    //add_current_pos(profundidade);
    procedimento_dc_v(profundidade);
    //add_current_pos(profundidade);
    procedimento_dc_p(profundidade);
}

//4. <dc_c> ::= const id = <numero> ; <dc_c> | λ
void SintaticoPascalCompiler::procedimento_dc_c(int profundidade)
{
    //cout << "--- procedimento_dc_c() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "simb_const")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == "id")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_dc_c, não é id e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_igual"};
            vector<string> seguidor_pai = {"simb_var", "simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: identificador esperado na linha " + to_string(linha_atual[current_pos]));
        }

        if (simbolo[current_pos] == "simb_igual")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_dc_c, não é = e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"numero_int", "numero_real"};
            vector<string> seguidor_pai = {"simb_var", "simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ = “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_fator(profundidade);
        if (simbolo[current_pos] == "simb_pv")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_dc_c, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_const", "simb_var", "simb_procedure", "simb_begin"};
            vector<string> seguidor_pai = {"simb_var", "simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_dc_c(profundidade);
    }
    else
    {
        return; //se não for const só sai da função (lambda)
    }
}

//5. <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
void SintaticoPascalCompiler::procedimento_dc_v(int profundidade)
{
    //cout << "--- procedimento_dc_v() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "simb_var")
    {
        add_current_pos(profundidade);

        procedimento_variaveis(profundidade);

        if (simbolo[current_pos] == "simb_dp")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_dc_v, não é : e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_real", "simb_integer"};
            vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ : “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_tipo_var(profundidade);
        if (simbolo[current_pos] == "simb_pv")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_dc_v, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_var", "simb_procedure", "simb_begin"};
            vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_dc_v(profundidade);
    }
    else
    {
        return; //se não for var só sai da função (lambda)
    }
}

//9. <dc_p> ::= precedure id <parametros> ; <corpo> <dc_p> | λ
void SintaticoPascalCompiler::procedimento_dc_p(int profundidade)
{
    //cout << "--- procedimento_dc_p() ---" << profundidade << endl;
    profundidade++;

    if (simbolo[current_pos] == "simb_procedure")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == "id")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_dc_p, não é id e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_apar", "simb_pv"};
            vector<string> seguidor_pai = {"simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: identificador esperado na linha " + to_string(linha_atual[current_pos]));
        }

        procedimento_parametros(profundidade);

        if (simbolo[current_pos] == "simb_pv")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_dc_p, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_var", "simb_begin"};
            vector<string> seguidor_pai = {"simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_corpo_p(profundidade);
        procedimento_dc_p(profundidade);
    }
    else
    {
        return; //se não for procedure só sai da função (lambda)
    }
}

//6. <tipo_var> ::= real | integer
void SintaticoPascalCompiler::procedimento_tipo_var(int profundidade)
{
    //cout << "--- procedimento_tipo_var() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "simb_real")
    {
        add_current_pos(profundidade);

        return;
    }
    else if (simbolo[current_pos] == "simb_integer")
    {
        add_current_pos(profundidade);

        return;
    }
    else
    {
        //cout << "Erro no procedimento_tipo_var, não é real ou integer e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_pv"};
        vector<string> seguidor_pai = {"simb_pv"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ real “ ou “ integer “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
}

//7. <variaveis> ::= id <mais_var> com
//8. <mais_var> ::= , <variaveis> | λ

//id ,variaveis
void SintaticoPascalCompiler::procedimento_variaveis(int profundidade)
{
    //cout << "--- procedimento_variaveis() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "id")
    {
        add_current_pos(profundidade);
    }
    else
    {
        //cout << "Erro no procedimento_variaveis, não é id e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_virg", "simb_dp"};
        vector<string> seguidor_pai = {"simb_dp"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: identificador esperado na linha " + to_string(linha_atual[current_pos]));
    }

    if (simbolo[current_pos] == "simb_virg")
    {
        add_current_pos(profundidade);
        procedimento_variaveis(profundidade);
    }
    else
    {
        return; //se não for vírgula só sai da função (lambda)
    }
}

//10- <parametros> ::= ( <lista_par> ) | lambda
void SintaticoPascalCompiler::procedimento_parametros(int profundidade)
{
    //cout << "--- procedimento_parametros() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "simb_apar")
    {
        add_current_pos(profundidade);
        procedimento_lista_par(profundidade);
    }
    else
    {
        return; //se não for "simb_apar", sai da função (lambda)
    }
    if (simbolo[current_pos] == "simb_fpar")
    {
        add_current_pos(profundidade);
        return;
    }
    else
    {
        //cout << "Erro no procedimento_parametros, não é ) e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_pv"};
        vector<string> seguidor_pai = {"simb_pv"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ ) “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
}

//11- <lista_par> ::= <variaveis> : <tipo_var> <mais_par>
//12 -<mais_par> ::= ; <lista_par> | lambda
void SintaticoPascalCompiler::procedimento_lista_par(int profundidade)
{
    //cout << "--- procedimento_lista_par() ---" << profundidade << endl;
    profundidade++;
    procedimento_variaveis(profundidade);

    if (simbolo[current_pos] == "simb_dp")
    {
        add_current_pos(profundidade);
    }
    else
    {
        //cout << "Erro no procedimento_lista_par, não é : e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_real", "simb_integer"};
        vector<string> seguidor_pai = {"simb_fpar"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ : “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    procedimento_tipo_var(profundidade);
    if (simbolo[current_pos] == "simb_pv")
    {
            add_current_pos(profundidade);
            procedimento_lista_par(profundidade);
    }
    else
    {
        return;
    }
    
}

//13. <corpo_p> ::= <dc_loc> begin <comandos> end ; com
//14. <dc_loc> ::= <dc_v>
void SintaticoPascalCompiler::procedimento_corpo_p(int profundidade)
{
    //cout << "--- procedimento_corpo_p() ---" << profundidade << endl;
    profundidade++;
    procedimento_dc_v(profundidade);

    if (simbolo[current_pos] == "simb_begin")
    {
        add_current_pos(profundidade);
    }
    else
    {
        //cout << "Erro no procedimento_corpo_p, não é begin e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for"};
        vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ begin “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    procedimento_comandos(profundidade);
    if (simbolo[current_pos] == "simb_end")
    {
        add_current_pos(profundidade);
    }
    else
    {
        //cout << "Erro no procedimento_corpo_p, não é end e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_pv"};
        vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ end “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    if (simbolo[current_pos] == "simb_pv")
    {
        add_current_pos(profundidade);
        return;
    }
    else
    {
        //cout << "Erro no procedimento_corpo_p, não é ; e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_procedure", "simb_begin"};
        vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
}

//15. <lista_arg> ::= ( <argumentos> ) | λ
void SintaticoPascalCompiler::procedimento_lista_arg(int profundidade)
{
    //cout << "--- procedimento_lista_arg() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "simb_apar")
    {
        add_current_pos(profundidade);
        procedimento_argumentos(profundidade);
    }
    else
    {
        return; //se não for "simb_apar", sai da função (lambda)
    }
    if (simbolo[current_pos] == "simb_fpar")
    {
        add_current_pos(profundidade);
        return;
    }
    else
    { 
        //cout << "Erro no procedimento_lista_arg, não é ) e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_pv" , "simb_else"};
        vector<string> seguidor_pai = {"simb_pv" , "simb_else"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ) “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
}

//16. <argumentos> ::= id <mais_id> com
//17. <mais_id> ::= ; <argumentos> | λ
void SintaticoPascalCompiler::procedimento_argumentos(int profundidade)
{
    //cout << "--- procedimento_argumentos() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "id")
    {
        add_current_pos(profundidade);
    }
    else
    {
        //cout << "Erro no procedimento_argumentos, não é id e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_pv", "simb_fpar"};
        vector<string> seguidor_pai = {"simb_fpar"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  identificador esperado na linha " + to_string(linha_atual[current_pos]));
    }
    if (simbolo[current_pos] == "simb_pv")
    {
        add_current_pos(profundidade);
        //cout << "Função procedimento_argumentos:   " << simbolo[current_pos] << endl;
        procedimento_argumentos(profundidade);
    }
    else
    {
        add_current_pos(profundidade);
        return;
    }
}

//18. <pfalsa> ::= else <cmd> | λ
void SintaticoPascalCompiler::procedimento_pfalsa(int profundidade)
{
    if (simbolo[current_pos] == "simb_else")
    {
        add_current_pos(profundidade);
        procedimento_cmd(profundidade);
        return;
    }
    else
    {
        return; //se não for "simb_else", sai da função (lambda)
    }
}

//19. <comandos> ::= <cmd> ; <comandos> | λ
void SintaticoPascalCompiler::procedimento_comandos(int profundidade)
{
    //cout << "--- procedimento_comandos() ---" << profundidade << endl;
    if (simbolo[current_pos] == "simb_read" || simbolo[current_pos] == "simb_write" || simbolo[current_pos] == "simb_while" || simbolo[current_pos] == "simb_if" || simbolo[current_pos] == "id" || simbolo[current_pos] == "simb_begin" || simbolo[current_pos] == "simb_for")
    {
        procedimento_cmd(profundidade);
        if (simbolo[current_pos] == "simb_pv")
        {

            add_current_pos(profundidade);
            
        }
        else
        {
            //cout << "Erro no procedimento_comandos, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for", "lambda"};
            vector<string> seguidor_pai = {"simb_end"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_comandos(profundidade);
    }
    else
    {
        //cout << "Retornou do comandos " << endl;
        return;
    }
    
}

//15. <lista_arg> ::= ( <argumentos> ) | λ

//20  <cmd> ::= read (<variaveis>) |
//                write (<variaveis>) |
//                while (<condicao>) do <cmd> |
//                if <condicao> then <cmd> <pfalsa> |
//                id <cmd_aux> |
//                begin <comandos> end |
//                for <variaveis> := numero_int to numero_int do
//    <cmd_aux’> ::= := <expressao> | <lista_arg>

void SintaticoPascalCompiler::procedimento_cmd(int profundidade)
{
    //cout << "--- procedimento_cmd() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "simb_read")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos(profundidade);
            //cout << "Função procedimento_cmd if read:   " << simbolo[current_pos] << endl;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-read, não há ( e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"id"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ( “ esperado no comando read da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_variaveis(profundidade);
        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos(profundidade);
            return;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-read, não há ) e sim:    " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_pv"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ) “ esperado no comando read da linha " + to_string(linha_atual[current_pos]));
        } 
    }

    else if (simbolo[current_pos] == "simb_write")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos(profundidade);
            //cout << "Função procedimento_cmd if write:   " << simbolo[current_pos] << endl;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-write, não há ( e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"id"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ( “ esperado no comando write da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_variaveis(profundidade);
        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos(profundidade);
            return;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-write, não há ) e sim:    " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_pv"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ) “ esperado no comando write da linha" + to_string(linha_atual[current_pos]));
        }     
    }

    else if (simbolo[current_pos] == "simb_while")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos(profundidade);
            //cout << "Função procedimento_cmd if while:   " << simbolo[current_pos] << endl;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-while, não há ( e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_mais", "simb_menos", "id", "numero_int", "numero_real", "simb_apar"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ( “ esperado no comando while da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_condicao(profundidade);
        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-while, não há ) e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_do"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ) “ esperado no comando while da linha " + to_string(linha_atual[current_pos]));
        }
        if (simbolo[current_pos] == "simb_do")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-while, não há do e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ do “ esperado no comando while da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_cmd(profundidade);  
    }

    else if (simbolo[current_pos] == "id")
    {
        add_current_pos(profundidade);

        if (simbolo[current_pos] == "simb_atrib")
        {
            add_current_pos(profundidade);
            //cout << "Função procedimento_cmd id if:   " << simbolo[current_pos] << endl;
            procedimento_expressao(profundidade);
            return;
        }
        else if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos(profundidade);
            //cout << "Função procedimento_cmd id else if:   " << simbolo[current_pos] << endl;
            procedimento_argumentos(profundidade);
            add_current_pos(profundidade);
        
            if (simbolo[current_pos] == "simb_fpar")
            {
                add_current_pos(profundidade);
                return;
            }
            else
            {
                //cout << "Erro no procedimento_cmd id else if - if, não há ) e sim:   " << simbolo[current_pos] << endl;
                vector<string> seguidor = {"id"};
                vector<string> seguidor_pai = {"simb_pv"};
                procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ) “ esperado no comando id da linha " + to_string(linha_atual[current_pos]));
            }
        }
        else
        {
            return; //se não for "simb_dp" nem "simb_apar", sai da função (lambda)
        }
    }

    else if (simbolo[current_pos] == "simb_begin")
    {
        add_current_pos(profundidade);
        procedimento_comandos(profundidade);
        if (simbolo[current_pos] == "simb_end")
        {
            add_current_pos(profundidade);
            return;
        }
        else
        {
            //cout << "Erro no procedimento_cmd begin, não é end e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_pv"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ end “ esperado no comando begin da linha " + to_string(linha_atual[current_pos]));
        }
    }

    else if (simbolo[current_pos] == "simb_if")
    {
        add_current_pos(profundidade);
        //cout << "Função procedimento_cmd if:   " << simbolo[current_pos] << endl;
        procedimento_condicao(profundidade);

        if (simbolo[current_pos] == "simb_then")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd if, não é then e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ then “ esperado no comando if da linha " + to_string(linha_atual[current_pos]));
        }
            //cout << "Função procedimento_cmd if primeiro if *:   " << simbolo[current_pos] << endl;
            procedimento_cmd(profundidade);
            //cout << "Função procedimento_cmd if primeiro if +++:   " << simbolo[current_pos] << endl;
            procedimento_pfalsa(profundidade);
    }

    else if (simbolo[current_pos] == "simb_for")
    {
        add_current_pos(profundidade);
        //cout << "Função procedimento_cmd for:   " << simbolo[current_pos] << endl;
        procedimento_variaveis(profundidade);
        //cout << "Função procedimento_cmd for 2:   " << simbolo[current_pos] << endl;

        if (simbolo[current_pos] == "simb_atrib")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd for, não é := e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_mais", "simb_menos", "id", "numero_int", "numero_real", "simb_apar"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ := “ esperado no comando for da linha " + to_string(linha_atual[current_pos]));
        }
        if (simbolo[current_pos] == "numero_int")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd for, não é numero_int e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_to"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  número inteiro esperado no comando for da linha " + to_string(linha_atual[current_pos]));
        }
        if (simbolo[current_pos] == "simb_to")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd for, não é to e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"numero_int"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ to “ esperado no comando for da linha " + to_string(linha_atual[current_pos]));
        }
        if (simbolo[current_pos] == "numero_int")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd for, não é numero_int e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_to"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  número inteiro esperado no comando for da linha " + to_string(linha_atual[current_pos]));
        }
        if (simbolo[current_pos] == "simb_do")
        {
            add_current_pos(profundidade);
        }
        else
        {
            //cout << "Erro no procedimento_cmd for, não é do e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_pv"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ do “ esperado na linha x " + to_string(linha_atual[current_pos]));
        }
        procedimento_cmd(profundidade);       
    }
    else
    {
        //cout << "Erro no procedimento_cmd, nenhuma regra foi utilizada, simbolo:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"id"};
        vector<string> seguidor_pai = {"simb_pv"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: nenhum comando (read, write, while, id, begin, if ou for) foi utilizado na linha " + to_string(linha_atual[current_pos]));
    }
}

//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_expressao(int profundidade)
{
    //cout << "--- procedimento_expressao() ---" << profundidade << endl;
    //cout << "Função procedimento_expressao:   " << simbolo[current_pos] << endl;
    procedimento_termo(profundidade);
    procedimento_outros_termos(profundidade);
}

//21. <condicao> ::= <expressao> <relacao> <expressao>
//22. <relacao> ::= = | <> | >= | <= | > | <
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_condicao(int profundidade)
{
    //cout << "--- procedimento_condicao() ---" << profundidade << endl;
    procedimento_expressao(profundidade);
    if (simbolo[current_pos] == "simb_igual" || simbolo[current_pos] == "simb_dif" || simbolo[current_pos] == "simb_maior_igual" || simbolo[current_pos] == "simb_menor_igual" || simbolo[current_pos] == "simb_maior" || simbolo[current_pos] == "simb_menor")
    {
        add_current_pos(profundidade);
        //cout << "Função procedimento_condicao if:   " << simbolo[current_pos] << endl;
    }
    else
    {
        //cout << "Erro no procedimento_condicao, não é  = | <> | >= | <= | > | <, e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_mais", "simb_menos", "id", "numero_int", "numero_real", "simb_apar"};
        vector<string> seguidor_pai = {"simb_fpar", "simb_then"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ = “, “ <> “ , “ >= “, “ <= “, “ > “ ou “ < “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    procedimento_expressao(profundidade);
    return;
}

//24. <op_un> ::= + | - | λ com
//27. <termo> ::= <op_un> <fator> <mais_fatores>
void SintaticoPascalCompiler::procedimento_termo(int profundidade)
{
    //cout << "--- procedimento_termo() ---" << profundidade << endl;
    if (simbolo[current_pos] == "simb_mais" || simbolo[current_pos] == "simb_menos")
    {

        add_current_pos(profundidade);
        //cout << "Função procedimento_termo if:   " << simbolo[current_pos] << endl;
    }

    procedimento_fator(profundidade);
    procedimento_mais_fatores(profundidade);
}

//25. <outros_termos> ::= <op_ad><termo><outros_termos> | λ com
//26. <op_ad> ::= + | -
void SintaticoPascalCompiler::procedimento_outros_termos(int profundidade)
{
    //cout << "--- procedimento_outros_termos() ---" << profundidade << endl;
    if (simbolo[current_pos] == "simb_mais" || simbolo[current_pos] == "simb_menos")
    {
        add_current_pos(profundidade);
        //cout << "Função procedimento_outros_termos if:   " << simbolo[current_pos] << endl;
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
    //cout << "--- procedimento_mais_fatores() ---" << profundidade << endl;
    if (simbolo[current_pos] == "simb_mult" || simbolo[current_pos] == "simb_div")
    {

        add_current_pos(profundidade);
        //cout << "Função procedimento_mais_fatores if1:   " << simbolo[current_pos] << endl;
        procedimento_fator(profundidade);
        //cout << "Função procedimento_mais_fatores if2:   " << simbolo[current_pos] << endl;
        procedimento_mais_fatores(profundidade);
    }
    else
    {
        return; //não é * ou /
    }
}

//30. <fator> ::= id | <numero> | ( <expressao> )
//31. <numero> ::= numero_int | numero_real
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_fator(int profundidade)
{
    //cout << "--- procedimento_fator() ---" << profundidade << endl;
    if (simbolo[current_pos] == "id" || simbolo[current_pos] == "numero_int" || simbolo[current_pos] == "numero_real")
    {
        //cout << "Função procedimento_fator if:   " << simbolo[current_pos] << endl;
        add_current_pos(profundidade); //simbolo "id" ou "numero_int" ou "numero_real" é consumido
        return;                        //retorno é realizado
    }
    else if (simbolo[current_pos] == "simb_apar")
    {

        add_current_pos(profundidade);
        //cout << "Função procedimento_fator else if:   " << simbolo[current_pos] << endl;
        procedimento_expressao(profundidade);

        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos(profundidade); //simbolo "simb_fpar" é consumido
            return;                        //retorno é realizado
        }
        else
        {
            //cout << "Erro no procedimento_fator, não é ) e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_mult", "simb_div", "simb_virg", "simb_mais", "simb_menos", "simb_igual", "simb_virg", "simb_dif", "simb_maior_igual", "simb_menor_igual", "simb_maior", "simb_menor", "simb_pv", "simb_fpar", "simb_then"};
            vector<string> seguidor_pai = {"simb_mult", "simb_div", "simb_virg", "simb_mais" , "simb_menos" , "simb_igual", "simb_dif", "simb_maior_igual", "simb_menor_igual", "simb_maior", "simb_menor", "simb_pv", "simb_fpar", "simb_then"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ) “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
    }
    else
    {
        //cout << "Erro no procedimento_fator, não é id | numero_int | numero_real | ( e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_mult", "simb_div", "simb_virg", "simb_mais" , "simb_menos" , "simb_igual", "simb_dif", "simb_maior_igual", "simb_menor_igual", "simb_maior", "simb_menor", "simb_pv", "simb_fpar", "simb_then"};
        vector<string> seguidor_pai = { "simb_mais" , "simb_menos" , "simb_igual", "simb_dif", "simb_maior_igual", "simb_menor_igual", "simb_maior", "simb_menor", "simb_pv", "simb_fpar", "simb_then"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  identificador, número inteiro, número real ou “ ( “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
}

void SintaticoPascalCompiler::procedimento_ERRO(vector<string> seguidor, vector<string> seguidor_pai, int linha_atual, string MSG_ERRO)
{
    vector<string> token_sincronizacao = {"simb_program", "simb_var", "simb_const", "simb_procedure", "simb_begin", "simb_read", "simb_write", "simb_while", "simb_if", "simb_end"};
    buffer_erro.push_back(MSG_ERRO);

    vector<string>::iterator t_seg = find(seguidor.begin(), seguidor.end(), simbolo[current_pos]);
    vector<string>::iterator t_pai = find(seguidor_pai.begin(), seguidor_pai.end(), simbolo[current_pos]);
    vector<string>::iterator t_sinc = find(token_sincronizacao.begin(), token_sincronizacao.end(), simbolo[current_pos]);

    bool first_pos = false;

    for (int i = 0; i < seguidor.size(); i++)
    {
        if(simbolo[current_pos] == seguidor[i])
        {
            if(current_pos > 0)
            {
                current_pos--;
            }
            else
            {
                first_pos = true;
            }
            break;
        }
    }
    

    while (true)
    {
        if(simbolo.size()-1 == current_pos)
        {
            break;
        }
        if(simbolo[current_pos] == "Erro_Lexico")
        {
            buffer_erro.push_back(simbolo[current_pos] + ": " + simb_msg[current_pos]);
        }
        add_current_pos(0);
        if(first_pos)
            current_pos--;
        vector<string>::iterator t_seg = find(seguidor.begin(), seguidor.end(), simbolo[current_pos]);
        ////cout << "current_pos = " << simbolo[current_pos] << endl;
        if (t_seg != seguidor.end()) //token atual e seguidor do token que deu erro
        {
            //cout << "Achou o seguidor: " << simbolo[current_pos] << endl;
            break;
        }
        vector<string>::iterator t_pai = find(seguidor_pai.begin(), seguidor_pai.end(), simbolo[current_pos]);
        if (t_pai != seguidor_pai.end()) //token atual e seguidor do pai  token que deu erro
        {
            //cout << "Achou o seguidor do pai: " << simbolo[current_pos] << endl;
            break;
        }
        vector<string>::iterator t_sinc = find(token_sincronizacao.begin(), token_sincronizacao.end(), simbolo[current_pos]);
        if (t_sinc != token_sincronizacao.end())
        {
            //cout << "Achou palavra de sincronizacao: " << simbolo[current_pos] << endl;
            break;
        }
    }
    return;
}