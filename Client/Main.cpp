#include "Parser.h"
#include <iostream>
#include "linda.h"

void print_tuple(Tuple tuple);

int main()
{
    Msg msg;
    linda_init();
    std::string request;
    int timeout;
    char c;

    while(1)
    {
        std::cout << "Input tuple or pattern (in one line):" << std::endl;
        getline(std::cin, request);
        if(request.empty())
            break;

        Parser parser = Parser(request);
        msg = parser.parse();

        if(msg.option == 0 || msg.option == 1)
        {
            std::cout << "Input timeout: ";
            std::cin >> timeout;
            while(std::cin.get(c) && c != '\n');

            if(timeout < 1)
            {
                std::cout << "Expected timeout value - integer > 0\n";
                return 1;
            }
        }

        if(msg.option == 0)         // read
        {
            print_tuple(linda_read(msg.req.pattern, timeout));
        }
        else if(msg.option == 1)    // input
        {
            print_tuple(linda_input(msg.req.pattern, timeout));
        }
        else                        // output
        {
            linda_output(msg.req.tuple);
            std::cout << "Tuple send" << std::endl;
        }
    }

    linda_close();
    return 0;
}

void print_tuple(Tuple tuple)
{
    if(tuple.tel_amount == -1)
    {
        std::cout << "Timeout - no tuple matching given pattern" << std::endl;
        return;
    }

    bool first = true;
    std::cout << "Received tuple:\n(";
    for(int i = 0; i < tuple.tel_amount; i++)
    {
        if(first)
            first = false;
        else
            std::cout << ", ";
        
        switch(tuple.tel[i].type)
        {
        case 0:
            std::cout << tuple.tel[i].value.i;
            break;
        
        case 1:
            std::cout << tuple.tel[i].value.s;
            break;

        default:
            std::cout << tuple.tel[i].value.f;
            break;
        }
    }

    std::cout << ")\n";
}
