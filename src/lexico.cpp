//
// Created by felipe on 4/17/22.
//

#include <iostream>
#include "lexico.h"

Lexico::~Lexico ()
{

}

Lexico::Lexico ()
{
  current_cond_token.clear ();
  current_arith_token.clear ();
  current_attrib_token.clear ();
  current_rel_token.clear ();
  current_sep_token.clear ();
  current_spec_token.clear ();
}

Lexico::Token_condition Lexico::last_cond_token ()
{
  if (!current_cond_token.empty ())
    return current_cond_token.back ();
  else
    return Token_condition::Nothing;
}
Lexico::Token_arithmetic Lexico::last_arith_token ()
{
  return current_arith_token.back ();
}

void Lexico::identificar (Glib::ustring texto)
{

  Glib::ustring last_word = {};
  gchar last_char = {};
  gchar curr_char = {};

  //Vetor para armazenar os caracteres e verificar os tokens.
  for (int i = 0; i < texto.length (); i++)
    {
      curr_char = texto[i];

      if (last_word.length () != 0)
        {
          last_char = last_word[last_word.length () - 1];
        }
      else
        {
          last_char = curr_char;
        }
      last_word.push_back (curr_char);

      std::cout << "cur_char :' " << curr_char << std::endl;
      std::cout << "last_char :' " << gchar (last_char) << std::endl;

      /* Token IF */
      if (last_char == '\n' || std::isspace (last_char))
        {
          if (curr_char == 'I')
            {
              std::cout << "Atribuindo 'I' " << std::endl;
              last_word.push_back (curr_char);
            }
        }

      if (curr_char == 'f' && last_char == 'I')
        {
          std::cout << "Atribuindo 'f' " << std::endl;
          last_word.push_back (curr_char);
        }

      if ((curr_char == '\n' || std::isspace (curr_char)) && last_char == 'f')
        {
          std::cout << "Adicionando token IF" << std:: endl;
          current_cond_token.push_back (Token_condition::If);
        }
      /* Fim Token IF */

      std::cout.flush ();
    }

}
