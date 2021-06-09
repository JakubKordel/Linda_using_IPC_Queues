#include "Source.h"

Source::Source(std::string code)
{
    position = std::make_pair(1, 0);
    program << code;
    next_character();
}

char Source::next_character()
{
    char c = '\0';
    if(program.get(c))
    {
        if(c == '\n')
            position = std::make_pair(position.first + 1, position.second);
        else
            position = std::make_pair(position.first, position.second + 1);
    }

    character = c;
    return character;
}

char Source::get_character()
{
    return character;
}

int Source::get_position()
{
    return position;
}
