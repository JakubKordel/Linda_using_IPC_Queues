#ifndef UNIX_PROJEKT_TOKEN_H
#define UNIX_PROJEKT_TOKEN_H

#include <utility>
#include "Addons.h"

class Token
{
private:
    union TokenValue
    {
        int i;
        float f;
        std::string s;
    };

    addons::TokenType type;
    std::pair<int, int> position;
    TokenValue value;

public:
    Token(addons::TokenType, std::pair<int, int>, TokenValue);
    Token(addons::TokenType, std::pair<int, int>);
    addons::TokenType get_type();
    std::pair<int, int> get_position();
    int get_value_integer();
    float get_value_float();
    std::string get_value_string();
};

#endif //UNIX_PROJEKT_TOKEN_H
