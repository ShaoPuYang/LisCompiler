/* 
 * @Copyrigt 2023, liserver. All rights reserved.
 */

#include "TokenStream.h"

const char Keyword[][21] = {
    "if",
    "else",
    "while",
    "for",
    "return",
    "break",
    "continue",
    "int",
    "float",
    "double",
    "string",
    "function",
    "switch",
    "case",
    "default",
    "class",
    "public",
    "private",
    "protected",
    "Sizeof"};

bool IsKeyword(std::string str)
{
    for (int i = 0; i < (int) sizeof(Keyword) / (int) sizeof(Keyword[0]); i++)
    {
        if (str == Keyword[i])
            return true;
    }
    return false;
}

int KeywordCode(std::string str)
{
    for (int i = 0; i < (int) sizeof(Keyword) / (int) sizeof(Keyword[0]); i++)
    {
        if (str == Keyword[i])
            return i + 1;
    }
    return -1;
}

bool IsChar(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool IsNumber(char c)
{
    return c >= '0' && c <= '9';
}

TokenSpace::TokenStream TokenSpace::ReadString(std::string str)
{
    std::vector<Token> tokens;
    Token token; // Now currrl token
    int i = 0;   // 
    bool Is_UnCode = false;
    while (i < (int) str.length())
    {
        // std::cout << (int) str[i] << std::endl;
        if ((int) str[i] == 13) // ASCII CR 13
            str[i] = ' ';
        if (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
        {
            if (str[i] == '\n')
                token.line++;
            i++;
            continue;
        }
        // Identifier
        else if (IsChar((char)str[i]))
        {
            while (IsChar((char)str[i]) && !IsNumber((char)str[i]))
            {
                token.value += str[i];
                i++;
            }
            if (IsKeyword(token.value) && !IsNumber(str[i]))
            {
                token.code = TokenCode(KeywordCode(token.value));
            }
            else
            {
                if (IsNumber(str[i]))
                {
                    token.value += str[i];
                    i++;
                }
                token.code = TokenCode::TK_IDENTIFIER;
            }
        }
        // Number
        else if (IsNumber((char)str[i]))
        {
            while (IsNumber((char)str[i]))
            {
                token.value += str[i];
                i++;
            }
            if (str[i] == '.')
            {
                token.value += str[i];
                i++;
                while (IsNumber((char)str[i]))
                {
                    token.value += str[i];
                    i++;
                }
                token.code = TokenCode::TK_LITERAL_DOUBLE;
            }
            else
            {
                token.code = TokenCode::TK_LITERAL_INT;
            }
        }
        // Operator
        else
            switch (str[i])
            {
            case '$':
                while (str[i] != '\n')
                {
                    i++;
                }
                i++; // The next line
                break;
            case '+':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_ADD_ASSIGN;
                    token.value = "+=";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_ADD;
                    token.value = "+";
                    i++;
                }
                break;
            case '-':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_SUB_ASSIGN;
                    token.value = "-=";
                    i += 2;
                }
                else if (str[i + 1] == '>')
                {
                    token.code = TokenCode::TK_OPERATOR_ARROW;
                    token.value = "->";
                    i += 2;
                }
                else if (str[i + 1] == '>')
                {
                    token.code = TokenCode::TK_DELIMITER_ARROW;
                    token.value = "->";
                    i += 2;
                }
                else if (str[i + 1] == '>')
                {
                    token.code = TokenCode::TK_OPERATOR_ARROW;
                    token.value = "->";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_SUB;
                    token.value = "-";
                    i++;
                }
                break;
            case '*':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_MUL_ASSIGN;
                    token.value = "*=";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_MUL;
                    token.value = "*";
                    i++;
                }
                break;
            case '/':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_DIV_ASSIGN;
                    token.value = "/=";
                    i += 2;
                }
                else if (str[i + 1] == '/')
                {
                    i += 2;
                    // Comment
                    while (str[i] != '\n')
                        i++;
                    i++;
                    Is_UnCode = true;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_DIV;
                    token.value = "/";
                    i++;
                }
                break;
            case '%':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_MOD_ASSIGN;
                    token.value = "%=";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_MOD;
                    token.value = "%";
                    i++;
                }
                break;
            case '=':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_EQUAL;
                    token.value = "==";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_ASSIGN;
                    token.value = "=";
                    i++;
                }
                break;
            case '!':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_NOT_EQUAL;
                    token.value = "!=";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_NOT;
                    token.value = "!";
                    i++;
                }
                break;
            case '>':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_GREATER_EQUAL;
                    token.value = ">=";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_GREATER;
                    token.value = ">";
                    i++;
                }
                break;
            case '<':
                if (str[i + 1] == '=')
                {
                    token.code = TokenCode::TK_OPERATOR_LESS_EQUAL;
                    token.value = "<=";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_OPERATOR_LESS;
                    token.value = "<";
                    i++;
                }
                break;
            case '&':
                if (str[i + 1] == '&')
                {
                    token.code = TokenCode::TK_OPERATOR_AND;
                    token.value = "&&";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_NOT_DEFINED;
                    token.value = "&";
                    i++;
                }
                break;
            case '|':
                if (str[i + 1] == '|')
                {
                    token.code = TokenCode::TK_OPERATOR_OR;
                    token.value = "||";
                    i += 2;
                }
                else
                {
                    token.code = TokenCode::TK_NOT_DEFINED;
                    token.value = "|";
                    i++;
                }
                break;
            // Delimiter
            case '(':
                token.code = TokenCode::TK_DELIMITER_LEFT_PARENTHESIS;
                token.value = "(";
                i++;
                break;
            case ')':
                token.code = TokenCode::TK_DELIMITER_RIGHT_PARENTHESIS;
                token.value = ")";
                i++;
                break;
            case '{':
                token.code = TokenCode::TK_DELIMITER_LEFT_BRACE;
                token.value = "{";
                i++;
                break;
            case '}':
                token.code = TokenCode::TK_DELIMITER_RIGHT_BRACE;
                token.value = "}";
                i++;
                break;
            case '[':
                token.code = TokenCode::TK_DELIMITER_LEFT_BRACKET;
                token.value = "[";
                i++;
                break;
            case ']':
                token.code = TokenCode::TK_DELIMITER_RIGHT_BRACKET;
                token.value = "]";
                i++;
                break;
            case ',':
                token.code = TokenCode::TK_DELIMITER_COMMA;
                token.value = ",";
                i++;
                break;
            case ';':
                token.code = TokenCode::TK_DELIMITER_SEMICOLON;
                token.value = ";";
                i++;
                break;
            case '.':
                token.code = TokenCode::TK_DELIMITER_DOT;
                token.value = ".";
                i++;
                break;
            case ':':
                token.code = TokenCode::TK_DELIMITER_COLON;
                token.value = ":";
                i++;
                break;
            case '"':
            {
                token.code = TokenCode::TK_OPERATOR_DOUBLE;
                token.value = '"';
                i++;
                break;
            }
            case '\'':
            {
                token.code = TokenCode::TK_OPERATOR_SINGLE;
                token.value = "'";
                i++;
                break;
            }
            default:
                token.code = TokenCode::TK_NOT_DEFINED;
                token.value = str[i];
                i++;
                break;
            }
        if (Is_UnCode || token.value == "\n")
        {
            token.line++; 
            token.value = "";
            token.code = TK_NOT_DEFINED;
            Is_UnCode = false;
            continue;
        }
        tokens.push_back(token);
        token.value = "";
        token.code = TK_NOT_DEFINED;
    }

    // Save and return
    return TokenSpace::TokenStream(tokens);
}
