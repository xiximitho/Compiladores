// Created by felipe on 4/17/22.
//

#ifndef _LEXICO_H_
#define _LEXICO_H_

#include <glibmm/refptr.h>
#include <gtkmm/textbuffer.h>

class Lexico {
 public:
  ~Lexico ();
  Lexico();

  // Tokens de blocos condicionais
  enum Token_condition {
      If,
      Then,
      Else,
      Case,
      For,
      End,
      In,
      Begin,
      Nothing
  };

  // Tokens de comparação
  enum Token_relation {
   min,      // <
   min_eq,   // <=
   big,      // >
   big_eq,   // >=
   dif,      // <>
   eq        // =
  };

  // Token de atribuição
  enum Token_attrib {
      attr  // :=
  };

  // Tokens aritméticos
  enum Token_arithmetic {
      minus,  // -
      plus ,  // +
      mult,   // *
      div     // /
  };

  //Tokens separadores
  enum Token_separators {
      comma, // ,
      semicolon // ;
  };

  enum Token_specials {
      open_parentheses, // (
      close_parentheses // )
  };

  Token_condition last_cond_token ();
  Token_arithmetic last_arith_token ();

  void identificar(Glib::ustring texto);

 protected:

 private:

  std::vector<Token_condition>  current_cond_token{};
  std::vector<Token_arithmetic> current_arith_token{};
  std::vector<Token_attrib>     current_attrib_token{};
  std::vector<Token_relation>   current_rel_token{};
  std::vector<Token_separators> current_sep_token{};
  std::vector<Token_specials>   current_spec_token{};

};

#endif //_LEXICO_H_
