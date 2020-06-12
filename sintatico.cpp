#include <iostream>
#include <fstream>
#include <cmath>
#include "lexico.h"
#include "sintatico.h"
#include <typeinfo>
#include <vector>

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
}
int SintaticoPascalCompiler::get_current_pos()
{
    return current_pos;
}

void SintaticoPascalCompiler::ASD(vector<string> symbol)
{
    set_simbolo(symbol);
    procedimento_programa();
}

string SintaticoPascalCompiler::get_next_simb()
{
    add_current_pos();
    return simbolo[current_pos];
}


void SintaticoPascalCompiler::procedimento_programa()
{   
    if (simbolo[current_pos] == "program")
    {
        add_current_pos();
        if (simbolo[current_pos] == "ident")
        {   
            add_current_pos();
            if (simbolo[current_pos] == ";")
            {   
                add_current_pos();

                procedimento_corpo();
                
                add_current_pos();
                if (simbolo[current_pos] == ".")
                {
                    printf("Sucesso");
                    return;
                }
                else
                {
                    cout << "ERRO - não é igual a .";
                }
            }
            else
            {
                cout << "ERRO - não é igual a ;";
            }
        }
        else
        {
            cout << "ERRO - não é igual a ident";
        }
    }
    else
    {
        cout << "ERRO - não é igual a program";
    }
}

//2. <corpo> ::= <dc> begin <comandos> end
void SintaticoPascalCompiler::procedimento_corpo()
{   
    procedimento_dc();
    if (simbolo[current_pos] == "begin")
    {   
        add_current_pos();
        procedimento_comandos();
        add_current_pos();
        if (simbolo[current_pos] == "end")
        {
            return;
        }
        else
        {
            cout << "ERRO - não é igual a end";
        }
    }
    else
    {
        cout << "ERRO - não é igual a begin";
    }
}

//3. <dc> ::= <dc_c> <dc_v> <dc_p>
void SintaticoPascalCompiler::procedimento_dc()
{
    procedimento_dc_c();
    //add_current_pos();
    procedimento_dc_v();
    //add_current_pos();
    procedimento_dc_p();
}

//4. <dc_c> ::= const ident = <numero> ; <dc_c> | λ
void SintaticoPascalCompiler::procedimento_dc_c()
{   
    if (simbolo[current_pos] == "const")
    {
        add_current_pos();
        if (simbolo[current_pos] == "ident")
        {
            add_current_pos();
            if (simbolo[current_pos] == "=")
            {
                add_current_pos();
                procedimento_fator();
                add_current_pos();
                if (simbolo[current_pos] == ";")
                {
                    add_current_pos();
                    if (simbolo[current_pos] == "const")
                    {
                        procedimento_dc_c();
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    cout << "ERRO - não é igual a ;";
                }
            }
            else
            {
                cout << "Erro - não é igual a =";
            }
        }
        else
        {
            cout << "Erro - não é igual a ident";
        }
    }
    else
    {  
        return; //se não for const só sai da função (lambda)
    }
}

//5. <dc_v> ::= var <variaveis> : <tipo_var> ; <dc_v> | λ
void SintaticoPascalCompiler::procedimento_dc_v()
{
    if (simbolo[current_pos] == "var")
    {
        add_current_pos();
        procedimento_variaveis();
        cout <<"AQUII 2 " << simbolo[current_pos] << endl;
        
        cout <<"AQUII 3 " << simbolo[current_pos] << endl;
        if (simbolo[current_pos] == ":")
        {
            add_current_pos();
            procedimento_tipo_var();
            add_current_pos();
            if (simbolo[current_pos] == ";")
            {
                add_current_pos();
                if (simbolo[current_pos] == "var")
                {
                    procedimento_dc_v();
                }
                else
                {
                    return;
                }
            }
            else
            {
               return; 
            }
        }
        else
        {
            cout << "ERRO - não é igual a :";
        }
    }
    else
    {
        return; //se não for var só sai da função (lambda)
    }
}

//9. <dc_p> ::= precedure ident <parametros> ; <corpo> <dc_p> | λ
void SintaticoPascalCompiler::procedimento_dc_p()
{
    if (simbolo[current_pos] == "procedure")
    {
        add_current_pos();
        if (simbolo[current_pos] == "ident")
        {
            add_current_pos();
            procedimento_parametros();
            add_current_pos();
            if (simbolo[current_pos] == ";")
            {
                add_current_pos();
                procedimento_corpo_p();
                if (simbolo[current_pos] == "procedure")
                {
                    procedimento_dc_p();
                }
                else
                {
                    return;
                }
            }
            else
            {
                cout << "ERRO - não é igual a ;";
            }
        }
        else
        {
            cout << "ERRO - não é igual a :";
        }
    }
    else
    {
        return; //se não for procedure só sai da função (lambda)
    }
}

//6. <tipo_var> ::= real | integer
void SintaticoPascalCompiler::procedimento_tipo_var()
{
    if (simbolo[current_pos] == "real")
    {
        add_current_pos();
    }
    else if (simbolo[current_pos] == "integer")
    {
        add_current_pos();
    }
    else
    {
        cout << "ERRO - não é igual a real ou integer";
    }
}

//7. <variaveis> ::= ident <mais_var> com
//8. <mais_var> ::= , <variaveis> | λ

//ident ,variaveis
void SintaticoPascalCompiler::procedimento_variaveis()
{
    if (simbolo[current_pos] == "ident")
    {   
        add_current_pos();
        
        if (simbolo[current_pos] == ",")
        {
            add_current_pos();
            if (simbolo[current_pos] == "ident")
            {
                procedimento_variaveis();
            }
            else
            {
                cout << "ERRO - não é igual a ident";
            }
        }
        else
        {   cout <<"AQUII " << simbolo[current_pos] << endl;
            return; //se não for vírgula só sai da função (lambda)
        }
    }
    else
    {   
        cout << "ERRO - não é igual a ident";
    }
}

//10- <parametros> ::= ( <lista_par> ) | lambda
void SintaticoPascalCompiler::procedimento_parametros()
{
    if (simbolo[current_pos] == "(")
    {
        add_current_pos();
        procedimento_lista_par();
        add_current_pos();
        if (simbolo[current_pos] == ")")
        {
            return;
        }
        else
        {
            cout << "ERRO - não é igual a )";
        }
    }
    else
    {
        return; //se não for "(", sai da função (lambda)
    }
}

//11- <lista_par> ::= <variaveis> : <tipo_var> <mais_par>
//12 -<mais_par> ::= ; <lista_par> | lambda
void SintaticoPascalCompiler::procedimento_lista_par()
{
    procedimento_variaveis();
    add_current_pos();
    if (simbolo[current_pos] == ":")
    {
        add_current_pos();
        procedimento_tipo_var();
        add_current_pos();
        if (simbolo[current_pos] == ";")
        {
            procedimento_lista_par();
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "ERRO - não é igual a :";
    }
}

//13. <corpo_p> ::= <dc_loc> begin <comandos> end ; com
//14. <dc_loc> ::= <dc_v>
void SintaticoPascalCompiler::procedimento_corpo_p()
{
    procedimento_dc_v();
    add_current_pos();
    if (simbolo[current_pos] == "begin")
    {
        add_current_pos();
        procedimento_comandos();
        add_current_pos();
        if (simbolo[current_pos] == "end")
        {
            add_current_pos();
            if (simbolo[current_pos] == ";")
            {
                return;
            }
            else
            {
                cout << "ERRO - não é igual a ;";
            }
        }
        else
        {
            cout << "ERRO - não é igual a end";
        }
    }
    else
    {
        cout << "ERRO - não é igual a begin";
    }
}

//15. <lista_arg> ::= ( <argumentos> ) | λ
//int procedimento_lista_arg(simbolo){
//    if(simbolo == "("){
//        simbolo = get_next_simb();
//        procedimento_argumentos(simbolo);
//        simbolo = get_next_simb();
//        if(simbolo == ")"){
//            return;
//        }else{
//            ERRO - não é igual a ")"
//        }
//    }else{
//        return; //se não for "(", sai da função (lambda)
//    }
//}

//16. <argumentos> ::= ident <mais_ident> com
//17. <mais_ident> ::= ; <argumentos> | λ
void SintaticoPascalCompiler::procedimento_argumentos()
{
    if (simbolo[current_pos] == "ident")
    {
        add_current_pos();
        if (simbolo[current_pos] == ";")
        {
            add_current_pos();
            if (simbolo[current_pos] == "ident")
            {
                procedimento_argumentos();
            }
            else
            {
                cout << "ERRO - não é igual a ident";
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "ERRO - não é igual a ident";
    }
}

//18. <pfalsa> ::= else <cmd> | λ
//int procedimento_pfalsa(simbolo){
//    if(simbolo == "else"){
//        simbolo = get_next_simb();
//        procedimento_cmd(simbolo);
//        return;
//    }else{
//        return; //se não for "else", sai da função (lambda)
//    }
//}

//19. <comandos> ::= <cmd> ; <comandos> | λ
void SintaticoPascalCompiler::procedimento_comandos()
{
    if (simbolo[current_pos] == "read" || "write" || "while" || "if" || "ident" || "begin" || "for")
    {
        add_current_pos();
        if (simbolo[current_pos] == ";")
        {
            add_current_pos();
            procedimento_variaveis();
            return;
        }
        else
        {
            cout << "ERRO - não é igual a ;";
        }
    }
    else
    {
        return;
    }
}

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

void SintaticoPascalCompiler::procedimento_cmd()
{
    if (simbolo[current_pos] == "read")
    {
        add_current_pos();
        procedimento_variaveis();
        return;
    }

    else if (simbolo[current_pos] == "write")
    {
        add_current_pos();
        procedimento_variaveis();
        return;
    }

    else if (simbolo[current_pos] == "while")
    {
        add_current_pos();
        procedimento_condicao();
        add_current_pos();
        if (simbolo[current_pos] == "do")
        {
            add_current_pos();
            procedimento_cmd();
        }

        else if (simbolo[current_pos] == "ident")
        {
            add_current_pos();
            if (simbolo[current_pos] == ":")
            {
                add_current_pos();
                if (simbolo[current_pos] == "=")
                {
                    add_current_pos();
                    procedimento_expressao();
                    return;
                }
                else
                {
                    cout << "ERRO - não é =";
                }
            }
            else if (simbolo[current_pos] == "(")
            {
                add_current_pos();
                procedimento_argumentos();
                add_current_pos();
                if (simbolo[current_pos] == ")")
                {
                    return;
                }
                else
                {
                    cout << "ERRO - não é )";
                }
            }
            else
            {
                return; //se não for ":" nem "(", sai da função (lambda)
            }
        }

        else if (simbolo[current_pos] == "begin")
        {
            add_current_pos();
            procedimento_comandos();
            add_current_pos();
            if (simbolo[current_pos] == "end")
            {
                return;
            }
            else
            {
                cout << "ERRO - não é igual a end";
            }
        }

        else if (simbolo[current_pos] == "if")
        {
            add_current_pos();
            procedimento_condicao();
            add_current_pos();
            if (simbolo[current_pos] == "then")
            {
                add_current_pos();
                if (simbolo[current_pos] == "read" || "write" || "while" || "if" || "ident" || "begin" || "if" || "for")
                {
                    procedimento_cmd();
                }
                else if (simbolo[current_pos] == "else")
                {
                    add_current_pos();
                    procedimento_cmd();
                }
                else
                {
                    return;
                }
            }
        }

        else if (simbolo[current_pos] == "for")
        {
            add_current_pos();
            procedimento_variaveis();
            add_current_pos();
            if (simbolo[current_pos] == ":")
            {
                add_current_pos();
                if (simbolo[current_pos] == "=")
                {
                    add_current_pos();
                    if (simbolo[current_pos] == "numero_int")
                    {
                        add_current_pos();
                        if (simbolo[current_pos] == "to")
                        {
                            add_current_pos();
                            if (simbolo[current_pos] == "numero_int")
                            {
                                add_current_pos();
                                if (simbolo[current_pos] == "do")
                                {
                                    return;
                                }
                                else
                                {
                                    cout << "ERRO - não é igual a do";
                                }
                            }
                            else
                            {
                                cout << "ERRO - não é igual a numero_int";
                            }
                        }
                        else
                        {
                            cout << "ERRO - não é igual a to";
                        }
                    }
                    else
                    {
                        cout << "ERRO - não é igual a numero_int";
                    }
                }
                else
                {
                    cout << "ERRO - não é igual a =";
                }
            }
            else
            {
                cout << "ERRO - não é igual a :";
            }
        }
        else
        {
            cout << "ERRO - Nenhum regra do cmd foi utilizada";
        }
    }
}

//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_expressao()
{
    if(simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "("){
        procedimento_termo();
        add_current_pos();
        if(simbolo[current_pos] == "-" || "+"){
            procedimento_termo();
            add_current_pos();
        }else{
            return;
        }
    }else{
        printf("ERRO - não é + || - || ident || numero_int || numero_real || ( "); 
    }
}

//21. <condicao> ::= <expressao> <relacao> <expressao>
//22. <relacao> ::= = | <> | >= | <= | > | <
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_condicao()
{
    if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
    {
        procedimento_termo();
        add_current_pos();
        if (simbolo[current_pos] == "+" || "-")
        {
            procedimento_outros_termos();
            add_current_pos();
            if (simbolo[current_pos] == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                add_current_pos();
                if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao();
                }
                else
                {
                    return;
                }
            }
            else
            {
                cout << "ERRO - não é igual a = || diferente || maior_igual || menor_igual || > || <";
            }
        }
        else
        {
            if (simbolo[current_pos] == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                add_current_pos();
                if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao();
                }
                else
                {
                    return;
                }
            }
            else
            {
                cout << "ERRO - não é igual a = || diferente || maior_igual || menor_igual || > || <";
            }
        }
    }
    else
    {
        cout << "ERRO - não é igual a + || - || ident || numero_int || numero_real || (";
    }
}

//24. <op_un> ::= + | - | λ com
//27. <termo> ::= <op_un> <fator> <mais_fatores>
void SintaticoPascalCompiler::procedimento_termo()
{
    if (simbolo[current_pos] == "+" || "-")
    {
        add_current_pos();
        if (simbolo[current_pos] == "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_fator();
            add_current_pos();
            if (simbolo[current_pos] == "*" || "/")
            {
                procedimento_mais_fatores();
                return;
            }
            else
            {
                return; //se não for "*" nem "/", sai da funcao (lambda)
            }
        }
    }
    else if (simbolo[current_pos] == "ident" || "numero_int" || "numero_real" || "(")
    {
        procedimento_fator();
        add_current_pos();
        if (simbolo[current_pos] == "*" || "/")
        {
            procedimento_mais_fatores();
            return;
        }
        else
        {
            return; //se não for "*" nem "/", sai da funcao (lambda)
        }
    }
}

//25. <outros_termos> ::= <op_ad><termo><outros_termos> | λ com
//26. <op_ad> ::= + | -
void SintaticoPascalCompiler::procedimento_outros_termos()
{
    if (simbolo[current_pos] == "+" || "-")
    {
        add_current_pos();
        if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_termo();
            add_current_pos();
            if (simbolo[current_pos] == "+" || "-")
            {
                procedimento_outros_termos();
            }
            else
            {
                return;
            }
        }
        else
        {
            cout << "ERRO - não é igual a + || - || ident || numero_int || numero_real || (";
        }
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
    if (simbolo[current_pos] == "*" || "/")
    {
        add_current_pos();
        if (simbolo[current_pos] == "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_fator();
            add_current_pos();
            if (simbolo[current_pos] == "*" || "/")
            {
                procedimento_mais_fatores();
            }
            else
            {
                return;
            }
        }
        else
        {
            cout << "ERRO - não é igual a ident || numero_int || numero_real || (";
        }
    }
    else
    {
        return;
    }
}

//30. <fator> ::= ident | <numero> | ( <expressao> )
//31. <numero> ::= numero_int | numero_real
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_fator()
{
    if (simbolo[current_pos] == "ident" || "numero_int" || "numero_real")
    {
        return;
    }
    else if (simbolo[current_pos] == "(")
    {
        add_current_pos();
        if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_termo();
            add_current_pos();
            if (simbolo[current_pos] == "+" || "-")
            {
                procedimento_outros_termos();
                add_current_pos();
                if (simbolo[current_pos] == ")")
                {
                    return;
                }
                else
                {
                    cout << "ERRO - não é )";
                }
            }
        }
        else
        {
            add_current_pos();
            if (simbolo[current_pos] == ")")
            {
                return;
            }
            else
            {
                cout << "ERRO - não é )";
            }
        }
    }
    else
    {
        cout << "ERRO - não é igual a ident || numero_int || numero_real || (";
    }
}
