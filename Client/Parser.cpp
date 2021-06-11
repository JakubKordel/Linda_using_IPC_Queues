#include "Parser.h"
#include <stdexcept>
#include <cstring>

Parser::Parser(const std::string& code)
{
    lexer = Lexer(code);
}

Msg Parser::parse()
{
    Msg msg{};
    if(lexer.get_token().get_type() == addons::TokenType::OUTPUT)
    {
        msg.option = 2;
        msg.req = parse_tuple();
    }
    else if(lexer.get_token().get_type() == addons::TokenType::INPUT)
    {
        msg.option = 1;
        msg.req = parse_pattern();
    }
    else if(lexer.get_token().get_type() == addons::TokenType::READ)
    {
        msg.option = 0;
        msg.req = parse_pattern();
    }
    else
        throw_parsing_error("incorrect operation", lexer.get_token().get_position());

    if(lexer.next_token().get_type() != addons::TokenType::END_OF_FILE)
        throw_parsing_error("expected EOF", lexer.get_token().get_position());

    return msg;
}

Request Parser::parse_tuple()
{
    Request request{};
    request.tuple.tel_amount = 0;
    if(lexer.next_token().get_type() == addons::TokenType::OPEN_PARENTHESIS)
    {
        for(auto & i : request.tuple.tel)
        {
            TupleElement tupleElement{};
            if(lexer.next_token().get_type() == addons::TokenType::STR_LITERAL)
            {
                strcpy(tupleElement.value.s, lexer.get_token().get_value_string());
                tupleElement.type = 1;
                i = tupleElement;
                request.tuple.tel_amount += 1;
            }
            else if(lexer.get_token().get_type() == addons::TokenType::INT_LITERAL)
            {
                tupleElement.value.i = lexer.get_token().get_value_integer();
                tupleElement.type = 0;
                i = tupleElement;
                request.tuple.tel_amount += 1;
            }
            else if(lexer.get_token().get_type() == addons::TokenType::FLOAT_LITERAL)
            {
                tupleElement.value.f = lexer.get_token().get_value_float();
                tupleElement.type = 2;
                i = tupleElement;
                request.tuple.tel_amount += 1;
            }
            else
                throw_parsing_error("expected literal", lexer.get_token().get_position());

            if(lexer.next_token().get_type() != addons::TokenType::COMMA)
                break;
        }

        if(lexer.get_token().get_type() != addons::TokenType::CLOSE_PARENTHESIS)
            throw_parsing_error("expected )", lexer.get_token().get_position());
    }
    else
        throw_parsing_error("expected (", lexer.get_token().get_position());

    return request;
}

Request Parser::parse_pattern()
{
    Request request{};
    request.pattern.pel_amount = 0;
    if(lexer.next_token().get_type() == addons::TokenType::OPEN_PARENTHESIS)
    {
        for(auto & i : request.pattern.pel)
        {
            PatternElement patternElement{};
            patternElement.condition = 0;
            if(lexer.next_token().get_type() == addons::TokenType::STRING)
                patternElement.type = 1;
            else if(lexer.get_token().get_type() == addons::TokenType::INTEGER)
                patternElement.type = 0;
            else if(lexer.get_token().get_type() == addons::TokenType::FLOAT)
                patternElement.type = 2;
            else
                throw_parsing_error("expected type name", lexer.get_token().get_position());

            if(lexer.next_token().get_type() != addons::TokenType::COLON)
                throw_parsing_error("expected :", lexer.get_token().get_position());

            if(lexer.next_token().get_type() == addons::TokenType::LESS)
            {
                patternElement.condition = 1;
                lexer.next_token();
            }
            else if(lexer.get_token().get_type() == addons::TokenType::LESS_EQUAL)
            {
                patternElement.condition = 2;
                lexer.next_token();
            }
            else if(lexer.get_token().get_type() == addons::TokenType::MORE)
            {
                patternElement.condition = 3;
                lexer.next_token();
            }
            else if(lexer.get_token().get_type() == addons::TokenType::MORE_EQUAL)
            {
                patternElement.condition = 4;
                lexer.next_token();
            }

            if(lexer.get_token().get_type() == addons::TokenType::STAR)
            {
                patternElement.condition = 5;
                i = patternElement;
                request.pattern.pel_amount += 1;
            }
            else if(lexer.get_token().get_type() == addons::TokenType::STR_LITERAL)
            {
                if(patternElement.type != 1)
                    throw_parsing_error("not expected string literal", lexer.get_token().get_position());

                strcpy(patternElement.value.s, lexer.get_token().get_value_string());
                i = patternElement;
                request.pattern.pel_amount += 1;
            }
            else if(lexer.get_token().get_type() == addons::TokenType::INT_LITERAL)
            {
                if(patternElement.type != 0)
                    throw_parsing_error("not expected int literal", lexer.get_token().get_position());

                patternElement.value.i = lexer.get_token().get_value_integer();
                i = patternElement;
                request.pattern.pel_amount += 1;
            }
            else if(lexer.get_token().get_type() == addons::TokenType::FLOAT_LITERAL)
            {
                if(patternElement.type != 2)
                    throw_parsing_error("not expected float literal", lexer.get_token().get_position());

                if(patternElement.condition == 0)
                    throw_parsing_error("== condition is not available for float type",
                                        lexer.get_token().get_position());

                patternElement.value.f = lexer.get_token().get_value_float();
                i = patternElement;
                request.pattern.pel_amount += 1;
            }
            else
                throw_parsing_error("expected condition and/or value", lexer.get_token().get_position());

            if(lexer.next_token().get_type() != addons::TokenType::COMMA)
                break;
        }

        if(lexer.get_token().get_type() != addons::TokenType::CLOSE_PARENTHESIS)
            throw_parsing_error("expected )", lexer.get_token().get_position());
    }
    else
        throw_parsing_error("expected (", lexer.get_token().get_position());

    return request;
}

void Parser::throw_parsing_error(const std::string& msg, std::pair<int, int> pos)
{
    std::string message = "Parsing error - " + msg + " [line=" + std::to_string(pos.first) +
                            ", col=" + std::to_string(pos.second) + "]";
    throw std::runtime_error(message.c_str());
}
