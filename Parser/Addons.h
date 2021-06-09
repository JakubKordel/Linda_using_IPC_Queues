#ifndef UNIX_PROJEKT_ADDONS_H
#define UNIX_PROJEKT_ADDONS_H

#include <map>
#include <string>
#include <vector>
#include <cstring>

namespace addons
{
    enum TokenType
    {
        END_OF_FILE,
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

    struct cmp_str
    {
        bool operator()(char const *a, char const *b) const
        {
            return std::strcmp(a, b) < 0;
        }
    };


    const std::map<const char*, TokenType, cmp_str> keywordMap {
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
