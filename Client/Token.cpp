#include "Token.h"
#include <cstring>

Token::Token(addons::TokenType t, std::pair<int, int> pos)
{
    type = t;
    position = pos;
}

addons::TokenType Token::get_type()
{
    return type;
}

std::pair<int, int> Token::get_position()
{
    return position;
}

int Token::get_value_integer() const
{
    return value.i;
}

float Token::get_value_float() const
{
    return value.f;
}

char* Token::get_value_string()
{
    return value.s;
}

Token::Token()
{
    type = addons::TokenType::UNDEFINED;
}

Token::Token(addons::TokenType t, std::pair<int, int> pos, const char *s)
{
    type = t;
    position = pos;
    strcpy(value.s, s);
}

Token::Token(addons::TokenType t, std::pair<int, int> pos, int i)
{
    type = t;
    position = pos;
    value.i = i;
}

Token::Token(addons::TokenType t, std::pair<int, int> pos, float f)
{
    type = t;
    position = pos;
    value.f = f;
}
