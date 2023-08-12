/* 
 * @Copyrigt 2023, liserver. All rights reserved.
 */

#include "../core/Compiler.h"
#include "../Token/TokenStream.h"

#include <iostream>
#include <string>
#include <vector>

// TokenAnalysis

class AST
{

};

class Parser
{
private:
    TokenSpace::TokenStream Tokenstream;
public:
    void parse();
    void parse_variable();
    void parse_function();
    void parse_parameters();
    void parse_parameter();
    void parse_compound();
    void parse_statement();
    void parse_function_call();
    void parse_return();
    void parse_operand();
    bool parse_primary();
    bool parse_unary_expression();
    void parse_binary_expression();
    bool parse_binary_operators();
    void parse_unary_operators();

    AST BuildAST(); 

    Parser(TokenSpace::TokenStream ts)
    {
        this->Tokenstream = ts;
    }
};