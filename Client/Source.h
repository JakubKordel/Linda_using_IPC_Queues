#ifndef UNIX_PROJEKT_SOURCE_H
#define UNIX_PROJEKT_SOURCE_H

#include <string>
#include <sstream>
#include <utility>

class Source
{
private:
    char character;
    std::stringstream program;
    std::pair<int, int> position;

public:
    explicit Source(const std::string&);
    Source();
    char next_character();
    char get_character() const;
    std::pair<int, int> get_position();
};

#endif //UNIX_PROJEKT_SOURCE_H
