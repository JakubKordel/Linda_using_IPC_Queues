#include "Parser.h"
#include <iostream>
#include "linda.h"

int main()
{
    std::string krotka = "output(1, \"abcd\", 4.5)";
    std::string wzorzec = "input(integer:>=0, string:*, float:*)";
    linda_init();
    std::cout << "Init Linda" << std::endl;

    Parser parser = Parser(krotka);
    Msg msg = parser.parse();
    std::cout <<"Parsed tuple" << std::endl;
    linda_output(msg.req.tuple);
    std::cout << "Send tuple" << std::endl;

    parser = Parser(wzorzec);
    Msg msg2 = parser.parse();
    std::cout << "Parsed pattern" << std::endl;
    Tuple tupl = linda_input(msg2.req.pattern, 0);
    std::cout << "Send pattern and received tuple" << std::endl;

    std::cout << tupl.tel_amount << " " << msg.req.tuple.tel_amount << std::endl;
    std::cout << tupl.tel[0].type << " " << msg.req.tuple.tel[0].type << std::endl;
    std::cout << tupl.tel[0].value.i << " " << msg.req.tuple.tel[0].value.i << std::endl;
    
    std::cout << "Close Linda" << std::endl;
    linda_close();
    return 0;
}
