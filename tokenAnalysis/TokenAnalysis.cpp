/*
 * @Copyrigt 2023, liserver. All rights reserved.
 */

#include "TokenAnalysis.h"

bool IsT(std::string str)
{
    return (str == "string" || str == "int" || str == "float" || str == "double");
}

void Parser::parse_function_call()
{
    this->Tokenstream.match(TokenCode::TK_IDENTIFIER);
    this->Tokenstream.match("(");
    this->parse_compound();
    this->Tokenstream.match("(");
}

void Parser::parse_parameter()
{
    if (IsT(this->Tokenstream.GetCurToken().value) || this->Tokenstream.GetCurToken().code == TK_IDENTIFIER)
    {
        this->Tokenstream.match(TokenCode::TK_IDENTIFIER);
        if (this->Tokenstream.GetNextToken().value == "=")
        {
            this->Tokenstream.match("=");
            this->Tokenstream.Next();
        }
    }
}

void Parser::parse_parameters()
{
    while (this->Tokenstream.GetCurToken().value != ")")
    {
        if (this->Tokenstream.number + 1 == this->Tokenstream.Size())
            Message::Error("Can't find the ; or )", CP_ERR, CP_NOTFIND_TOKEN, true);
        this->parse_parameter();
        if (this->Tokenstream.GetNextToken().value == ",")
        {
            this->Tokenstream.match(",");
        }
        else
        {
            this->Tokenstream.match(")");
            return;
        }
    }
    this->Tokenstream.match(")");
}

void Parser::parse_compound()
{
    this->Tokenstream.match("{");
    this->parse_statement();
    this->Tokenstream.match("}");

    if (this->Tokenstream.GetNextToken().value == ";")
    {
        this->Tokenstream.match(";");
    }
}

bool Parser::parse_binary_operators()
{
    if (this->Tokenstream.GetCurToken().value.size() == 1)
    {
        switch (this->Tokenstream.GetCurToken().value[0])
        {
        case '+':
            this->Tokenstream.match("+");
            break;
        case '-':
            this->Tokenstream.match("-");
            break;
        case '*':
            this->Tokenstream.match("*");
            break;
        case '/':
            this->Tokenstream.match("/");
            break;
        case '<':
            this->Tokenstream.match("<");
            break;
        case '>':
            this->Tokenstream.match(">");
            break;
        default:
            return false;
        }
    }
    else if (this->Tokenstream.GetCurToken().value.size() == 2)
    {
        if (this->Tokenstream.GetCurToken().value == "==")
            this->Tokenstream.match("==");
        else if (this->Tokenstream.GetCurToken().value == "!=")
            this->Tokenstream.match("!=");
        else if (this->Tokenstream.GetCurToken().value == "&&")
            this->Tokenstream.match("&&");
        else if (this->Tokenstream.GetCurToken().value == "||")
            this->Tokenstream.match("||");
        else
            return false;
    }
    else
    {
        return false;
    }
    return true;
}

void Parser::parse_unary_operators()
{
    this->Tokenstream.match("!");
}

void Parser::parse_operand()
{
    if (parse_primary())
        return;
    if (parse_unary_expression())
        return;
    parse_binary_expression();
}

bool Parser::parse_primary()
{
    Token NToken = this->Tokenstream.GetCurToken();
    if (NToken.code == TK_LITERAL_STRING)
        this->Tokenstream.match(TK_LITERAL_STRING);
    else if (NToken.code == TK_LITERAL_FLOAT)
        this->Tokenstream.match(TK_LITERAL_FLOAT);
    else if (NToken.code == TK_LITERAL_INT)
        this->Tokenstream.match(TK_LITERAL_INT);
    else if (NToken.code == TK_IDENTIFIER)
        this->parse_function_call();
    else
        return false;
    return true;
}

bool Parser::parse_unary_expression()
{
    Token NToken = this->Tokenstream.GetCurToken();
    if (NToken.value == "!")
    {
        this->Tokenstream.match("!");
        parse_operand();
        return true;
    }
    return false;
}

void Parser::parse_binary_expression()
{
    parse_operand();
    parse_binary_operators();
    parse_operand();
}

void Parser::parse_return()
{
    this->Tokenstream.match(TK_KEYWORD_RETURN);
    if (this->Tokenstream.GetCurToken().value != ";")
        this->parse_operand();
    this->Tokenstream.match(";");
}

void Parser::parse_statement()
{
    if (IsT(this->Tokenstream.GetCurToken().value) || this->Tokenstream.GetCurToken().code == TK_IDENTIFIER)
    {
        this->Tokenstream.match(TokenCode::TK_IDENTIFIER);
        if (this->Tokenstream.GetNextToken().value == "=" || this->Tokenstream.GetNextToken().value == ";")
            this->parse_variable();
        else
            Message::Error("Unknow token [" + this->Tokenstream.GetNextToken().value + "]", CP_ERR, CP_UNKNOW_TOKEN, true);
    }
    else if (this->Tokenstream.GetCurToken().code == TK_KEYWORD_RETURN)
    {
        this->parse_return();
    }
}

void Parser::parse_function()
{
    this->Tokenstream.match("(");
    if (this->Tokenstream.GetNextToken().value != ")")
        this->parse_parameters();
    if (this->Tokenstream.GetCurToken().value == ";")
        this->Tokenstream.match(";");
    else
        this->parse_compound();
}

void Parser::parse_variable()
{
    if (this->Tokenstream.GetCurToken().value == "=")
    {
        this->Tokenstream.match("=");
        this->parse_operand();
    }
    this->Tokenstream.match(";");
}

void Parser::parse()
{
    if (IsT(this->Tokenstream.GetCurToken().value) || this->Tokenstream.GetCurToken().code == TK_IDENTIFIER)
    {
        Tokenstream.Next();
        this->Tokenstream.match(TK_IDENTIFIER);
        if (this->Tokenstream.GetCurToken().value == "(")
            this->parse_function();
        else
            this->parse_variable();
    }
}