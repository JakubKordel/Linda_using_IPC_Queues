#ifndef UNIX_PROJEKT_LEXER_H
#define UNIX_PROJEKT_LEXER_H

#include "Source.h"
#include "Token.h"

class Lexer
{
private:
    Source source;
    Token token;
    std::pair<int, int> position;
    bool build_keyword();
    bool build_number();
    bool build_string();
    bool build_char_token();
    int build_integer();
    Token build_float();
    bool extend_undefined();
public:
    Lexer(Source);
    Token next_token();
    Token get_token();
};

#endif //UNIX_PROJEKT_LEXER_H
