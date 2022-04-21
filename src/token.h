//
// Created by felipe on 4/18/22.
//

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <glibmm/ustring.h>

enum TOKEN{
    TK_IDENTIFIER
  , TK_NUMBER
  , TK_OPERATOR
  , TK_PONTUACTION
  , TK_ASSIGN
  , TK_IF
  , TK_THEN
  , TK_ELSE
  , TK_CASE
  , TK_FOR
  , TK_END
  , TK_IN
  , TK_BEGIN
  , TK_FLOAT
  , TK_DOUBLE
  , TK_INT
  , TK_LONG
  , TK_SHORT
  , TK_BOOL
  , TK_NULL
};


class Token {
 public:
  Token (TOKEN type, const std::string &text);
  Token ();
  ~Token();

  TOKEN get_type () const;
  void set_type (TOKEN type);
  std::string get_text ();
  void set_text (const std::string text);

 private:
  TOKEN type;
  std::string text;
};

#endif //_TOKEN_H_

/*
  enum Token {
      // Tokens de blocos condicionais
      If,
      Then,
      Else,
      Case,
      For,
      End,
      In,
      Begin,

      // Tokens de comparação
      min,       // <
      min_eq,    // <=
      big,       // >
      big_eq,    // >=
      dif,       // <>
      eq,        // =

      // Token de atribuição
      attr,      // :=

      // Tokens aritméticos
      minus,     // -
      plus,      // +
      mult,      // *
      div,       // /

      //Tokens separadores
      comma,     // ,
      semicolon, // ;

      open_parentheses,  // (
      close_parentheses, // )

      //Token para não retornar nada, em C++ não é possível usar Null em qualquer tipo de retorno;
      empty
  };

 * */