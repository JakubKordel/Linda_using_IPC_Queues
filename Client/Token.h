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
        char s[20];
    };

    addons::TokenType type;
    std::pair<int, int> position;
    TokenValue value{};

public:
    Token(addons::TokenType, std::pair<int, int>, const char*);
    Token(addons::TokenType, std::pair<int, int>, int);
    Token(addons::TokenType, std::pair<int, int>, float);
    Token(addons::TokenType, std::pair<int, int>);
    Token();
    addons::TokenType get_type();
    std::pair<int, int> get_position();
    int get_value_integer() const;
    float get_value_float() const;
    char* get_value_string();
};

#endif //UNIX_PROJEKT_TOKEN_H
