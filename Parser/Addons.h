#ifndef UNIX_PROJEKT_ADDONS_H
#define UNIX_PROJEKT_ADDONS_H

#include <map>
#include <string>
#include <vector>

namespace addons
{
    enum TokenType
    {
        EOF,
        OUTPUT,
        INPUT,
        READ,
        INTEGER,
        FLOAT,
        STRING,
        INT_LITERAL,
        FLOAT_LITERAL,
        STR_LITERAL,
        STAR,
        COMMA,
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        COLON,
        LESS,
        LESS_EQUAL,
        MORE,
        MORE_EQUAL,
        UNDEFINED
    };

    const std::map<std::string, TokenType> keywordMap {
        {"output", TokenType::OUTPUT},
        {"input", TokenType::INPUT},
        {"read", TokenType::READ},
        {"integer", TokenType::INTEGER},
        {"float", TokenType::FLOAT},
        {"string", TokenType::STRING}
    };

    const std::vector<char> start_operators = {'*', ':', '(', ')', ',', '<', '>'};
}

#endif //UNIX_PROJEKT_ADDONS_H
