#include "Source.h"

Source::Source(const std::string& code)
{
    position = std::make_pair(1, 0);
    program << code;
    character = '\0';
    next_character();
}

char Source::next_character()
{
    character = '\0';
    if(program.get(character))
    {
        if(character == '\n')
            position = std::make_pair(position.first + 1, position.second);
        else
            position = std::make_pair(position.first, position.second + 1);
    }

    return character;
}

char Source::get_character() const
{
    return character;
}

std::pair<int, int> Source::get_position()
{
    return position;
}

Source::Source()
{
    character = '\0';
}
