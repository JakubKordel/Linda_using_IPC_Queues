#include "Parser.h"
#include <iostream>

int main()
{
    //std::string krotka = "output(2.5, 4e+7, 12, \"abcd\")";
    std::string krotka = "input(integer:1, string:*, float:>=.6)";
    Parser parser = Parser(krotka);
    Msg msg = parser.parse();

    return 0;
}
