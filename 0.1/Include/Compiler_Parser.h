#ifndef PRETTY_PARSER
#define PRETTY_PARSER

#include <iostream> 
#include <string> 
#include <vector>
#include <memory>
#include <stdexcept>
#include "Token_Maker.h"


enum class NodeType {

add,
minus,
multiply,
divide,
unary,

number, 
identifier,

less,
greater,
greq,
leq,
is,
Not,

if_stmt,
var_assign,
print_stmt,
block,

condition 


};

struct Node {
std::string string_token;
std::vector<std::unique_ptr<Node>> block;
NodeType type;
std::unique_ptr<Node> left = nullptr;
std::unique_ptr<Node> right = nullptr;

};



class parser {
private:
std::vector<token> tokens;
size_t current = 0;


public:
    explicit parser(std::vector<token> input_tokens)
        : tokens(input_tokens){}

    const token& peek();
    const token& consume(TokenType expected);
    std::unique_ptr<Node> parse_number();
    std::unique_ptr<Node> parse_expression();
    std::unique_ptr<Node> parse_term();
    std::unique_ptr<Node> parse_factor();
    std::unique_ptr<Node> parse_primary();
    std::unique_ptr<Node> parse_identifier();
    std::unique_ptr<Node> parse_assignment();
    std::unique_ptr<Node> parse_condition();
    std::unique_ptr<Node> parse_write();
    std::unique_ptr<Node> parse_if();
    std::unique_ptr<Node> parse_statement();
    std::vector<std::unique_ptr<Node>> parse_program();
};
    void print_ast(const std::unique_ptr<Node>& node, int depth = 0);
    std::string node_type_name(NodeType type);

#endif
