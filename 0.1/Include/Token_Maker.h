#ifndef TTOOKEN
#define TTOOKEN
#include <vector>
#include <string>
#include <unordered_map>


enum class TokenType {

number,
identifier,

//logic operators
less,
greater,
leq,
greq,
is,
Not,

//Assign
assignment,

//arithmetic
asterisk,
plus,
slash,
minus,

//Delimiters 
leftbracket,
rightbracket,
semicolon,
period,
leftparentheses,
rightparentheses,

//keyword
If,
make,
write,


//special

end_token








};
struct token {
TokenType type;
std::string lexeme;
size_t pos;

};
int token_maker (std::vector<token>&, int i, int size, const std::string& e, TokenType);
std::vector<token> tokenizer(const std::string& e);
void token_error(char c, size_t pos);
void comment_error(size_t pos);




#endif
