#include "Lexer.h"
#include <cctype>
#include <algorithm>
#include <cmath>
#include <cstring>

#define STR_LENGTH 20

Lexer::Lexer(const std::string& code)
{
    source = Source(code);
    next_token();
}

Token Lexer::next_token()
{
    while(isspace(source.get_character()))
        source.next_character();

    position = source.get_position();
    if(source.get_character() == '\0')
    {
        token = Token(addons::TokenType::END_OF_FILE, position);
        return token;
    }

    if(build_keyword())
        return token;

    if(build_number())
        return token;

    if(build_string())
        return token;

    if(build_char_token())
        return token;

    extend_undefined();
    return token;

}

bool Lexer::build_keyword()
{
    if(islower(source.get_character()))
    {
        std::stringstream name;
        name << source.get_character();
        while(islower(source.next_character()))
            name << source.get_character();

        std::string keyword = name.str();
        auto it = addons::keywordMap.find(keyword.c_str());
        if((source.get_character() == ':' || source.get_character() == '(' || isspace(source.get_character())) &&
            it != addons::keywordMap.end())
        {
            token = Token(it->second, position);
            return true;
        }
        else
            return extend_undefined();
    }
    else
        return false;
}

bool Lexer::build_number()
{
    bool negative = false;
    if(source.get_character() == '-')
    {
        negative = true;
        source.next_character();
    }

    Token number = build_float();
    if(number.get_type() == addons::TokenType::END_OF_FILE)
    {
        if(negative)
        {
            return extend_undefined();
        }
        else
            return false;
    }
    else
    {
        if(number.get_type() == addons::TokenType::UNDEFINED)
            return extend_undefined();
        else
        {
            if(source.get_character() == '\0' || isspace(source.get_character()) ||
                    std::find(addons::start_operators.begin(), addons::start_operators.end(),
                              source.get_character()) != addons::start_operators.end())
            {
                if(negative)
                {
                    if(number.get_type() == addons::TokenType::FLOAT_LITERAL)
                        token = Token(number.get_type(), number.get_position(), -number.get_value_float());
                    else
                        token = Token(number.get_type(), number.get_position(), -number.get_value_integer());
                }
                else
                    token = number;
            }
            else
                extend_undefined();
        }

        return true;
    }

}

Token Lexer::build_float()
{
    auto number = (float)build_integer();
    bool is_exp = false;
    bool dot = false;
    bool after_dot = false;
    float number2 = 0.0f;
    if(source.get_character() == '.')
    {
        dot = true;
        float divide = 10.0f;
        while(isdigit(source.next_character()))
        {
            after_dot = true;
            number2 += (float)(source.get_character() - '0') / divide;
            divide *= 10.0f;
        }

        if(after_dot)
        {
            if(number == -1.0f)
                number = 0.0f;

            number += number2;
        }
    }

    if(source.get_character() == 'e')
    {
        is_exp = true;
        if(!after_dot && number == -1.0f)
        {
            source.next_character();
            return {addons::TokenType::UNDEFINED, position};   // .e
        }

        bool minus = false;
        if(source.next_character() == '+')
            source.next_character();
        else if(source.get_character() == '-')
        {
            minus = true;
            source.next_character();
        }

        int value = build_integer();
        if(value != -1)
        {
            if(minus)
                number /= std::pow(10.0f, (float)value);
            else
                number *= std::pow(10.0f, (float)value);
        }
        else
            return {addons::TokenType::UNDEFINED, position};   // {number}e[+/-]{not-a-number}
    }

    if(is_exp)
        return {addons::TokenType::FLOAT_LITERAL, position, number};  // [point] float with exponent
    else
    {
        if(after_dot)
            return {addons::TokenType::FLOAT_LITERAL, position, number};  // point float ([int].{number})
        else if(!dot)
        {
            if(number != -1.0f)
                return {addons::TokenType::INT_LITERAL, position, (int)number}; // integer
            else
                return {addons::TokenType::END_OF_FILE, position};  // no match
        }
        else
        {
            if(number != -1.0f)
                return {addons::TokenType::FLOAT_LITERAL, position, number};   // point float (int.)
            else
                return {addons::TokenType::UNDEFINED, position};   // .
        }
    }
}

int Lexer::build_integer()
{
    if(source.get_character() == '0')
    {
        source.next_character();
        return 0;
    }
    else if(isdigit(source.get_character()))
    {
        int value = source.get_character() - '0';
        while(isdigit(source.next_character()))
        {
            value *= 10;
            value += source.get_character() - '0';
        }

        return value;
    }
    else
        return -1;
}

bool Lexer::build_string()
{
    if(source.get_character() == '"')
    {
        std::stringstream content;
        source.next_character();
        while(source.get_character() != '\n' && source.get_character() != '\0')
        {
            if(source.get_character() == '"')
            {
                source.next_character();
                if(isspace(source.get_character()) || source.get_character() == '\0' ||
                            std::find(addons::start_operators.begin(), addons::start_operators.end(),
                                      source.get_character()) != addons::start_operators.end())
                {
                    if(strlen(content.str().c_str()) < STR_LENGTH)
                        token = Token(addons::TokenType::STR_LITERAL, position, content.str().c_str());
                    else
                        extend_undefined();
                }
                else
                    extend_undefined();

                return true;
            }
            else if(source.get_character() == '\\')
            {
                source.next_character();
                if(source.get_character() == '\\')
                    content << '\\';
                else if(source.get_character() == 't')
                    content << '\t';
                else if(source.get_character() == 'n')
                    content << '\n';
                else if(source.get_character() == '"')
                    content << '"';
                else if(source.get_character() == '\n')
                    break;
                else
                    content << '\\' << source.get_character();

                source.next_character();
            }
            else
            {
                content << source.get_character();
                source.next_character();
            }
        }

        token = Token(addons::TokenType::UNDEFINED, position);
        source.next_character();
        return true;
    }
    else
        return false;
}

bool Lexer::build_char_token()
{
    if(source.get_character() == '*')
    {
        token = Token(addons::TokenType::STAR, position);
        source.next_character();
        return true;
    }
    else if(source.get_character() == ':')
    {
        token = Token(addons::TokenType::COLON, position);
        source.next_character();
        return true;
    }
    else if(source.get_character() == '(')
    {
        token = Token(addons::TokenType::OPEN_PARENTHESIS, position);
        source.next_character();
        return true;
    }
    else if(source.get_character() == ')')
    {
        token = Token(addons::TokenType::CLOSE_PARENTHESIS, position);
        source.next_character();
        return true;
    }
    else if(source.get_character() == ',')
    {
        token = Token(addons::TokenType::COMMA, position);
        source.next_character();
        return true;
    }
    else if(source.get_character() == '<')
    {
        if(source.next_character() == '=')
        {
            token = Token(addons::TokenType::LESS_EQUAL, position);
            source.next_character();
            return true;
        }
        else
        {
            token = Token(addons::TokenType::LESS, position);
            return true;
        }
    }
    else if(source.get_character() == '>')
    {
        if(source.next_character() == '=')
        {
            token = Token(addons::TokenType::MORE_EQUAL, position);
            source.next_character();
            return true;
        }
        else
        {
            token = Token(addons::TokenType::MORE, position);
            return true;
        }
    }
    else
        return false;
}

bool Lexer::extend_undefined()
{
    while(!isspace(source.get_character()) && source.get_character() != '\0')
        source.next_character();

    token = Token(addons::TokenType::UNDEFINED, position);
    return true;
}

Token Lexer::get_token()
{
    return token;
}

Lexer::Lexer()
{
    source = Source();
}
