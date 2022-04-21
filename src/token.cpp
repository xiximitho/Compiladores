//
// Created by felipe on 4/18/22.
//

#include "token.h"

Token::Token (TOKEN type, const std::string &text)
{
  this->type = type;
  this->text = text;
}
TOKEN Token::get_type () const
{
  return type;
}
void Token::set_type (TOKEN type)
{
  Token::type = type;
}

std::string Token::get_text ()
{
  return text;
}
void Token::set_text (const std::string text)
{
  this->text = text;
}
Token::Token ()
{

}
Token::~Token ()
{
  text = "";
  type = TK_NULL;
}
