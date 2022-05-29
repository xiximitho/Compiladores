//
// Created by felipe on 15/05/22.
//

#ifndef GTKMM_ANALISADOR_SINTATICO_H
#define GTKMM_ANALISADOR_SINTATICO_H
#include "lexico.h"
#include <vector>

class Sintatico {
    public:
    Sintatico();
    ~Sintatico();

    void analisar(std::vector<Token> pilha);
private:
    static Token nextToken(std::vector<Token> pilha, int pos_atual);
    static Token previousToken(std::vector<Token> pilha, int pos_atual);

    bool validar_prox_token(Token atual_token, Token prox_token, std::vector<Token> &controle, int pos);

    static bool valida_declaracoes(Token t);
    static bool valida_inicio_bloco(Token t);
	static bool valida_relacionais(Token t);
};


#endif //GTKMM_ANALISADOR_SINTATICO_H
