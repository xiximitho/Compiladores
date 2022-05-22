//
// Created by felipe on 15/05/22.
//

#include <iostream>
#include "sintatico.h"

Sintatico::~Sintatico() = default;

Sintatico::Sintatico() = default;

void Sintatico::analisar(std::vector<Token> pilha) {
    std::vector<Token> pilha_aux = pilha;
    int pos = 0;
    Token proximo_token;
    Token anterior_token;
    while (pos < pilha.size()) {
        std::cout << "Token: " << pilha[pos].get_conteudo() << std::endl;
        proximo_token = nextToken(pilha, pos);
        anterior_token = previousToken(pilha, pos);
        /*
         *
         * REGRAS.
         * se.. o tokenatual = X e o proximo_token = Y então ..... desempilha.
         *
        */

        pos ++;
    }
}

Token Sintatico::nextToken(std::vector<Token> pilha, int pos_atual) {
    pos_atual = pos_atual + 1;
    Token token;
    if (pos_atual < pilha.size()) {
        return pilha[pos_atual];
    } else {
        token.set_conteudo("EOF");
        token.set_token(Token::NADA);
        return token;
    }
}

Token Sintatico::previousToken(std::vector<Token> pilha, int pos_atual) {
    Token token;
    pos_atual = pos_atual - 1;
    if (pos_atual >= 0) {
        return pilha[pos_atual];
    } else {
        token.set_conteudo("SOF");
        token.set_token(Token::NADA);
        return token;
    }
}


