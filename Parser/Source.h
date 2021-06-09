#ifndef UNIX_PROJEKT_SOURCE_H
#define UNIX_PROJEKT_SOURCE_H

#include <string>
#include <stringstream>
#include <utility>

class Source
{
private:
    char character;
    std::stringstream program;
    std:pair<int, int> position;

public:
    Source(std::string);
    char next_character();
    char get_character();
    std::pair<int, int> get_position();
};

#endif //UNIX_PROJEKT_SOURCE_H
