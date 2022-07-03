//
// Created by felipe on 15/05/22.
//

#include "sintatico.h"
#include <iostream>
#include <stdexcept>

Sintatico::~Sintatico() = default;

Sintatico::Sintatico() = default;

bool valida_declaracoes(Token t);

bool valida_declaracoes(Token t);

void Sintatico::analisar(std::vector<Token> pilha) {
  std::vector<Token> pilha_aux = pilha;
  int pos = 0;
  Token proximo_token, anterior_token, atual_token;
  std::vector<Token> controle_vector;

  while (pos < pilha.size()) {
    atual_token = pilha[pos];

    if (validar_prox_token(atual_token, nextToken(pilha_aux, pos),
                           controle_vector, pos)) {
      pos++;
    } else {
      break;
    }
  }
  try {
    if (!controle_vector.empty()){
      throw std::runtime_error("Erro de sintaxe, esperava End");
    }
  }
  catch (std::exception &e) {
  std::cout << e.what() << std::endl;
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

bool Sintatico::valida_declaracoes(Token t) {
  return (t.get_tipo() == Token::RESERVADA_INT ||
          t.get_tipo() == Token::RESERVADA_LONG_INT ||
          t.get_tipo() == Token::RESERVADA_FLOAT ||
          t.get_tipo() == Token::RESERVADA_DOUBLE ||
          t.get_tipo() == Token::RESERVADA_BOOL);
}

bool Sintatico::valida_inicio_bloco(Token t) {
  return (t.get_tipo() == Token::RESERVADA_IF ||
          t.get_tipo() == Token::RESERVADA_FOR ||
          t.get_tipo() == Token::RESERVADA_CASE);
}

bool Sintatico::valida_relacionais(Token t) {
  return t.get_tipo() == Token::RELACIONAL_MAIOR ||
         t.get_tipo() == Token::RELACIONAL_MENOR ||
         t.get_tipo() == Token::RELACIONAL_IGUAL ||
         t.get_tipo() == Token::RELACIONAL_MENOR_IGUAL ||
         t.get_tipo() == Token::RELACIONAL_MAIOR_IGUAL ||
         t.get_tipo() == Token::RELACIONAL_DIFERENTE;
}

bool Sintatico::valida_operadores_logico(Token t) {
  return t.get_tipo() == Token::RESERVADA_AND||
         t.get_tipo() == Token::RESERVADA_OR;
}

bool Sintatico::validar_prox_token(Token atual_token, Token prox_token,
                                   std::vector<Token>& vector_controle,
                                   int pos) {
  try {
    // BEGIN.
    if (atual_token.get_tipo() == Token::RESERVADA_BEGIN) {
      if (!valida_inicio_bloco(prox_token) && !valida_declaracoes(prox_token) &&
          prox_token.get_tipo() != Token::RESERVADA_END) {
        throw std::invalid_argument("Inicializador");
      } else {
        // Quando abre bloco begin, adiciona no vetor de controle.
        vector_controle.push_back(atual_token);
      }
    }
    // DECLARAÇÃO, int, float..
    else if (Sintatico::valida_declaracoes(atual_token)) {
      if (prox_token.get_tipo() != Token::IDENTIFICADOR) {
        throw std::invalid_argument("Identificador");
      } else {
        return true;
      }
    }
    // ATRIBUIÇÃO
    else if (atual_token.get_tipo() == Token::ATRIBUICAO) {
      if (prox_token.get_tipo() != Token::NUMERO &&
          prox_token.get_tipo() != Token::RESERVADA_CHAR &&
          prox_token.get_tipo() != Token::IDENTIFICADOR)
        throw std::invalid_argument("Atribuicao");
    }
    // BLOCO INICIAL
    else if (valida_inicio_bloco(atual_token)) {
      if (prox_token.get_tipo() != Token::ESPECIAL_ABRE_PARENTESES)
        throw std::invalid_argument("Parentese");
      else {
        // Quando abre parentese, adiciona no vetor de controle pois necessita
        // de fechamento.
        vector_controle.push_back(atual_token);
        vector_controle.push_back(prox_token);
      }
    }
    else if (atual_token.get_tipo() == Token::RESERVADA_THEN){
      vector_controle.push_back(atual_token);
    }
    // PARENTESE INICIAL
    else if (atual_token.get_tipo() == Token::ESPECIAL_ABRE_PARENTESES) {
      if (prox_token.get_tipo() != Token::IDENTIFICADOR &&
          prox_token.get_tipo() != Token::NUMERO) {
        throw std::invalid_argument("Identificador ou Numero");
      }
    } else if (Sintatico::valida_relacionais(atual_token) || Sintatico::valida_operadores_logico(atual_token)) {
      if (prox_token.get_tipo() != Token::IDENTIFICADOR &&
          prox_token.get_tipo() != Token::NUMERO) {
        throw std::invalid_argument("Identificador ou Numero");
      }
    } else if (Sintatico::valida_operadores(atual_token)) {
      if (prox_token.get_tipo() != Token::IDENTIFICADOR &&
          prox_token.get_tipo() != Token::NUMERO) {
        throw std::invalid_argument("Identificador ou Numero");
      }
    } else if ((atual_token.get_tipo() == Token::IDENTIFICADOR ||
                atual_token.get_tipo() == Token::NUMERO)  &&
               vector_controle.back().get_tipo() ==
                   Token::ESPECIAL_ABRE_PARENTESES) {
        if (prox_token.get_tipo() != Token::ESPECIAL_FECHA_PARENTESES){
          if (!Sintatico::valida_relacionais(prox_token) &&
              !Sintatico::valida_operadores(prox_token) &&
              !Sintatico::valida_operadores_logico(prox_token)) {
            if (prox_token.get_tipo() != Token::ESPECIAL_FECHA_PARENTESES){
              throw std::invalid_argument("Fechamento de Parentese");
            }
            else
              throw std::invalid_argument("Condicional ou Operador");
          }
        }
    } else if (atual_token.get_tipo() == Token::ESPECIAL_FECHA_PARENTESES) {
      vector_controle.pop_back();

      if (vector_controle.back().get_tipo() == Token::RESERVADA_IF) {
        if (prox_token.get_tipo() != Token::RESERVADA_THEN) {
          throw std::invalid_argument("then");
        }
        //std::cout << vector_controle.back().get_conteudo();
        vector_controle.pop_back();
      }
    }
    /*else if (atual_token.get_tipo() == Token::NUMERO
             atual_token.get_tipo() == Token::IDENTIFICADOR) nn compila pls*/
    // Validacao parentese aberto
    else if (prox_token.get_tipo() == Token::RESERVADA_THEN &&
             vector_controle.back().get_tipo() ==
                 Token::ESPECIAL_ABRE_PARENTESES) {
      throw std::invalid_argument("Fechamento Parentese");
    }

    else
    if (atual_token.get_tipo() == Token::RESERVADA_END) {
        // Quando fecha bloco end, remove do vetor de controle.
        if (vector_controle.back().get_tipo() == Token::RESERVADA_THEN || vector_controle.back().get_tipo() == Token::RESERVADA_BEGIN) {
          vector_controle.pop_back();
        }
    }


    return true;
  } catch (const std::invalid_argument& e) {
    std::cout << "Lido "
              << "\033[1;35m" << atual_token.get_conteudo() << "\033[0m";
    std::cout << " Esperava: "
              << "\033[1;31m" << e.what() << "\033[0m";
    std::cout << " Recebido: "
              << "\033[1;31m" << prox_token.get_conteudo() << "\033[0m\n";
    return false;
  }
}
bool Sintatico::valida_operadores(Token token) {
  return token.get_tipo() == Token::ARITMETICO_DIVISAO ||
         token.get_tipo() == Token::ARITMETICO_MULTIPLICACAO ||
         token.get_tipo() == Token::ARITMETICO_SOMA ||
         token.get_tipo() == Token::ARITMETICO_SUBTRACAO;
}
