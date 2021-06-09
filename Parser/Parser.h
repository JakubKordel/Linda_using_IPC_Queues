#ifndef UNIX_PROJEKT_PARSER_H
#define UNIX_PROJEKT_PARSER_H

#include "Lexer.h"
#include "Structs.h"

class Parser
{
private:
    Lexer lexer;
    Request parse_tuple();
    Request parse_pattern();
    void throw_parsing_error(std::string);
public:
    Parser(Lexer);
    Msg parse();
};

#endif //UNIX_PROJEKT_PARSER_H
