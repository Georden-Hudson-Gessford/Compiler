#include "Token_Maker.h"
#include <iostream>


size_t number_token (const std::string& e, size_t i, std::vector<token>& tokens) {
token t;

size_t end_pos = e.find_first_not_of( "1234567890", i);
if (end_pos == std::string::npos)
end_pos = e.size();
t.lexeme = e.substr(i, end_pos - i);
t.pos = i;
t.type = TokenType::number;
tokens.push_back(t);
return end_pos -1;


}
void token_error(char c, size_t pos) {

    std::cout   
            << "LEXICAL ERROR:\n"
            << "Type: \n" 
            << "unsupported character: \n" 
            << c
            << "at position: " << pos  << "\n";

}

void comment_error(size_t pos) {


    std::cout 
            << "COMMENT ERROR:\n"
            << "EXPECTED | TO MATCH | AT POS : " 
            << pos << "\n";
            
}

std::vector<token> tokenizer(const std::string& e) {
std::vector<token> tokens;

std::unordered_map<std::string, TokenType> keyword_map = {

    {"make", TokenType::make}, 
    {"write", TokenType::write },
    { "not", TokenType::Not }, 
    {"if", TokenType::If}, 
    { "is", TokenType::is} };

    for (size_t i = 0; i < e.size(); i++) {
        token t;
char c = e[i];
if (isalpha(c)) {


size_t j = i;


    while ((j < e.size()) && (isalnum(static_cast<int>(e[j])) || e[j] == '_')) {
    j++;
    }
    
t.lexeme = e.substr(i, j - i);
t.pos = i;
i = j -1;
if (keyword_map.count(t.lexeme))
t.type = keyword_map[t.lexeme];
else
t.type = TokenType::identifier;


tokens.push_back(t);
continue;

}


 if (c == '|') {
    size_t closing = e.find_first_of("|", i  +1 );
    if ( closing == std::string::npos) {
        comment_error(i);
        return tokens;
    }
    else 
    i = closing;
    continue;
    }

if ( isspace(c))
continue;

if (isdigit(c)) {
    i = number_token(e, i ,tokens);
    continue;
}


switch (c) {
 case '=' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::assignment;
    t.pos = i;
    tokens.push_back(t);
    continue;
 
case '.' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::period;
    t.pos = i;
    tokens.push_back(t);
    continue;

case ';' : 
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::semicolon;
    t.pos = i;
    tokens.push_back(t);
    continue;
case '[' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::leftbracket;
    t.pos = i;
    tokens.push_back(t);
    continue;
case ']' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::rightbracket;
    t.pos = i;
    tokens.push_back(t);
    continue;
case '(' : 
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::leftparentheses;
    t.pos = i;
    tokens.push_back(t);
    continue;
case ')' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::rightparentheses;
    t.pos = i;
    tokens.push_back(t);
    continue;
case '*' :
    t.lexeme = e.substr(i ,1);
    t.type = TokenType::asterisk;
    t.pos = i;
    tokens.push_back(t);
    continue;
case '/' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::slash;
    t.pos = i;
    tokens.push_back(t);
    continue;
case '+' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::plus;
    t.pos = i;
    tokens.push_back(t);
    continue;
case '-' :
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::minus;
    t.pos = i;
    tokens.push_back(t);
    continue; 
case '<' : 
    if (i + 1 < e.size() && e[i+1] == '=' ) {
        t.lexeme = e.substr(i, 2);
        t.type = TokenType::leq;
        t.pos = i;
        tokens.push_back(t);
        i += 1;
        continue; }
    else  
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::less;
    t.pos = i;
    tokens.push_back(t);
    continue;
case '>' : 
    if (i + 1 < e.size() && e[i+1] == '=' ) {
        t.lexeme = e.substr(i, 2);
        t.type = TokenType::greq;
        t.pos = i;
        tokens.push_back(t);
        i += 1;
        continue; }
    else  
    t.lexeme = e.substr(i, 1);
    t.type = TokenType::greater;
    t.pos = i;
    tokens.push_back(t);
    continue;

}

   token_error(c, i);
   continue;
    }
    token end;
    end.lexeme = "";
    end.pos = std::string::npos;
    end.type = TokenType::end_token;
    tokens.push_back(end);
    return tokens;
};
