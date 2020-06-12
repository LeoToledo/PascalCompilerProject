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

void SintaticoPascalCompiler::add_current_pos(int profundidade)
{
    current_pos++;
    cout << simbolo[current_pos] << " " << profundidade << endl;
}
int SintaticoPascalCompiler::get_current_pos()
{
    return current_pos;
}

void SintaticoPascalCompiler::ASD(vector<string> symbol)
{
    set_simbolo(symbol);
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

                add_current_pos(profundidade);
                
                if (simbolo[current_pos] == ".")
                {
                    printf("Sucesso");
                    return;
                }
                else
                {
                    cout << "ERRO - não é igual a ." << endl;
                }
            }
            else
            {
                cout << "ERRO - não é igual a ;" << endl;
            }
        }
        else
        {
            cout << "ERRO - não é igual a ident" << endl;
        }
    }
    else
    {
        cout << "ERRO - não é igual a program" << endl;
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
            cout << "Retornou" << endl;
        }
        else
        {
            cout << "ERRO - não é igual a end" << endl;
        }
    }
    else
    {
        cout << "ERRO - não é igual a begin" << endl;
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
                add_current_pos(profundidade);
                
                if (simbolo[current_pos] == ";")
                {
                    add_current_pos(profundidade);
                    
                    if (simbolo[current_pos] == "const")
                    {
                        procedimento_dc_c(profundidade);
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    cout << "ERRO - não é igual a ;" << endl;
                }
            }
            else
            {
                cout << "Erro - não é igual a =" << endl;
            }
        }
        else
        {
            cout << "Erro - não é igual a ident" << endl;
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
                
                if (simbolo[current_pos] == "var")
                {
                    procedimento_dc_v(profundidade);
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
            add_current_pos(profundidade);
            
            if (simbolo[current_pos] == ";")
            {
                add_current_pos(profundidade);
                
                procedimento_corpo_p(profundidade);
                if (simbolo[current_pos] == "procedure")
                {
                    procedimento_dc_p(profundidade);
                }
                else
                {
                    return;
                }
            }
            else
            {
                cout << "ERRO - não é igual a ;" << endl;
            }
        }
        else
        {
            cout << "ERRO - não é igual a :" << endl;
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
        cout << "ERRO - não é igual a real ou integer" << endl;
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
            
            if (simbolo[current_pos] == "ident")
            {
                procedimento_variaveis(profundidade);
            }
            else
            {
                cout << "ERRO - não é igual a ident" << endl;
            }
        }
        else
        {
            return; //se não for vírgula só sai da função (lambda)
        }
    }
    else
    {
        cout << "ERRO - não é igual a ident" << endl;
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
        add_current_pos(profundidade);
        
        if (simbolo[current_pos] == ")")
        {
            return;
        }
        else
        {
            cout << "ERRO - não é igual a )" << endl;
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
    add_current_pos(profundidade);
    
    if (simbolo[current_pos] == ":")
    {
        add_current_pos(profundidade);
        procedimento_tipo_var(profundidade);
        add_current_pos(profundidade);
        
        if (simbolo[current_pos] == ";")
        {
            procedimento_lista_par(profundidade);
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "ERRO - não é igual a :" << endl;
    }
}

//13. <corpo_p> ::= <dc_loc> begin <comandos> end ; com
//14. <dc_loc> ::= <dc_v>
void SintaticoPascalCompiler::procedimento_corpo_p(int profundidade)
{
    cout << "--- procedimento_corpo_p() ---" << profundidade << endl;
    profundidade++;
    procedimento_dc_v(profundidade);
    add_current_pos(profundidade);
    
    if (simbolo[current_pos] == "begin")
    {
        add_current_pos(profundidade);
        procedimento_comandos(profundidade);
        add_current_pos(profundidade);
        
        if (simbolo[current_pos] == "end")
        {
            add_current_pos(profundidade);
            
            if (simbolo[current_pos] == ";")
            {
                return;
            }
            else
            {
                cout << "ERRO - não é igual a ;" << endl;
            }
        }
        else
        {
            cout << "ERRO - não é igual a end" << endl;
        }
    }
    else
    {
        cout << "ERRO - não é igual a begin" << endl;
    }
}


//15. <lista_arg> ::= ( <argumentos> ) | λ
void SintaticoPascalCompiler::procedimento_lista_arg(int profundidade){
    cout << "--- procedimento_lista_arg() ---" << profundidade << endl;
    profundidade++;
    if(simbolo[current_pos] == "("){
        add_current_pos(profundidade);
        procedimento_argumentos(profundidade);
        add_current_pos(profundidade);
        
        if(simbolo[current_pos] == ")"){
            return;
        }else{
            cout << "ERRO - não é igual a )" << endl;
        }
    }else{
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
            
            if (simbolo[current_pos] == "ident")
            {
                procedimento_argumentos(profundidade);
            }
            else
            {
                cout << "ERRO - não é igual a ident" << endl;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "ERRO - não é igual a ident" << endl;
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
void SintaticoPascalCompiler::procedimento_comandos(int profundidade)
{
    cout << "--- procedimento_comandos() ---" << profundidade << endl;
    if (simbolo[current_pos] == "read" ||simbolo[current_pos] ==  "write" ||simbolo[current_pos] ==  "while" ||simbolo[current_pos] ==  "if" ||simbolo[current_pos] ==  "ident" ||simbolo[current_pos] ==  "begin" ||simbolo[current_pos] ==  "for")
    { 
        procedimento_cmd(profundidade);
 
        //add_current_pos(profundidade);


        if (simbolo[current_pos] == ";")
        { 

            add_current_pos(profundidade);
            
            procedimento_comandos(profundidade);
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

void SintaticoPascalCompiler::procedimento_cmd(int profundidade)
{
    cout << "--- procedimento_cmd() ---" << profundidade << endl;
    profundidade++;
    if (simbolo[current_pos] == "read")
    {
        add_current_pos(profundidade);
        procedimento_variaveis(profundidade);
        return;
    }

    else if (simbolo[current_pos] == "write")
    {
        add_current_pos(profundidade);
        procedimento_variaveis(profundidade);
        return;
    }

    else if (simbolo[current_pos] == "while")
    {
        add_current_pos(profundidade);
        procedimento_condicao(profundidade);
        add_current_pos(profundidade);
        
        if (simbolo[current_pos] == "do")
        {
            add_current_pos(profundidade);
            procedimento_cmd(profundidade);
        }
    }
    else if (simbolo[current_pos] == "ident")
    {   
        add_current_pos(profundidade);
        
        
        if (simbolo[current_pos] == ":=")
        {   
            add_current_pos(profundidade);
            procedimento_expressao(profundidade);
            return;
        }
        else if (simbolo[current_pos] == "(")
        {
            add_current_pos(profundidade);
            procedimento_argumentos(profundidade);
            add_current_pos(profundidade);
            
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
        add_current_pos(profundidade);
        
        procedimento_comandos(profundidade);
        add_current_pos(profundidade);
        
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
        add_current_pos(profundidade);
        
        procedimento_condicao(profundidade);
        add_current_pos(profundidade);
        
        if (simbolo[current_pos] == "then")
        {
            add_current_pos(profundidade);
            
            if (simbolo[current_pos] == "read" || "write" || "while" || "if" || "ident" || "begin" || "if" || "for")
            {
                procedimento_cmd(profundidade);
            }
            else if (simbolo[current_pos] == "else")
            {
                add_current_pos(profundidade);
                
                procedimento_cmd(profundidade);
            }
            else
            {
                return;
            }
        }
    }

    else if (simbolo[current_pos] == "for")
    {
        add_current_pos(profundidade);
        
        procedimento_variaveis(profundidade);
        add_current_pos(profundidade);
        
        if (simbolo[current_pos] == ":")
        {
            add_current_pos(profundidade);
            
            if (simbolo[current_pos] == "=")
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
                                return;
                            }
                            else
                            {
                                cout << "ERRO - não é igual a do" << endl;
                            }
                        }
                        else
                        {
                            cout << "ERRO - não é igual a numero_int" << endl;
                        }
                    }
                    else
                    {
                        cout << "ERRO - não é igual a to" << endl;
                    }
                }
                else
                {
                    cout << "ERRO - não é igual a numero_int" << endl;
                }
            }
            else
            {
                cout << "ERRO - não é igual a =" << endl;
            }
        }
        else
        {
            cout << "ERRO - não é igual a :" << endl;
        }
    }
    else
    {
        cout << "ERRO - Nenhum regra do cmd foi utilizada" << endl;
    }
}

//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_expressao(int profundidade)
{   
    cout << "--- procedimento_expressao() ---" << profundidade << endl;
    if (simbolo[current_pos] == "+" ||simbolo[current_pos] == "-" ||simbolo[current_pos] == "ident" || simbolo[current_pos] =="numero_int" || simbolo[current_pos] =="numero_real" ||simbolo[current_pos] == "(")
    {   
        procedimento_termo(profundidade);
        //add_current_pos(profundidade);
        
        if (simbolo[current_pos] == "-" ||simbolo[current_pos] == "+")
        {
            procedimento_termo(profundidade);
            add_current_pos(profundidade);
        }
        else
        {   
            return;
        }
    }
    else
    {
        printf("ERRO - não é + || - || ident || numero_int || numero_real || ( ");
    }
}

//21. <condicao> ::= <expressao> <relacao> <expressao>
//22. <relacao> ::= = | <> | >= | <= | > | <
//23. <expressao> ::= <termo> <outros_termos>
void SintaticoPascalCompiler::procedimento_condicao(int profundidade)
{
    cout << "--- procedimento_condicao() ---" << profundidade << endl;
    if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
    {
        procedimento_termo(profundidade);
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "+" || "-")
        {
            procedimento_outros_termos(profundidade);
            add_current_pos(profundidade);
            if (simbolo[current_pos] == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                add_current_pos(profundidade);
                if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao(profundidade);
                }
                else
                {
                    return;
                }
            }
            else
            {
                cout << "ERRO - não é igual a = || diferente || maior_igual || menor_igual || > || <" << endl;
            }
        }
        else
        {
            if (simbolo[current_pos] == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                add_current_pos(profundidade);
                if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao(profundidade);
                }
                else
                {
                    return;
                }
            }
            else
            {
                cout << "ERRO - não é igual a = || diferente || maior_igual || menor_igual || > || <" << endl;
            }
        }
    }
    else
    {
        cout << "ERRO - não é igual a + || - || ident || numero_int || numero_real || (" << endl;
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
        if (simbolo[current_pos] == "ident" ||simbolo[current_pos] ==  "numero_int" ||simbolo[current_pos] ==  "numero_real" ||simbolo[current_pos] ==  "(")
        {   
            procedimento_fator(profundidade); 
            add_current_pos(profundidade);
            if (simbolo[current_pos] == "*" || simbolo[current_pos] == "/")
            {
                procedimento_mais_fatores(profundidade);
                return;
            }
            else
            {   
                return; //se não for "*" nem "/", sai da funcao (lambda)
            }
        }
    }
    
    else if (simbolo[current_pos] == "ident" || simbolo[current_pos] == "numero_int" ||simbolo[current_pos] ==  "numero_real" ||simbolo[current_pos] ==  "(")
    {     
        procedimento_fator(profundidade);
        add_current_pos(profundidade);
        
        if (simbolo[current_pos] == "*" || simbolo[current_pos] == "/")
        {
            procedimento_mais_fatores(profundidade);
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
void SintaticoPascalCompiler::procedimento_outros_termos(int profundidade)
{
    cout << "--- procedimento_outros_termos() ---" << profundidade << endl;
    if (simbolo[current_pos] == "+" || "-")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
        {
            procedimento_termo(profundidade);
            
            add_current_pos(profundidade);
            if (simbolo[current_pos] == "+" || "-")
            {
                procedimento_outros_termos(profundidade);
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
void SintaticoPascalCompiler::procedimento_mais_fatores(int profundidade)
{
    cout << "--- procedimento_mais_fatores() ---" << profundidade << endl;
    if (simbolo[current_pos] == "*" || "/")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "ident" || "numero_int" || "numero_real" || "(")
        {   
            procedimento_fator(profundidade);
            add_current_pos(profundidade);
            
            if (simbolo[current_pos] == "*" || "/")
            {
                procedimento_mais_fatores(profundidade);
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
void SintaticoPascalCompiler::procedimento_fator(int profundidade)
{   
    cout << "--- procedimento_fator() ---" << profundidade << endl;
    if (simbolo[current_pos] == "ident" ||simbolo[current_pos] == "numero_int" ||simbolo[current_pos] == "numero_real")
    {
        return;
    }
    else if (simbolo[current_pos] == "(")
    {
        add_current_pos(profundidade);
        if (simbolo[current_pos] == "+" ||simbolo[current_pos] == "-" || simbolo[current_pos] =="ident" ||simbolo[current_pos] == "numero_int" || simbolo[current_pos] =="numero_real" || simbolo[current_pos] =="(")
        {
            procedimento_termo(profundidade);
            add_current_pos(profundidade);
            if (simbolo[current_pos] == "+" ||simbolo[current_pos] == "-")
            {
                procedimento_outros_termos(profundidade);
                add_current_pos(profundidade);
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
            add_current_pos(profundidade);
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
