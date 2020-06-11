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
    procedimento_programa(simbolo[0]);
}

string SintaticoPascalCompiler::get_next_simb()
{
    add_current_pos();
    return simbolo[current_pos];
}

void SintaticoPascalCompiler::procedimento_programa(string symbol)
{
    if (symbol == "program")
    {
        symbol = get_next_simb();
        if (symbol == "ident")
        {   
            symbol = get_next_simb();
            if (symbol == ";")
            {   
                symbol = get_next_simb();

                procedimento_corpo(symbol);
                
                symbol = get_next_simb();
                if (symbol == ".")
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
void SintaticoPascalCompiler::procedimento_corpo(string symbol)
{   
    procedimento_dc(symbol);
    if (symbol == "begin")
    {   
        symbol = get_next_simb();
        procedimento_comandos(symbol);
        symbol = get_next_simb();
        if (symbol == "end")
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
void SintaticoPascalCompiler::procedimento_dc(string symbol)
{
    procedimento_dc_c(symbol);
    //symbol = get_next_simb();
    procedimento_dc_v(symbol);
    //symbol = get_next_simb();
    procedimento_dc_p(symbol);
}

//4. <dc_c> ::= const ident = <numero> ; <dc_c> | λ
void SintaticoPascalCompiler::procedimento_dc_c(string symbol)
{   
    if (symbol == "const")
    {
        symbol = get_next_simb();
        if (symbol == "ident")
        {
            symbol = get_next_simb();
            if (symbol == "=")
            {
                symbol = get_next_simb();
                procedimento_fator(symbol);
                symbol = get_next_simb();
                if (symbol == ";")
                {
                    symbol = get_next_simb();
                    if (symbol == "const")
                    {
                        procedimento_dc_c(symbol);
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
void SintaticoPascalCompiler::procedimento_dc_v(string symbol)
{
    if (symbol == "var")
    {
        symbol = get_next_simb();
        procedimento_variaveis(symbol);
        cout <<"AQUII " << symbol << endl;
        if (symbol == ":")
        {
            symbol = get_next_simb();
            procedimento_tipo_var(symbol);
            symbol = get_next_simb();
            if (symbol == ";")
            {
                symbol = get_next_simb();
                if (symbol == "var")
                {
                    procedimento_dc_v(symbol);
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
        return; //se não for var só sai da função (lambda)
    }
}

//9. <dc_p> ::= precedure ident <parametros> ; <corpo> <dc_p> | λ
void SintaticoPascalCompiler::procedimento_dc_p(string symbol)
{
    if (symbol == "procedure")
    {
        symbol = get_next_simb();
        if (symbol == "ident")
        {
            symbol = get_next_simb();
            procedimento_parametros(symbol);
            symbol = get_next_simb();
            if (symbol == ";")
            {
                symbol = get_next_simb();
                procedimento_corpo_p(symbol);
                if (symbol == "procedure")
                {
                    procedimento_dc_p(symbol);
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
void SintaticoPascalCompiler::procedimento_tipo_var(string symbol)
{
    if (symbol == "real")
    {
        symbol = get_next_simb();
    }
    else if (symbol == "integer")
    {
        symbol = get_next_simb();
    }
    else
    {
        cout << "ERRO - não é igual a real ou integer";
    }
}

//7. <variaveis> ::= ident <mais_var> com
//8. <mais_var> ::= , <variaveis> | λ

//ident ,variaveis
void SintaticoPascalCompiler::procedimento_variaveis(string symbol)
{
    if (symbol == "ident")
    {
        symbol = get_next_simb();
        
        if (symbol == ",")
        {
            symbol = get_next_simb();
            if (symbol == "ident")
            {
                procedimento_variaveis(symbol);
            }
            else
            {
                cout << "ERRO - não é igual a ident";
            }
        }
        else
        {   cout <<"AQUII AOBA " <<symbol << endl;
            return; //se não for vírgula só sai da função (lambda)
        }
    }
    else
    {   
        cout << "ERRO - não é igual a ident";
    }
}

//10- <parametros> ::= ( <lista_par> ) | lambda
void SintaticoPascalCompiler::procedimento_parametros(string symbol)
{
    if (symbol == "(")
    {
        symbol = get_next_simb();
        procedimento_lista_par(symbol);
        symbol = get_next_simb();
        if (symbol == ")")
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
void SintaticoPascalCompiler::procedimento_lista_par(string symbol)
{
    procedimento_variaveis(symbol);
    symbol = get_next_simb();
    if (symbol == ":")
    {
        symbol = get_next_simb();
        procedimento_tipo_var(symbol);
        symbol = get_next_simb();
        if (symbol == ";")
        {
            procedimento_lista_par(symbol);
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
void SintaticoPascalCompiler::procedimento_corpo_p(string symbol)
{
    procedimento_dc_v(symbol);
    symbol = get_next_simb();
    if (symbol == "begin")
    {
        symbol = get_next_simb();
        procedimento_comandos(symbol);
        symbol = get_next_simb();
        if (symbol == "end")
        {
            symbol = get_next_simb();
            if (symbol == ";")
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
void SintaticoPascalCompiler::procedimento_argumentos(string symbol)
{
    if (symbol == "ident")
    {
        symbol = get_next_simb();
        if (symbol == ";")
        {
            symbol = get_next_simb();
            if (symbol == "ident")
            {
                procedimento_argumentos(symbol);
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
void SintaticoPascalCompiler::procedimento_comandos(string symbol)
{
    if (symbol == "read" || "write" || "while" || "if" || "ident" || "begin" || "for")
    {
        symbol = get_next_simb();
        if (symbol == ";")
        {
            symbol = get_next_simb();
            procedimento_variaveis(symbol);
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

void SintaticoPascalCompiler::procedimento_cmd(string symbol)
{
    if (symbol == "read")
    {
        symbol = get_next_simb();
        procedimento_variaveis(symbol);
        return;
    }

    else if (symbol == "write")
    {
        symbol = get_next_simb();
        procedimento_variaveis(symbol);
        return;
    }

    else if (symbol == "while")
    {
        symbol = get_next_simb();
        procedimento_condicao(symbol);
        symbol = get_next_simb();
        if (symbol == "do")
        {
            symbol = get_next_simb();
            procedimento_cmd(symbol);
        }

        else if (symbol == "ident")
        {
            symbol = get_next_simb();
            if (symbol == ":")
            {
                symbol = get_next_simb();
                if (symbol == "=")
                {
                    symbol = get_next_simb();
                    procedimento_expressao(symbol);
                    return;
                }
                else
                {
                    cout << "ERRO - não é =";
                }
            }
            else if (symbol == "(")
            {
                symbol = get_next_simb();
                procedimento_argumentos(symbol);
                symbol = get_next_simb();
                if (symbol == ")")
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

        else if (symbol == "begin")
        {
            symbol = get_next_simb();
            procedimento_comandos(symbol);
            symbol = get_next_simb();
            if (symbol == "end")
            {
                return;
            }
            else
            {
                cout << "ERRO - não é igual a end";
            }
        }

        else if (symbol == "if")
        {
            symbol = get_next_simb();
            procedimento_condicao(symbol);
            symbol = get_next_simb();
            if (symbol == "then")
            {
                symbol = get_next_simb();
                if (symbol == "read" || "write" || "while" || "if" || "ident" || "begin" || "if" || "for")
                {
                    procedimento_cmd(symbol);
                }
                else if (symbol == "else")
                {
                    symbol = get_next_simb();
                    procedimento_cmd(symbol);
                }
                else
                {
                    return;
                }
            }
        }

        else if (symbol == "for")
        {
            symbol = get_next_simb();
            procedimento_variaveis(symbol);
            symbol = get_next_simb();
            if (symbol == ":")
            {
                symbol = get_next_simb();
                if (symbol == "=")
                {
                    symbol = get_next_simb();
                    if (symbol == "numero_int")
                    {
                        symbol = get_next_simb();
                        if (symbol == "to")
                        {
                            symbol = get_next_simb();
                            if (symbol == "numero_int")
                            {
                                symbol = get_next_simb();
                                if (symbol == "do")
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
void SintaticoPascalCompiler::procedimento_expressao(string symbol)
{
    if(symbol == "+" || "-" || "ident" || "numero_int" || "numero_real" || "("){
        procedimento_termo(symbol);
        symbol = get_next_simb();
        if(symbol == "-" || "+"){
            procedimento_termo(symbol);
            symbol = get_next_simb();
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
void SintaticoPascalCompiler::procedimento_condicao(string symbol)
{
    if (symbol == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
    {
        procedimento_termo(symbol);
        symbol = get_next_simb();
        if (symbol == "+" || "-")
        {
            procedimento_outros_termos(symbol);
            symbol = get_next_simb();
            if (symbol == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                symbol = get_next_simb();
                if (symbol == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao(symbol);
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
            if (symbol == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                symbol = get_next_simb();
                if (symbol == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao(symbol);
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
void SintaticoPascalCompiler::procedimento_termo(string symbol)
{
    if (symbol == "+" || "-")
    {
        symbol = get_next_simb();
        if (symbol == "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_fator(symbol);
            symbol = get_next_simb();
            if (symbol == "*" || "/")
            {
                procedimento_mais_fatores(symbol);
                return;
            }
            else
            {
                return; //se não for "*" nem "/", sai da funcao (lambda)
            }
        }
    }
    else if (symbol == "ident" || "numero_int" || "numero_real" || "(")
    {
        procedimento_fator(symbol);
        symbol = get_next_simb();
        if (symbol == "*" || "/")
        {
            procedimento_mais_fatores(symbol);
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
void SintaticoPascalCompiler::procedimento_outros_termos(string symbol)
{
    if (symbol == "+" || "-")
    {
        symbol = get_next_simb();
        if (symbol == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_termo(symbol);
            symbol = get_next_simb();
            if (symbol == "+" || "-")
            {
                procedimento_outros_termos(symbol);
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
void SintaticoPascalCompiler::procedimento_mais_fatores(string symbol)
{
    if (symbol == "*" || "/")
    {
        symbol = get_next_simb();
        if (symbol == "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_fator(symbol);
            symbol = get_next_simb();
            if (symbol == "*" || "/")
            {
                procedimento_mais_fatores(symbol);
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
void SintaticoPascalCompiler::procedimento_fator(string symbol)
{
    if (symbol == "ident" || "numero_int" || "numero_real")
    {
        return;
    }
    else if (symbol == "(")
    {
        symbol = get_next_simb();
        if (symbol == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_termo(symbol);
            symbol = get_next_simb();
            if (symbol == "+" || "-")
            {
                procedimento_outros_termos(symbol);
                symbol = get_next_simb();
                if (symbol == ")")
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
            symbol = get_next_simb();
            if (symbol == ")")
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
