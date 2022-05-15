//
// Created by felipe on 4/16/22.
//
#include "lexico.h"
#include <cstring>
#include <utility>
#include <iostream>

bool Lexico::ehSimbolo(gchar ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
        ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' ||
        ch == '(' || ch == ')' || ch == ':') {
        return true;
    }
    return false;
}
bool Lexico::identificadorValido(gchar *str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' ||
        str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' ||
        str[0] == '8' || str[0] == '9' || ehSimbolo(str[0])) {
        return false;
    } // Se o primeiro caractere da string for digito ou pontuacao o identificador não é valido.
    int i;
    unsigned long len = strlen(str);
    if (len == 1) {
        return true;
    } // Se o tamanho da string = 1 a validação ja foi feita.
    else {
        for (i = 1; i < len;
             i++) // Identificador não pode conter caractere especiais.
        {
            if (ehSimbolo(str[i])) {
                return false;
            }
        }
    }
    return true;
}
bool Lexico::ehOperador(gchar ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' ||
        ch == '<' || ch == '=') {
        return true;
    }
    return false;
}

bool Lexico::ehEspecial(gchar ch)
{
    if (ch == '(' || ch == ')') {
        return true;
    }
    return false;
}
bool Lexico::ehReservada(gchar *str)
{
    if (strcmp(str, "if") == 0 || strcmp(str, "then") == 0 ||
        strcmp(str, "else") == 0 || strcmp(str, "case") == 0 ||
        strcmp(str, "or") == 0 || strcmp(str, "and") == 0 ||
        strcmp(str, "for") == 0 || strcmp(str, "end") == 0 ||
        strcmp(str, "in") == 0 || strcmp(str, "begin") == 0 ||
        strcmp(str, "float") == 0 || strcmp(str, "double") == 0 ||
        strcmp(str, "int") == 0 || strcmp(str, "long_int") == 0 ||
        strcmp(str, "char") == 0 || strcmp(str, "string") == 0 ||
        strcmp(str, "short_int") == 0 || strcmp(str, "bool") == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Lexico::ehNumero(gchar *str)
{
    int i;
    unsigned long len = strlen(str);
    int ponto = 0;
    int nDecimal = 0;

    if (len == 0) {
        return false;
    }
    for (i = 0; i < len; i++) {
        if (ponto > 1) {
            return false;
        }
        if (nDecimal < 1 && str[i] == '.') {
            return false;
        }
        if (nDecimal <= 1) {
            nDecimal++;
        }
        if (str[i] == '.') {
            i++;
            ponto++;
        }
        // Caso a string passada *str não possuir estes caracteres 0-9 não é
        // considerada numero.
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' &&
            str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' &&
            str[i] != '8' && str[i] != '9') {
            return false;
        }
    }
    return true;
}

gchar * Lexico::subString(const gchar *baseStr, int primeiro, int ultimo)
{
    int i;
    auto *str = (gchar *) malloc(sizeof(gchar) * (ultimo - primeiro + 2));
    for (i = primeiro; i <= ultimo; i++) {
        str[i - primeiro] = baseStr[i];
        str[ultimo - primeiro + 1] = '\0';
    }
    return str;
}

//Identifica \n e \t para ser trocado para espaço
bool Lexico::ehQuebra(gchar chr){
    return (chr == '\n');
}
bool Lexico::ehEspaco(gchar chr)
{
    return (chr == '\t');
}

int Lexico::ehString(gchar *str)
{
    //0 - Nenhuma aspa dupla, 1 - Somente uma aspa dupla, 2 = Duas aspas duplas (String)
    short sum = 0;
    unsigned long tamanho = strlen(str);
    for (int i = 0; i < tamanho; ++i) {
        if (str[i] == '"')
            sum++;
    }
    return sum;
}
void Lexico::parse(gchar *str)
{
    int atual = 0, proximo = 0;
    unsigned long len = strlen(str);
    while (proximo <= len && atual <= proximo) {
        if (ehEspaco(str[proximo]) || ehQuebra(str[proximo])) {
            str[proximo] = ' ';
        }
        // Caso o caractere é um digito ou letra
        if (!ehSimbolo(str[proximo])) {
            proximo++;
        }

        if (ehSimbolo(str[proximo]) &&
            atual == proximo) // verifica se é um caractere de simbolos
        {
            if (ehRelacional(str[atual], str[proximo + 1])) {
                g_print("%c%c EH RELACIONAL\n", str[atual], str[proximo + 1]);
                Glib::ustring tmp;
                tmp.append(sizeof(gchar), str[atual]);
                tmp.append(sizeof(gchar), str[proximo+1]);

                proximo = proximo + 2;
                atual = proximo;
                if (tmp == "<>")
                    analisados.push_back(novo_token(Token::RELACIONAL_DIFERENTE, tmp));
                else if (tmp == ">=")
                    analisados.push_back(novo_token(Token::RELACIONAL_MAIOR_IGUAL, tmp));
                else if (tmp == "<=")
                    analisados.push_back(novo_token(Token::RELACIONAL_MENOR_IGUAL, tmp));
            }
            else if (ehAtribuicao(str[atual], str[proximo + 1])) {
                g_print("%c%c EH OPERADOR DE ATRIBUIÇÃO\n", str[atual], str[proximo + 1]);
                analisados.push_back(novo_token(Token::ATRIBUICAO
                        ,Glib::ustring().append(sizeof(gchar)
                                ,str[atual]).append(sizeof(gchar), str[proximo+1])));

                proximo = proximo + 2;
                atual = proximo;

            }
            else {
                if (ehOperador(str[proximo])) {
                    g_print("%c EH OPERADOR\n", str[proximo]);
                    Glib::ustring tmp;
                    tmp.append(sizeof(gchar), str[proximo]);

                    if (tmp == "<")
                        analisados.push_back(novo_token(Token::RELACIONAL_MENOR, tmp));
                    else if (tmp == ">")
                        analisados.push_back(novo_token(Token::RELACIONAL_MAIOR, tmp));
                    else if (tmp == "=")
                        analisados.push_back(novo_token(Token::RELACIONAL_IGUAL, tmp));
                    else if (tmp == "+")
                        analisados.push_back(novo_token(Token::ARITMETICO_SOMA, tmp));
                    else if (tmp == "-")
                        analisados.push_back(novo_token(Token::ARITMETICO_SUBTRACAO, tmp));
                    else if (tmp == "*")
                        analisados.push_back(novo_token(Token::ARITMETICO_MULTIPLICACAO, tmp));
                    else if (tmp == "/")
                        analisados.push_back(novo_token(Token::ARITMETICO_DIVISAO, tmp));

                }

                if (ehEspecial(str[proximo])) {
                    g_print("%c EH CARACTERE ESPECIAL\n", str[proximo]);
                    if (str[proximo] == '(')
                        analisados.push_back(novo_token(Token::ESPECIAL_ABRE_PARENTESES, Glib::ustring().append(sizeof(gchar), str[proximo])));
                    else if (str[proximo] == ')')
                        analisados.push_back(novo_token(Token::ESPECIAL_FECHA_PARENTESES, Glib::ustring().append(sizeof(gchar), str[proximo])));
                }
                proximo++;
                atual = proximo;
            }
        }
        else if (ehSimbolo(str[proximo]) && atual != proximo ||
                 (proximo == len
                  && atual != proximo)) {
            gchar *sub = subString(str, atual, proximo - 1);
            // Verifica se a substring é uma palavra reservada, identificador, string ou numero
            if (ehReservada(sub)) {
                g_print("%s PALAVRA_RESERVADA\n", sub);
                Glib::ustring tmp;
                tmp = sub;
                if (tmp == "begin")
                    analisados.push_back(novo_token(Token::RESERVADA_BEGIN, tmp));
                else if (tmp == "end")
                    analisados.push_back(novo_token(Token::RESERVADA_END, tmp));
                else if (tmp == "if")
                    analisados.push_back(novo_token(Token::RESERVADA_IF, tmp));
                else if (tmp == "then")
                    analisados.push_back(novo_token(Token::RESERVADA_THEN, tmp));
                else if (tmp == "else")
                    analisados.push_back(novo_token(Token::RESERVADA_ELSE, tmp));
                else if (tmp == "case")
                    analisados.push_back(novo_token(Token::RESERVADA_CASE, tmp));
                else if (tmp == "for")
                    analisados.push_back(novo_token(Token::RESERVADA_FOR, tmp));
                else if (tmp == "in")
                    analisados.push_back(novo_token(Token::RESERVADA_IN, tmp));
                else if (tmp == "and")
                    analisados.push_back(novo_token(Token::RESERVADA_AND, tmp));
                else if (tmp == "or")
                    analisados.push_back(novo_token(Token::RESERVADA_OR, tmp));
                else if (tmp == "const")
                    analisados.push_back(novo_token(Token::RESERVADA_CONST, tmp));
                else if (tmp == "string")
                    analisados.push_back(novo_token(Token::RESERVADA_STRING, tmp));
                else if (tmp == "double")
                    analisados.push_back(novo_token(Token::RESERVADA_DOUBLE, tmp));
                else if (tmp == "float")
                    analisados.push_back(novo_token(Token::RESERVADA_FLOAT, tmp));
                else if (tmp == "int")
                    analisados.push_back(novo_token(Token::RESERVADA_INT, tmp));
                else if (tmp == "long_int")
                    analisados.push_back(novo_token(Token::RESERVADA_LONG_INT, tmp));
                else if (tmp == "short_int")
                    analisados.push_back(novo_token(Token::RESERVADA_SHORT_INT, tmp));
                else if (tmp == "bool")
                    analisados.push_back(novo_token(Token::RESERVADA_BOOL, tmp));
                else if (tmp == "char")
                    analisados.push_back(novo_token(Token::RESERVADA_CHAR, tmp));


            }
            else if (ehNumero(sub)) {
                analisados.push_back(novo_token(Token::NUMERO, Glib::ustring(sub)));
                g_print("%s NUMERO\n", sub);
            }
            else if (ehString(sub) == 2) {
                g_print("%s EH STRING\n", sub);
            }
            else if (identificadorValido(sub) &&
                     ehString(sub) == 0 &&
                     !ehReservada(sub) &&
                     !ehSimbolo(str[proximo - 1])) {
                g_print("%s IDENTIFICADOR VALIDO\n", sub);
                analisados.push_back(novo_token(Token::IDENTIFICADOR, Glib::ustring(sub)));
            }
            else if (!identificadorValido(sub) &&
                     ehString(sub) != 0 || ehString(sub) != 2 &&
                                           !ehReservada(sub) &&
                                           !ehSimbolo(str[proximo - 1])) {
                g_print("%s NAO EH UM IDENTIFICADOR VALIDO\n", sub);
            }

            atual = proximo;
        }
    }
}
bool Lexico::ehRelacional(gchar esquerda, gchar direita)
{
    if (esquerda == '<') {
        if (direita == '>') //Diferente
            return true;

        if (direita == '=') //Menor ou Igual
            return true;
    }
    else if (esquerda == '>') {
        if (direita == '=') // Maior ou Igual;
            return true;
    }
    return false;
}

bool Lexico::ehAtribuicao(gchar esquerda, gchar direita)
{
    if (esquerda == ':') {
        if (direita == '=') //Atribuição
            return true;
    }
    return false;
}

Lexico::~Lexico() = default;

Lexico::Lexico() = default;

std::vector<Token> Lexico::get_tokens() {
    return analisados;
}

Token Lexico::novo_token(Token::Tipo tipo, Glib::ustring conteudo) {
    Token t;
    t.set_conteudo(std::move(conteudo));
    t.set_token(tipo);
    return t;
}

void Token::set_conteudo(Glib::ustring cont) {
    this->conteudo = std::move(cont);
}

void Token::set_token(Tipo tipo) {
    this->tipo_token = tipo;
}

Glib::ustring Token::get_conteudo() {
    return this->conteudo;
}

Token::~Token() = default;

Token::Tipo Token::get_tipo() {
    return this->tipo_token;
}

void Lexico::print_tokens(std::vector<Token> analisados) {

    g_print("----PRINTANDO TOKENS----\n");
    Glib::ustring tmp;
    for (auto &t : analisados) {
        switch (t.get_tipo()) {
            case 0:
                tmp = "ATRIBUICAO \n" ;
                break;
            case 1:
                tmp = "ARITMETICO_SOMA \n" ;
                break;
            case 2:
                tmp = "ARITMETICO_SUBTRACAO \n" ;
                break;
            case 3:
                tmp = "ARITMETICO_MULTIPLICACAO \n" ;
                break;
            case 4:
                tmp = "ARITMETICO_DIVISAO \n" ;
                break;
            case 5:
                tmp = "RELACIONAL_IGUAL \n" ;
                break;
            case 6:
                tmp = "RELACIONAL_DIFERENTE \n" ;
                break;
            case 7:
                tmp = "RELACIONAL_MAIOR \n" ;
                break;
            case 8:
                tmp = "RELACIONAL_MENOR \n" ;
                break;
            case 9:
                tmp = "RELACIONAL_MAIOR_IGUAL \n" ;
                break;
            case 10:
                tmp = "RELACIONAL_MENOR_IGUAL \n" ;
                break;
            case 11:
                tmp = "ESPECIAL_ABRE_PARENTESES \n" ;
                break;
            case 12:
                tmp = "ESPECIAL_FECHA_PARENTESES \n" ;
                break;
            case 13:
                tmp = "SEPARADOR_PONTO_VIRGULA \n" ;
                break;
            case 14:
                tmp = "SEPARADOR_VIRGULA \n" ;
                break;
            case 15:
                tmp = "RESERVADA_BEGIN \n" ;
                break;
            case 16:
                tmp = "RESERVADA_END \n" ;
                break;
            case 17:
                tmp = "RESERVADA_IF \n" ;
                break;
            case 18:
                tmp = "RESERVADA_THEN \n" ;
                break;
            case 19:
                tmp = "RESERVADA_ELSE \n" ;
                break;
            case 20:
                tmp = "RESERVADA_CASE \n" ;
                break;
            case 21:
                tmp = "RESERVADA_FOR \n" ;
                break;
            case 22:
                tmp = "RESERVADA_IN \n" ;
                break;
            case 23:
                tmp = "RESERVADA_AND \n" ;
                break;
            case 24:
                tmp = "RESERVADA_CONST \n" ;
                break;
            case 25:
                tmp = "RESERVADA_STRING \n" ;
                break;
            case 26:
                tmp = "RESERVADA_DOUBLE \n" ;
                break;
            case 27:
                tmp = "RESERVADA_FLOAT \n" ;
                break;
            case 28:
                tmp = "RESERVADA_INT \n" ;
                break;
            case 29:
                tmp = "RESERVADA_LONG_INT \n" ;
                break;
            case 30:
                tmp = "RESERVADA_SHORT_INT \n" ;
                break;
            case 31:
                tmp = "RESERVADA_BOOL \n" ;
                break;
            case 32:
                tmp = "RESERVADA_CHAR \n" ;
                break;
            case 33:
                tmp = "RESERVADA_OR \n" ;
                break;
            case 34:
                tmp = "IDENTIFICADOR \n" ;
                break;
            case 35:
                tmp = "NUMERO \n" ;
                break;
            case Token::NADA:
                break;
        }
        g_print("%s : %s ", t.get_conteudo().c_str(), tmp.c_str());
    }
}

Token::Token() = default;
