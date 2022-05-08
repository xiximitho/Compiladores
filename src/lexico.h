// Created by felipe on 4/17/22.
//

#ifndef _LEXICO_H_
#define _LEXICO_H_

#include <glibmm/refptr.h>
#include <gtkmm/textbuffer.h>

class Token{
    enum Tipo{
        OP_MAIS = 0,
        OP_MENOS = 1,
        OP_DIV   = 2,
        OP_MULT  = 3,
    };
    Glib::ustring conteudo;
};

class Lexico {
public:
    ~Lexico();
    Lexico();

    static void parse(gchar *str);
    std::vector<Token> get_tokens();
private:
    std::vector<Token> analisados;

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
