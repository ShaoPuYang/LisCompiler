/*
 * @Copyrigt 2023, liserver. All rights reserved.
 */

#include "../core/Compiler.h"
#include "../Token/TokenStream.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

// TokenAnalysis

class AstNode {
public:
    virtual ~AstNode() = default;
};

class AstProgram : public AstNode {
public:
    std::vector<std::unique_ptr<AstNode>> declarations;
};

class AstDeclaration : public AstNode {
public:
    // ...
};

class AstIncludeDeclaration : public AstDeclaration {
public:
    // ...
};

class AstImportDeclaration : public AstDeclaration {
public:
    // ...
};

class AstVariableDeclaration : public AstDeclaration {
public:
    // ...
};

class AstFunctionDeclaration : public AstDeclaration {
public:
    // ...
};

class AstClassDeclaration : public AstDeclaration {
public:
    // ...
};

class AstNamespaceDeclaration : public AstDeclaration {
public:
    // ...
};

class AstExpression : public AstNode {
public:
    // ...
};

class AstPrimary : public AstExpression {
public:
    // ...
};

class AstUnaryExpression : public AstExpression {
public:
    // ...
};

class AstBinaryExpression : public AstExpression {
public:
    // ...
};

class AstFunctionCall : public AstExpression {
public:
    // ...
};

class AstParameter : public AstNode {
public:
    // ...
};

class AstStatement : public AstNode {
public:
    // ...
};

class AstReturnStatement : public AstStatement {
public:
    // ...
};

class AstCompoundStatement : public AstStatement {
public:
    // ...
};

class AstClassMember : public AstNode {
public:
    // ...
};

class Parser
{
private:
    TokenSpace::TokenStream Tokenstream;

public:
    bool is_binary_operator(const Token &token);

    void parse();
    void parse_default_value();
    void parse_import();
    void parse_namespace_members();
    void parse_namespace();
    void parse_class();
    void parse_class_member();
    void parse_class_members();
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

    Parser(TokenSpace::TokenStream ts)
    {
        this->Tokenstream = ts;
    }
};