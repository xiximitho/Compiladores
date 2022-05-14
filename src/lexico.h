// Created by felipe on 4/17/22.
//

#ifndef _LEXICO_H_
#define _LEXICO_H_

#include <glibmm/refptr.h>
#include <gtkmm/textbuffer.h>
#include <vector>

class Token{
public:
    enum Tipo{
        ATRIBUICAO = 0,
        ARITMETICO_SOMA = 1,
        ARITMETICO_SUBTRACAO = 2,
        ARITMETICO_MULTIPLICACAO = 3,
        ARITMETICO_DIVISAO = 4,
        RELACIONAL_IGUAL = 5,
        RELACIONAL_DIFERENTE = 6,
        RELACIONAL_MAIOR = 7,
        RELACIONAL_MENOR = 8,
        RELACIONAL_MAIOR_IGUAL = 9,
        RELACIONAL_MENOR_IGUAL = 10,
        ESPECIAL_ABRE_PARENTESES = 11,
        ESPECIAL_FECHA_PARENTESES = 12,
        SEPARADOR_PONTO_VIRGULA = 13,
        SEPARADOR_VIRGULA = 14,

        //RESERVADAS
        RESERVADA_BEGIN = 15,
        RESERVADA_END = 16,
        RESERVADA_IF = 17,
        RESERVADA_THEN = 18,
        RESERVADA_ELSE = 19,
        RESERVADA_CASE = 20,
        RESERVADA_FOR = 21,
        RESERVADA_IN = 22,
        RESERVADA_AND = 23,
        RESERVADA_CONST = 24,
        RESERVADA_STRING = 25,
        RESERVADA_DOUBLE = 26,
        RESERVADA_FLOAT = 27,
        RESERVADA_INT = 28,
        RESERVADA_LONG_INT = 29,
        RESERVADA_SHORT_INT = 30,
        RESERVADA_BOOL = 31,
        RESERVADA_CHAR = 32,
        RESERVADA_OR = 33,

        //IDENTIFICADORES
        IDENTIFICADOR = 34,
        NUMERO = 35,
    };
    Token();
    ~Token();

    void set_token(Tipo);
    void set_conteudo(Glib::ustring cont);
    Glib::ustring get_conteudo();
    Tipo get_tipo();
private:
    Tipo tipo_token;
    Glib::ustring conteudo;
};

class Lexico {
public:
    ~Lexico();
    Lexico();

    void parse(gchar *str);
    std::vector<Token> get_tokens();
    void print_tokens(std::vector<Token>);
private:
    std::vector<Token> analisados = {};

    static Token novo_token(Token::Tipo tipo, Glib::ustring conteudo);
    static bool ehSimbolo(gchar ch);
    static bool identificadorValido(gchar *str);
    static bool ehOperador(gchar ch);
    static bool ehReservada(gchar *str);
    static bool ehNumero(gchar *str);
    static bool ehEspecial(gchar ch);
    static bool ehEspaco(gchar chr);
    static int ehString(gchar *str);
    static bool ehRelacional(gchar esquerda, gchar direita);
    static bool ehAtribuicao(gchar esquerda, gchar direita);
    static gchar *subString(const gchar *baseStr, int primeiro, int ultimo);
};

#endif //_LEXICO_H_
