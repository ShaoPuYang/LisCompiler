/* 
 * @Copyrigt 2023, liserver. All rights reserved.
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../core/Compiler.h"
#include "library/console/prints.h"

enum TokenCode
{
    // About Token
    TK_NOT_DEFINED = 0, // Not defined

    // Keywords
    TK_KEYWORD_IF,        // if
    TK_KEYWORD_ELSE,      // else
    TK_KEYWORD_WHILE,     // while
    TK_KEYWORD_FOR,       // for
    TK_KEYWORD_RETURN,    // return
    TK_KEYWORD_BREAK,     // break
    TK_KEYWORD_CONTINUE,  // continue
    TK_KEYWORD_INT,       // int
    TK_KEYWORD_FLOAT,     // float
    TK_KEYWORD_DOUBLE,    // double
    TK_KEYWORD_STRING,    // string
    TK_KEYWORD_FUNCTION,  // function
    TK_KEYWORD_SWITCH,    // switch
    TK_KEYWORD_CASE,      // case
    TK_KEYWORD_DEFAULT,   // default
    TK_KEYWORD_CLASS,     // class
    TK_KEYWORD_PUBLIC,    // public
    TK_KEYWORD_PRIVATE,   // private
    TK_KEYWORD_PROTECTED, // protected
    TK_KEYWORD_SIZEOF,    // sizeof
    TK_KEYWORD_NAMESPACE, // namespace 

    // Operators
    TK_OPERATOR_ADD,           // +
    TK_OPERATOR_SUB,           // -
    TK_OPERATOR_MUL,           // *
    TK_OPERATOR_DIV,           // /
    TK_OPERATOR_MOD,           // %
    TK_OPERATOR_ASSIGN,        // =
    TK_OPERATOR_ADD_ASSIGN,    // +=
    TK_OPERATOR_SUB_ASSIGN,    // -=
    TK_OPERATOR_MUL_ASSIGN,    // *=
    TK_OPERATOR_DIV_ASSIGN,    // /=
    TK_OPERATOR_MOD_ASSIGN,    // %=
    TK_OPERATOR_EQUAL,         // ==
    TK_OPERATOR_NOT_EQUAL,     // !=
    TK_OPERATOR_LESS,          // <
    TK_OPERATOR_LESS_EQUAL,    // <=
    TK_OPERATOR_GREATER,       // >
    TK_OPERATOR_GREATER_EQUAL, // >=
    TK_OPERATOR_ARROW,         // ->
    TK_OPERATOR_AND,           // &&
    TK_OPERATOR_OR,            // ||
    TK_OPERATOR_NOT,           // !

    // Delimiters
    TK_DELIMITER_LEFT_BRACE,        // {
    TK_DELIMITER_RIGHT_BRACE,       // }
    TK_DELIMITER_LEFT_BRACKET,      // [
    TK_DELIMITER_RIGHT_BRACKET,     // ]
    TK_DELIMITER_LEFT_PARENTHESIS,  // (
    TK_DELIMITER_RIGHT_PARENTHESIS, // )
    TK_DELIMITER_COMMA,             // ,
    TK_DELIMITER_SEMICOLON,         // ;
    TK_DELIMITER_DOT,               // .
    TK_DELIMITER_COLON,             // :
    TK_DELIMITER_ARROW,             // ->
    TK_DELIMITER_DOUBLE,            // "
    TK_DELIMITER_SINGLE,            // '
    TK_DELIMITER_FMON,              // $

    // Literals
    TK_LITERAL_INT,    // 123
    TK_LITERAL_FLOAT,  // 123.456
    TK_LITERAL_DOUBLE, // 123.456
    TK_LITERAL_STRING, // "Hello World"
    TK_LITERAL_BOOL,   // true false

    // Token IDENTIFIER
    TK_IDENTIFIER // identifier
};

class Token
{
public:
    TokenCode code = TokenCode::TK_NOT_DEFINED;
    std::string value = "";
    int line = 1;

    Token(TokenCode code = TokenCode::TK_NOT_DEFINED, std::string value = "", int line = 1)
    {
        this->code = code;
        this->value = value;
        this->line = line;
    }
};

// Is or not a keyword
bool IsKeyword(std::string str);

// Return the keyword's id (In TokenCode)
int KeywordCode(std::string str);

// Is or not a delimiter
bool IsChar(char c);

// Is or not a number
bool IsNumber(char c);

// First, read each character of the given string. If it is a space or newline character, store the current token and continue reading the next character

namespace TokenSpace
{

    // The vector is not easy to read, so I thought of the data stream in js, so there was TokenStream
    class TokenStream
    {
    public:
        int number = 0; // The current token number
        std::vector<Token> tokens;
        inline int Size()
        {
            return tokens.size();
        }

        TokenStream(){};

        TokenStream(std::vector<Token> tokens)
        {
            this->tokens = tokens;
        }

        void Next()
        {
            if (number < Size())
            {
                this->number += 1;
            }
            else
            {
                this->number = 0;
            }
        }

        void Up()
        {
            if (number > 0)
                this->number -= 1;
            else
                this->number = Size()-1;
            
        }

        inline Token GetCurToken()
        {
            return this->tokens[this->number];
        }

        inline std::vector<Token> GetVector()
        {
            return this->tokens;
        }

        inline Token GetNextToken()
        {
            return this->tokens[this->number + 1];
        }

        void match(std::string str)
        {
            if (this->GetCurToken().value != str)
                Message::Error("Unknow token [" + str + "].", CP_ERR, CP_UNKNOW_TOKEN, true);
            this->Next();
        }

        void match(TokenCode tk)
        {
            if (this->GetCurToken().code != tk)
                Message::Error("Unknow token [" + this->GetCurToken().value + "].", CP_ERR, CP_UNKNOW_TOKEN, true);
            this->Next();
        }
    };

    TokenStream ReadString(std::string str);
} // namespace TokenSpace
