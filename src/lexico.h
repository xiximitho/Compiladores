// Created by felipe on 4/17/22.
//

#ifndef _LEXICO_H_
#define _LEXICO_H_

#include <glibmm/refptr.h>
#include <gtkmm/textbuffer.h>

class Lexico {
public:
  ~Lexico();
  Lexico();

  void parse(const char *str);

private:
  bool ehSimbolo(char ch);
  bool identificadorValido(char *str);
  bool ehOperador(char ch);
  bool ehReservada(char *str);
  bool ehNumero(char* str);
  bool ehEspecial(char ch);
  bool ehRelacional(char esquerda, char direita);
  bool ehAtribuicao(char esquerda, char direita);
  char *subString(const char *baseStr, int l, int r);
};

#endif //_LEXICO_H_
