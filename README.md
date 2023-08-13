# LisCompiler

A easy language compiler. (not be ready)


for AST :

This is a table of ast class.
| Ast类                   | 实现内容                                                       | Parser操作                                                           | 作用                                           |
| ----------------------- | -------------------------------------------------------------- | -------------------------------------------------------------------- | ---------------------------------------------- |
| AstNode                 | 基本的虚析构函数                                               | 无                                                                   | 作为所有Ast类的基类                            |
| AstProgram              | 包含一个AstNode类型的声明向量                                  | 在`parse()`函数中创建并返回AstProgram节点                            | 代表整个程序的根节点                           |
| AstDeclaration          | 无                                                             | 无                                                                   | 作为所有声明类的基类                           |
| AstIncludeDeclaration   | 包含一个字符串表示包含的文件名                                 | 在`parse_include()`函数中创建并返回AstIncludeDeclaration节点         | 代表一个包含声明                               |
| AstImportDeclaration    | 包含一个字符串表示导入的标识符                                 | 在`parse_import()`函数中创建并返回AstImportDeclaration节点           | 代表一个导入声明                               |
| AstVariableDeclaration  | 包含类型、标识符和可选的初始值操作数                           | 在`parse_variable()`函数中创建并返回AstVariableDeclaration节点       | 代表一个变量声明                               |
| AstFunctionDeclaration  | 包含返回类型、函数名、参数列表和函数体（AstCompoundStatement） | 在`parse_function()`函数中创建并返回AstFunctionDeclaration节点       | 代表一个函数声明                               |
| AstClassDeclaration     | 包含类名、可选的父类名和类成员列表                             | 在`parse_class()`函数中创建并返回AstClassDeclaration节点             | 代表一个类声明                                 |
| AstNamespaceDeclaration | 包含命名空间名和命名空间成员列表                               | 在`parse_namespace()`函数中创建并返回AstNamespaceDeclaration节点     | 代表一个命名空间声明                           |
| AstExpression           | 无                                                             | 无                                                                   | 作为所有表达式类的基类                         |
| AstPrimary              | 包含一个variant表示字面值、标识符或函数调用                    | 在`parse_primary()`函数中创建并返回AstPrimary节点                    | 代表一个基本表达式（字面值、标识符或函数调用） |
| AstUnaryExpression      | 包含一元操作符和操作数                                         | 在`parse_unary_expression()`函数中创建并返回AstUnaryExpression节点   | 代表一个一元表达式                             |
| AstBinaryExpression     | 包含二元操作符和两个操作数                                     | 在`parse_binary_expression()`函数中创建并返回AstBinaryExpression节点 | 代表一个二元表达式                             |
| AstFunctionCall         | 包含函数名和参数列表                                           | 在`parse_function_call()`函数中创建并返回AstFunctionCall节点         | 代表一个函数调用表达式                         |
| AstParameter            | 包含类型、标识符和可选的默认值                                 | 在`parse_parameter()`函数中创建并返回AstParameter节点                | 代表一个函数参数                               |
| AstStatement            | 无                                                             | 无                                                                   | 作为所有语句类的基类                           |
| AstReturnStatement      | 包含一个可选的返回值操作数                                     | 在`parse_return()`函数中创建并返回AstReturnStatement节点             | 代表一个返回语句                               |
| AstCompoundStatement    | 包含一个语句列表                                               | 在`parse_compound()`函数中创建并返回AstCompoundStatement节点         | 代表一个复合语句（由一组语句组成）             |
| AstClassMember          | 无                                                             | 无                                                                   | 作为类成员（变量声明和函数声明）的基类         |