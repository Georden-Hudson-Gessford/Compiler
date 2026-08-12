#include <iostream> 
#include <string> 
#include <vector>
#include <memory>
#include <stdexcept>
#include "Token_Maker.h"
#include "Compiler_Parser.h"



const token& parser::peek() { 

if (current >= tokens.size()) {
            throw std::runtime_error("Read past token list");
        }

        return tokens[current];

};

const token& parser::consume(TokenType expected) {

if ( peek().type != expected) {
    throw std::runtime_error("invalid token");
}

else
return tokens[current++];

};



    std::unique_ptr<Node> parser::parse_number() {
        const token& tok = consume(TokenType::number);

        auto node = std::make_unique<Node>();
        node->type = NodeType::number;
        node->string_token = tok.lexeme;
        return node;

    }

    std::unique_ptr<Node> parser::parse_expression() {
       auto left = parse_term();

       while (peek().type == TokenType::plus || peek().type == TokenType::minus) {

        auto op = peek();
        auto node = std::make_unique<Node>();

        if ( op.type == TokenType::plus) {
            node->string_token = consume(TokenType::plus).lexeme;
            node->type = NodeType::add; }
        else if (op.type == TokenType::minus) {
            node->string_token = consume(TokenType::minus).lexeme;
            node->type = NodeType::minus; }

            auto right = parse_term();


        node->left =  std::move(left);
        node->right = std::move(right);
        left = std::move(node);

       }

       return left;
     
    }

    std::unique_ptr<Node> parser::parse_term() {
auto left = parse_factor();

       while (peek().type == TokenType::asterisk || peek().type == TokenType::slash) {

        auto op = peek();
        auto node = std::make_unique<Node>();

        if ( op.type == TokenType::asterisk) {
            node->string_token = consume(TokenType::asterisk).lexeme;
            node->type = NodeType::multiply; }
        else if (op.type == TokenType::slash) {
            node->string_token = consume(TokenType::slash).lexeme;
            node->type = NodeType::divide; }

            auto right = parse_factor();


        node->left =  std::move(left);
        node->right = std::move(right);
        left = std::move(node);

       }

       return left;
    }

    std::unique_ptr<Node> parser::parse_factor() {

token peekey = peek();



 if (peek().type == TokenType::minus) {
        consume(TokenType::minus);

        auto node = std::make_unique<Node>();
        node->type = NodeType::unary;
        node->string_token = "-";
        node->right = parse_factor();

        return node;
    }

    return parse_primary();
    }

    std::unique_ptr<Node> parser::parse_primary() { 
        
        token peekey = peek(); 

         if (peekey.type == TokenType::identifier)
            return parse_identifier();

         if (peekey.type == TokenType::number)
           return parse_number();

         if (peekey.type == TokenType::leftparentheses) {
            consume(TokenType::leftparentheses);

             auto result = parse_expression();
            consume(TokenType::rightparentheses);
            return result;
         
        }

    throw std::runtime_error("Expected primary expression");
}
    
std::unique_ptr<Node> parser::parse_identifier() {

        const token& token = consume(TokenType::identifier);
        auto node = std::make_unique<Node>();
        node->type = NodeType::identifier;
        node->string_token = token.lexeme;
        return node;

}




std::unique_ptr<Node> parser::parse_assignment() {
     
        auto node = std::make_unique<Node>();
        node->type = NodeType::var_assign;
        consume(TokenType::make);
       node->left =  parse_identifier();
        consume(TokenType::assignment);
        node->right = parse_expression();
        node->string_token = "make";
        consume(TokenType::semicolon);
        return node;

};


std::unique_ptr<Node> parser::parse_condition(){

auto node = std::make_unique<Node>();
auto left_side = parse_expression();
auto peekey = peek();

if (peekey.type == TokenType::greater) {
node->string_token = consume(TokenType::greater).lexeme;
node->type = NodeType::greater; }


else if (peekey.type == TokenType::greq)  {
node->string_token = consume(TokenType::greq).lexeme;
node->type = NodeType::greq;
}

else if ( peekey.type == TokenType::less) {
node->string_token = consume(TokenType::less).lexeme;
node->type = NodeType::less;
}

else if (peekey.type == TokenType::leq) {
node->string_token = consume(TokenType::leq).lexeme;
node->type = NodeType::leq;
}
else if (peekey.type == TokenType::is) {
node->string_token = consume(TokenType::is).lexeme;
node->type = NodeType::is;

}
else if (peekey.type == TokenType::Not) {
node->string_token = consume(TokenType::Not).lexeme;
node->type = NodeType::Not;

}
else
throw std::runtime_error ("missing comparison operatior");


auto right_side = parse_expression();

node->left = std::move(left_side);
node->right = std::move(right_side);



 return node;
};



std::unique_ptr<Node> parser::parse_write() {

auto node = std::make_unique<Node>();

 consume(TokenType::write);
 node->type = NodeType::print_stmt;
 node->string_token = "write";
 node->right = parse_expression();

 


consume(TokenType::semicolon);
        return node;
};

std::unique_ptr<Node> parser::parse_if(){ 

auto block_node = std::make_unique<Node>();

block_node->type = NodeType::block;
block_node->string_token = "block_stmt";
 

auto node = std::make_unique<Node>();

consume(TokenType::If);
consume(TokenType::period);

auto left = parse_condition();

consume(TokenType::period);
consume(TokenType::leftbracket);

    while (peek().type != TokenType::rightbracket) {


    if (peek().type == TokenType::end_token) {
        throw std::runtime_error("Expected ']' before end of file");
    }
      block_node->block.push_back(parse_statement());
        
    } 
auto right = std::move(block_node);

consume(TokenType::rightbracket);
node->type = NodeType::if_stmt;
node->string_token = "if";
node->left = std::move(left);
node->right = std::move(right);
    



        return node;
 }

std::unique_ptr<Node> parser::parse_statement() {
   

        if (peek().type == TokenType::make) 
            return parse_assignment();
        
        else if (peek().type == TokenType::If) 
            return parse_if();
        
        else if (peek().type == TokenType::write) 
            return parse_write();
        
        else 
            throw std::runtime_error("Expected statement");
        
    


};

std::vector<std::unique_ptr<Node>> parser::parse_program() {

    std::vector<std::unique_ptr<Node>> module;

    while (peek().type != TokenType::end_token) {

       module.push_back(parse_statement());
    }

    return module;
}

//Call for debugging and parser tests
void print_ast(const std::unique_ptr<Node>& node, int depth)
{
    if (!node)
        return;

    print_ast(node->right, depth + 1);

    for (int i = 0; i < depth; i++)
        std::cout << "    ";

    
    std::cout << "[" << node_type_name(node->type) << "]";

    std::cout << node->string_token << '\n';

    print_ast(node->left, depth + 1);

    for (const auto& statement : node->block)
        print_ast(statement, depth + 1);
}

std::string node_type_name(NodeType type) {
    switch (type) {
        case NodeType::add:        return "ADD ";
        case NodeType::minus:      return "SUBTRACT ";
        case NodeType::multiply:   return "MULTIPLY ";
        case NodeType::divide:     return "DIVIDE ";
        case NodeType::number:     return "NUMBER ";
        case NodeType::identifier: return "IDENTIFIER ";
        case NodeType::var_assign: return "ASSIGN ";
        case NodeType::print_stmt: return "WRITE ";
        case NodeType::if_stmt:    return "IF ";
        case NodeType::block:      return "BLOCK ";
        case NodeType::is:         return "IS ";
        case NodeType::Not:        return "NOT ";
        case NodeType::leq:        return "LEQ ";
        case NodeType::greq:       return "GREQ ";
        case NodeType::less:       return "LESS_THAN ";
        case NodeType::greater:    return "GREATER_THAN ";
        case NodeType::unary:      return "UNARY_MINUS(-) ";
        default:                   return "UNKNOWN ";
    }
}
