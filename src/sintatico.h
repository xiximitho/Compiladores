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
    Token nextToken(std::vector<Token> pilha, int pos_atual);
    void error(std::string msg);
};


#endif //GTKMM_ANALISADOR_SINTATICO_H
