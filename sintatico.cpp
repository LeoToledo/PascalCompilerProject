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

void SintaticoPascalCompiler::add_current_pos()
{
    current_pos++;
    //cout << simbolo[current_pos] << " " <<  << endl;
}
int SintaticoPascalCompiler::get_current_pos()
{
    return current_pos;
}

void SintaticoPascalCompiler::ASD()
{
    procedimento_programa();
}

string SintaticoPascalCompiler::get_next_simb()
{
    //add_current_pos();
    return simbolo[current_pos];
}

void SintaticoPascalCompiler::procedimento_programa()
{
    //cout << "--- procedimento_programa() --- " <<  << endl;
    

    if (simbolo[current_pos] == "simb_program")
    {
        add_current_pos();
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
        add_current_pos();
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
        add_current_pos();
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
    procedimento_corpo();
    if (simbolo[current_pos] == "simb_p")
    {
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
void SintaticoPascalCompiler::procedimento_corpo()
{
    //cout << "--- procedimento_corpo() ---" <<  << endl;
    
    procedimento_dc();

    if (simbolo[current_pos] == "simb_begin")
    {
        add_current_pos();
    }
    else
    {
        if(linha_atual[current_pos] == linha_atual[current_pos+3])
        {
            //cout << "Erro no procedimento_corpo, não é var, procedure, const e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "simb_begin", "simb_if", "simb_for", "simb_end"};
            vector<string> seguidor_pai = {"simb_p"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “var“, “const“ ou “procedure“ esperado na linha " + to_string(linha_atual[current_pos]));
            add_current_pos();
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
    procedimento_comandos();
    if (simbolo[current_pos] == "simb_end")
    {
        add_current_pos();
        //cout << "Retornou do corpo" << endl;
        return;
    }
    else
    {
        if(current_pos < simbolo.size()-1)
        {
            add_current_pos();
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
            add_current_pos();
        }
    }
}

//3. <dc> ::= <dc_c> <dc_v> <dc_p>
void SintaticoPascalCompiler::procedimento_dc()
{
    //cout << "--- procedimento_dc() ---" <<  << endl;
    
    procedimento_dc_c();
    //add_current_pos();
    procedimento_dc_v();
    //add_current_pos();
    procedimento_dc_p();
}

//4. <dc_c> ::= const id = <numero> ; <dc_c> | λ
void SintaticoPascalCompiler::procedimento_dc_c()
{
    //cout << "--- procedimento_dc_c() ---" <<  << endl;
    
    if (simbolo[current_pos] == "simb_const")
    {
        add_current_pos();

        if (simbolo[current_pos] == "id")
        {
            add_current_pos();
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
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_dc_c, não é = e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"numero_int", "numero_real"};
            vector<string> seguidor_pai = {"simb_var", "simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ = “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_fator();
        if (simbolo[current_pos] == "simb_pv")
        {
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_dc_c, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_const", "simb_var", "simb_procedure", "simb_begin"};
            vector<string> seguidor_pai = {"simb_var", "simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_dc_c();
    }
    else
    {
        return; //se não for const só sai da função (lambda)
    }
}

//5. <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
void SintaticoPascalCompiler::procedimento_dc_v()
{
    //cout << "--- procedimento_dc_v() ---" <<  << endl;
    
    if (simbolo[current_pos] == "simb_var")
    {
        add_current_pos();

        procedimento_variaveis();

        if (simbolo[current_pos] == "simb_dp")
        {
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_dc_v, não é : e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_real", "simb_integer"};
            vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ : “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_tipo_var();
        if (simbolo[current_pos] == "simb_pv")
        {
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_dc_v, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_var", "simb_procedure", "simb_begin"};
            vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_dc_v();
    }
    else
    {
        return; //se não for var só sai da função (lambda)
    }
}

//9. <dc_p> ::= precedure id <parametros> ; <corpo> <dc_p> | λ
void SintaticoPascalCompiler::procedimento_dc_p()
{
    //cout << "--- procedimento_dc_p() ---" <<  << endl;
    

    if (simbolo[current_pos] == "simb_procedure")
    {
        add_current_pos();

        if (simbolo[current_pos] == "id")
        {
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_dc_p, não é id e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_apar", "simb_pv"};
            vector<string> seguidor_pai = {"simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: identificador esperado na linha " + to_string(linha_atual[current_pos]));
        }

        procedimento_parametros();

        if (simbolo[current_pos] == "simb_pv")
        {
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_dc_p, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_var", "simb_begin"};
            vector<string> seguidor_pai = {"simb_begin"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático: “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_corpo_p();
        procedimento_dc_p();
    }
    else
    {
        return; //se não for procedure só sai da função (lambda)
    }
}

//6. <tipo_var> ::= real | integer
void SintaticoPascalCompiler::procedimento_tipo_var()
{
    //cout << "--- procedimento_tipo_var() ---" <<  << endl;
    
    if (simbolo[current_pos] == "simb_real")
    {
        add_current_pos();

        return;
    }
    else if (simbolo[current_pos] == "simb_integer")
    {
        add_current_pos();

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
void SintaticoPascalCompiler::procedimento_variaveis()
{
    //cout << "--- procedimento_variaveis() ---" <<  << endl;
    
    if (simbolo[current_pos] == "id")
    {
        add_current_pos();
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
        add_current_pos();
        procedimento_variaveis();
    }
    else
    {
        return; //se não for vírgula só sai da função (lambda)
    }
}

//10- <parametros> ::= ( <lista_par> ) | lambda
void SintaticoPascalCompiler::procedimento_parametros()
{
    //cout << "--- procedimento_parametros() ---" <<  << endl;
    
    if (simbolo[current_pos] == "simb_apar")
    {
        add_current_pos();
        procedimento_lista_par();
    }
    else
    {
        return; //se não for "simb_apar", sai da função (lambda)
    }
    if (simbolo[current_pos] == "simb_fpar")
    {
        add_current_pos();
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
void SintaticoPascalCompiler::procedimento_lista_par()
{
    //cout << "--- procedimento_lista_par() ---" <<  << endl;
    
    procedimento_variaveis();

    if (simbolo[current_pos] == "simb_dp")
    {
        add_current_pos();
    }
    else
    {
        //cout << "Erro no procedimento_lista_par, não é : e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_real", "simb_integer"};
        vector<string> seguidor_pai = {"simb_fpar"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ : “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    procedimento_tipo_var();
    if (simbolo[current_pos] == "simb_pv")
    {
            add_current_pos();
            procedimento_lista_par();
    }
    else
    {
        return;
    }
    
}

//13. <corpo_p> ::= <dc_loc> begin <comandos> end ; com
//14. <dc_loc> ::= <dc_v>
void SintaticoPascalCompiler::procedimento_corpo_p()
{
    //cout << "--- procedimento_corpo_p() ---" <<  << endl;
    
    procedimento_dc_v();

    if (simbolo[current_pos] == "simb_begin")
    {
        add_current_pos();
    }
    else
    {
        //cout << "Erro no procedimento_corpo_p, não é begin e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for"};
        vector<string> seguidor_pai = {"simb_procedure", "simb_begin"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ begin “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    procedimento_comandos();
    if (simbolo[current_pos] == "simb_end")
    {
        add_current_pos();
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
        add_current_pos();
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
void SintaticoPascalCompiler::procedimento_lista_arg()
{
    //cout << "--- procedimento_lista_arg() ---" <<  << endl;
    
    if (simbolo[current_pos] == "simb_apar")
    {
        add_current_pos();
        procedimento_argumentos();
    }
    else
    {
        return; //se não for "simb_apar", sai da função (lambda)
    }
    if (simbolo[current_pos] == "simb_fpar")
    {
        add_current_pos();
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
void SintaticoPascalCompiler::procedimento_argumentos()
{
    //cout << "--- procedimento_argumentos() ---" <<  << endl;
    
    if (simbolo[current_pos] == "id")
    {
        add_current_pos();
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
        add_current_pos();
        //cout << "Função procedimento_argumentos:   " << simbolo[current_pos] << endl;
        procedimento_argumentos();
    }
    else
    {
        add_current_pos();
        return;
    }
}

//18. <pfalsa> ::= else <cmd> | λ
void SintaticoPascalCompiler::procedimento_pfalsa()
{
    if (simbolo[current_pos] == "simb_else")
    {
        add_current_pos();
        procedimento_cmd();
        return;
    }
    else
    {
        return; //se não for "simb_else", sai da função (lambda)
    }
}

//19. <comandos> ::= <cmd> ; <comandos> | λ
void SintaticoPascalCompiler::procedimento_comandos()
{
    //cout << "--- procedimento_comandos() ---" <<  << endl;
    if (simbolo[current_pos] == "simb_read" || simbolo[current_pos] == "simb_write" || simbolo[current_pos] == "simb_while" || simbolo[current_pos] == "simb_if" || simbolo[current_pos] == "id" || simbolo[current_pos] == "simb_begin" || simbolo[current_pos] == "simb_for")
    {
        procedimento_cmd();
        if (simbolo[current_pos] == "simb_pv")
        {

            add_current_pos();
            
        }
        else
        {
            //cout << "Erro no procedimento_comandos, não é ; e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for", "lambda"};
            vector<string> seguidor_pai = {"simb_end"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ; “ esperado na linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_comandos();
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

void SintaticoPascalCompiler::procedimento_cmd()
{
    //cout << "--- procedimento_cmd() ---" <<  << endl;
    
    if (simbolo[current_pos] == "simb_read")
    {
        add_current_pos();
        if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos();
            //cout << "Função procedimento_cmd if read:   " << simbolo[current_pos] << endl;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-read, não há ( e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"id"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ( “ esperado no comando read da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_variaveis();
        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos();
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
        add_current_pos();
        if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos();
            //cout << "Função procedimento_cmd if write:   " << simbolo[current_pos] << endl;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-write, não há ( e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"id"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ( “ esperado no comando write da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_variaveis();
        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos();
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
        add_current_pos();
        if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos();
            //cout << "Função procedimento_cmd if while:   " << simbolo[current_pos] << endl;
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-while, não há ( e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_mais", "simb_menos", "id", "numero_int", "numero_real", "simb_apar"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ ( “ esperado no comando while da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_condicao();
        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos();
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
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_cmd, if-while, não há do e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ do “ esperado no comando while da linha " + to_string(linha_atual[current_pos]));
        }
        procedimento_cmd();  
    }

    else if (simbolo[current_pos] == "id")
    {
        add_current_pos();

        if (simbolo[current_pos] == "simb_atrib")
        {
            add_current_pos();
            //cout << "Função procedimento_cmd id if:   " << simbolo[current_pos] << endl;
            procedimento_expressao();
            return;
        }
        else if (simbolo[current_pos] == "simb_apar")
        {
            add_current_pos();
            //cout << "Função procedimento_cmd id else if:   " << simbolo[current_pos] << endl;
            procedimento_argumentos();
            add_current_pos();
        
            if (simbolo[current_pos] == "simb_fpar")
            {
                add_current_pos();
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
        add_current_pos();
        procedimento_comandos();
        if (simbolo[current_pos] == "simb_end")
        {
            add_current_pos();
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
        add_current_pos();
        //cout << "Função procedimento_cmd if:   " << simbolo[current_pos] << endl;
        procedimento_condicao();

        if (simbolo[current_pos] == "simb_then")
        {
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_cmd if, não é then e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_read", "simb_write", "simb_while", "id", "simb_begin", "simb_if", "simb_for"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ then “ esperado no comando if da linha " + to_string(linha_atual[current_pos]));
        }
            //cout << "Função procedimento_cmd if primeiro if *:   " << simbolo[current_pos] << endl;
            procedimento_cmd();
            //cout << "Função procedimento_cmd if primeiro if +++:   " << simbolo[current_pos] << endl;
            procedimento_pfalsa();
    }

    else if (simbolo[current_pos] == "simb_for")
    {
        add_current_pos();
        //cout << "Função procedimento_cmd for:   " << simbolo[current_pos] << endl;
        procedimento_variaveis();
        //cout << "Função procedimento_cmd for 2:   " << simbolo[current_pos] << endl;

        if (simbolo[current_pos] == "simb_atrib")
        {
            add_current_pos();
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
            add_current_pos();
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
            add_current_pos();
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
            add_current_pos();
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
            add_current_pos();
        }
        else
        {
            //cout << "Erro no procedimento_cmd for, não é do e sim:   " << simbolo[current_pos] << endl;
            vector<string> seguidor = {"simb_pv"};
            vector<string> seguidor_pai = {"simb_pv"};
            procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ do “ esperado na linha x " + to_string(linha_atual[current_pos]));
        }
        procedimento_cmd();       
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
void SintaticoPascalCompiler::procedimento_expressao()
{
    //cout << "--- procedimento_expressao() ---" <<  << endl;
    //cout << "Função procedimento_expressao:   " << simbolo[current_pos] << endl;
    procedimento_termo();
    procedimento_outros_termos();
}

//21. <condicao> ::= <expressao> <relacao> <expressao>
//22. <relacao> ::= = | <> | >= | <= | > | <
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_condicao()
{
    //cout << "--- procedimento_condicao() ---" <<  << endl;
    procedimento_expressao();
    if (simbolo[current_pos] == "simb_igual" || simbolo[current_pos] == "simb_dif" || simbolo[current_pos] == "simb_maior_igual" || simbolo[current_pos] == "simb_menor_igual" || simbolo[current_pos] == "simb_maior" || simbolo[current_pos] == "simb_menor")
    {
        add_current_pos();
        //cout << "Função procedimento_condicao if:   " << simbolo[current_pos] << endl;
    }
    else
    {
        //cout << "Erro no procedimento_condicao, não é  = | <> | >= | <= | > | <, e sim:   " << simbolo[current_pos] << endl;
        vector<string> seguidor = {"simb_mais", "simb_menos", "id", "numero_int", "numero_real", "simb_apar"};
        vector<string> seguidor_pai = {"simb_fpar", "simb_then"};
        procedimento_ERRO(seguidor, seguidor_pai, linha_atual[current_pos], "Erro sintático:  “ = “, “ <> “ , “ >= “, “ <= “, “ > “ ou “ < “ esperado na linha " + to_string(linha_atual[current_pos]));
    }
    procedimento_expressao();
    return;
}

//24. <op_un> ::= + | - | λ com
//27. <termo> ::= <op_un> <fator> <mais_fatores>
void SintaticoPascalCompiler::procedimento_termo()
{
    //cout << "--- procedimento_termo() ---" <<  << endl;
    if (simbolo[current_pos] == "simb_mais" || simbolo[current_pos] == "simb_menos")
    {

        add_current_pos();
        //cout << "Função procedimento_termo if:   " << simbolo[current_pos] << endl;
    }

    procedimento_fator();
    procedimento_mais_fatores();
}

//25. <outros_termos> ::= <op_ad><termo><outros_termos> | λ com
//26. <op_ad> ::= + | -
void SintaticoPascalCompiler::procedimento_outros_termos()
{
    //cout << "--- procedimento_outros_termos() ---" <<  << endl;
    if (simbolo[current_pos] == "simb_mais" || simbolo[current_pos] == "simb_menos")
    {
        add_current_pos();
        //cout << "Função procedimento_outros_termos if:   " << simbolo[current_pos] << endl;
        procedimento_termo();
        procedimento_outros_termos();
    }
    else
    {
        return;
    }
}

//28. <mais_fatores> ::= <op_mul> <fator> <mais_fatores> | λ com
//29. <op_mul> ::= * | /
void SintaticoPascalCompiler::procedimento_mais_fatores()
{
    //cout << "--- procedimento_mais_fatores() ---" <<  << endl;
    if (simbolo[current_pos] == "simb_mult" || simbolo[current_pos] == "simb_div")
    {

        add_current_pos();
        //cout << "Função procedimento_mais_fatores if1:   " << simbolo[current_pos] << endl;
        procedimento_fator();
        //cout << "Função procedimento_mais_fatores if2:   " << simbolo[current_pos] << endl;
        procedimento_mais_fatores();
    }
    else
    {
        return; //não é * ou /
    }
}

//30. <fator> ::= id | <numero> | ( <expressao> )
//31. <numero> ::= numero_int | numero_real
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_fator()
{
    //cout << "--- procedimento_fator() ---" <<  << endl;
    if (simbolo[current_pos] == "id" || simbolo[current_pos] == "numero_int" || simbolo[current_pos] == "numero_real")
    {
        //cout << "Função procedimento_fator if:   " << simbolo[current_pos] << endl;
        add_current_pos(); //simbolo "id" ou "numero_int" ou "numero_real" é consumido
        return;                        //retorno é realizado
    }
    else if (simbolo[current_pos] == "simb_apar")
    {

        add_current_pos();
        //cout << "Função procedimento_fator else if:   " << simbolo[current_pos] << endl;
        procedimento_expressao();

        if (simbolo[current_pos] == "simb_fpar")
        {
            add_current_pos(); //simbolo "simb_fpar" é consumido
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
        add_current_pos();
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