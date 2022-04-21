//
// Created by felipe on 4/17/22.
//

#include "lexico.h"
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

Lexico::~Lexico()
{}

Lexico::Lexico()
{}

/*Verifica se é algum dos caracteres abaixo, ou seja, que possuem alguma ação diferente de chars e digitos.*/
bool Lexico::ehSimbolo(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
        ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' ||
        ch == '(' || ch == ')' || ch == ':' ) {
        return true;
    }
    return false;
}
bool Lexico::identificadorValido(char *str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' ||
        str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' ||
        str[0] == '8' || str[0] == '9' || ehSimbolo(str[0]) == true) {
        return false;
    } // Se o primeiro caractere da string for digito ou pontuacao o identificador não é valido.
    int i, len = strlen(str);
    if (len == 1) {
        return true;
    } // Se o tamanho da string = 1 a validação ja foi feita.
    else {
        for (i = 1; i < len;
             i++) // Identificador não pode conter caractere especiais.
        {
            if (ehSimbolo(str[i]) == true) {
                return false;
            }
        }
    }
    return true;
}
bool Lexico::ehOperador(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' ||
        ch == '<' || ch == '=') {
        return true;
    }
    return false;
}

bool Lexico::ehEspecial(char ch)
{
    if (ch == '(' || ch == ')') {
        return true;
    }
    return false;
}
bool Lexico::ehReservada(char *str)
{
    if (strcmp(str, "if") == 0 || strcmp(str, "then") == 0 ||
        strcmp(str, "else") == 0 || strcmp(str, "case") == 0 ||
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

bool Lexico::ehNumero(char *str)
{
    int i;
    int len = strlen(str);
    int nDecimal = 0;

    if (len == 0) {
        return false;
    }
    for (i = 0; i < len; i++) {
        if (nDecimal > 1 && str[i] == '.') {
            return false;
        }
        else if (nDecimal <= 1) {
            nDecimal++;
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

char *Lexico::subString(const char *baseStr, int l, int r)
{
    int i;
    char *str = (char *) malloc(sizeof(char) * (r - l + 2));
    for (i = l; i <= r; i++) {
        str[i - l] = baseStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}

void Lexico::parse(const char *str)
{
    int atual = 0, proximo = 0;
    int len = strlen(str);
    while (proximo <= len && atual <= proximo) {
        // Caso o caractere é um digito ou letra
        if (ehSimbolo(str[proximo]) == false) {
            proximo++;
        }

        if (ehSimbolo(str[proximo]) == true &&
            atual == proximo) // if character is a punctuator
        {
            if (ehRelacional(str[atual], str[proximo + 1])){
                std::cout << str[atual] << str[proximo+1] << " EH RELACIONAL\n";
                proximo = proximo+2;
                atual = proximo;
            }
            else if(ehAtribuicao(str[atual], str[proximo + 1])){
                std::cout << str[atual] << str[proximo+1] << " EH OPERADOR DE ATRIBUIÇÃO\n";
                proximo = proximo+2;
                atual = proximo;
            }
            else {
                if (ehOperador(str[proximo]) == true) {
                    std::cout << str[proximo] << " EH OPERADOR\n";
                }

                if (ehEspecial(str[proximo])){
                    std::cout << str[proximo] << " EH CARACTERE ESPECIAL\n";
                }
                proximo++;
                atual = proximo;
            }
        }
        else if (ehSimbolo(str[proximo]) == true && atual != proximo ||
            (proximo == len &&
                atual != proximo)) // check if parsed substring is a keyword or
            // identifier or number
        {
            char *sub = subString(str, atual, proximo - 1); // extract substring

            if (ehReservada(sub) == true) {
                cout << sub << " PALAVRA_RESERVADA\n";
            }
            else if (ehNumero(sub) == true) {
                cout << sub << " NUMERO\n";
            }
            else if (identificadorValido(sub) == true &&
                ehSimbolo(str[proximo - 1]) == false) {
                cout << sub << " IDENTIFICADOR VALIDO\n";
            }
            else if (identificadorValido(sub) == false &&
                ehSimbolo(str[proximo - 1]) == false) {
                cout << sub << " NAO EH UM IDENTIFICADOR VALIDO\n";
            }

            atual = proximo;
        }
    }
    return;
}
bool Lexico::ehRelacional(char esquerda, char direita)
{
    if (esquerda == '<') {
        if (direita == '>') //Diferente
            return true;

        if (direita == '=') //Menor ou Igual
            return true;
    } else if (esquerda == '>'){
        if (direita == '=') // Maior ou Igual;
            return true;
    }
    return false;
}

bool Lexico::ehAtribuicao(char esquerda, char direita)
{
    if (esquerda == ':') {
        if (direita == '=') //Atribuição
            return true;
    }
    return false;
}