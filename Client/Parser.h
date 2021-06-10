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
public:
    explicit Parser(const std::string&);
    Msg parse();
    static void throw_parsing_error(const std::string& msg, std::pair<int, int> pos);
};

#endif //UNIX_PROJEKT_PARSER_H
