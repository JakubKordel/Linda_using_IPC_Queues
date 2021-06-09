#include "Token.h"

Token::Token(addons::TokenType t, std::pair<int, int> pos, TokenValue val)
{
    type = t;
    position = pos;
    value = val;
}

Token::Token(addons::TokenType t, std::pair<int, int> pos)
{
    type = t;
    position = pos;
}

addons::TokenType Token::get_type()
{
    return type;
}

int Token::get_position()
{
    return position;
}

int Token::get_value_integer()
{
    return value.i;
}

float Token::get_value_float()
{
    return value.f;
}

std::string Token::get_value_string()
{
    return value.s;
}
