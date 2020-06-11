//21. <condicao> ::= <expressao> <relacao> <expressao>
//22. <relacao> ::= = | <> | >= | <= | > | <
//23. <expressao> ::= <termo> <outros_termos>

int procedimento_condicao(String simbolo)
{
    if (simbolo == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
    {
        posicao_corrente = procedimento_termo(simbolo);
        simbolo = obter_simbolo_lexico(posicao_corrente);
        if (simbolo == "+" || "-")
        {
            posicao_corrente = procedimento_outros_termos(simbolo);
            simbolo = obter_simbolo_lexico(posicao_corrente);
            if (simbolo == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                simbolo = obter_simbolo_lexico(posicao_corrente);
                if (simbolo == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao(simbolo);
                }
                else
                {
                    return posicao_corrente
                }
            }
            else
            {
                ERRO - não é igual a "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<"
            }
        }
        else
        {
            if (simbolo == "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<")
            {
                simbolo = obter_simbolo_lexico(posicao_corrente);
                if (simbolo == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
                {
                    procedimento_condicao(simbolo);
                }
                else
                {
                    return posicao_corrente
                }
            }
            else
            {
                ERRO - não é igual a "=" || "diferente" || "maior_igual" || "menor_igual" || ">" || "<"
            }
        }
    }
    else
    {
        ERRO - não é igual a "+" || "-" || "ident" || "numero_int" || "numero_real" || "("
    }
}

//24. <op_un> ::= + | - | λ com
//27. <termo> ::= <op_un> <fator> <mais_fatores>
int procedimento_termo(String simbolo)
{
    if (simbolo == "+" || "-")
    {
        simbolo = obter_simbolo_lexico(posicao_corrente);
        if (simbolo == "ident" || "numero_int" || "numero_real" || "(")
        {
            posicao_corrente = procedimento_fator(simbolo);
            simbolo = obter_simbolo_lexico(posicao_corrente);
            if (simbolo == "*" || "/")
            {
                posicao_corrente = procedimento_mais_fatores(simbolo);
                return posicao_corrente;
            }
            else
            {
                return posicao_corrente; //se não for "*" nem "/", sai da funcao (lambda)
            }
        }
    }
    else if (simbolo == "ident" || "numero_int" || "numero_real" || "(")
    {
        posicao_corrente = procedimento_fator(simbolo);
        simbolo = obter_simbolo_lexico(posicao_corrente);
        if (simbolo == "*" || "/")
        {
            posicao_corrente = procedimento_mais_fatores(simbolo);
            return posicao_corrente;
        }
        else
        {
            return posicao_corrente; //se não for "*" nem "/", sai da funcao (lambda)
        }
    }
}

//25. <outros_termos> ::= <op_ad><termo><outros_termos> | λ com
//26. <op_ad> ::= + | -
int procedimento_outros_termos(String simbolo)
{
    if (simbolo == "+" || "-")
    {
        simbolo = obter_simbolo_lexico(posicao_corrente);
        if (simbolo == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
        {
            posicao_corrente = procedimento_termo(simbolo);
            simbolo = obter_simbolo_lexico(posicao_corrente);
            if (simbolo == "+" || "-")
            {
                procedimento_outros_termos(simbolo);
            }
            else
            {
                return posicao_corrente;
            }
        }
        else
        {
            ERRO - não é igual a "+" || "-" || "ident" || "numero_int" || "numero_real" || "("
        }
    }
    else
    {
        return posicao_corrente;
    }
}

//28. <mais_fatores> ::= <op_mul> <fator> <mais_fatores> | λ com
//29. <op_mul> ::= * | /

int procedimento_mais_fatores(String simbolo)
{
    if (simbolo == "*" || "/")
    {
        simbolo = obter_simbolo_lexico(posicao_corrente);
        if (simbolo == "ident" || "numero_int" || "numero_real" || "(")
        {
            posicao_corrente = procedimento_fator(simbolo);
            simbolo = obter_simbolo_lexico(posicao_corrente) if (simbolo == "*" || "/")
            {
                procedimento_mais_fatores(simbolo);
            }
            else
            {
                return posicao_corrente;
            }
        }
        else
        {
            ERRO - não é igual a "ident" || "numero_int" || "numero_real" || "("
        }
    }
    else
    {
        return posicao_corrente;
    }
}

//30. <fator> ::= ident | <numero> | ( <expressao> )
//31. <numero> ::= numero_int | numero_real
//23. <expressao> ::= <termo> <outros_termos>
int procedimento_fator(String simbolo)
{
    if (simbolo == "ident" || "numero_int" || "numero_real")
    {
        return posicao_corrente;
    }
    else if (simbolo == "(")
    {
        simbolo = obter_simbolo_lexico(posicao_corrente);
        if (simbolo == "+" || "-" || "ident" || "numero_int" || "numero_real" || "(")
        {
            posicao_corrente = procedimento_termo(simbolo);
            simbolo = obter_simbolo_lexico(posicao_corrente);
            if (simbolo == "+" || "-")
            {
                posicao_corrente = procedimento_outros_termos(simbolo);
                simbolo = obter_simbolo_lexico(posicao_corrente);
                if (simbolo == ")")
                {
                    return posicao_corrente;
                }
                else
                {
                    ERRO - não é ")"
                }
            }
        }
        else
        {
            simbolo = obter_simbolo_lexico(posicao_corrente);
            if (simbolo == ")")
            {
                return posicao_corrente;
            }
            else
            {
                ERRO - não é ")"
            }
        }
    }
    else
    {
        ERRO - não é igual a "ident" || "numero_int" || "numero_real" || "("
    }
}