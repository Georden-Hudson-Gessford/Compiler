#include <iostream> 
#include "Token_Maker.h" 
//g++ Token_Test.cpp Token_Maker.cpp -o wh
bool check(bool condition, const std::string& message)
{
    if (!condition) {
        std::cerr << "FAILED: " << message << '\n';
        return false;
    }

    return true;
}


int ultimate_test() {
    std::cout << "calling ultimate_test:\n";
    auto ultimate_test = tokenizer(" A make write not is > < >= <= . if ( ) [ ] 89 ; | | = * + - /");


bool passed = true;

passed &= check(ultimate_test[0].type == TokenType::identifier, "Incorrect TokenType of token 1");
passed &= check(ultimate_test[1].type == TokenType::make, "Incorrect TokenType of token 2");
passed &= check(ultimate_test[2].type == TokenType::write, "Incorrect TokenType of token 3");
passed &= check(ultimate_test[3].type == TokenType::Not, "Incorrect TokenType of token 4");
passed &= check(ultimate_test[4].type == TokenType::is, "Incorrect TokenType of token 5");
passed &= check(ultimate_test[5].type == TokenType::greater, "Incorrect TokenType of token 6");
passed &= check(ultimate_test[6].type == TokenType::less, "Incorrect TokenType of token 7");
passed &= check(ultimate_test[7].type == TokenType::greq, "Incorrect TokenType of token 8");
passed &= check(ultimate_test[8].type == TokenType::leq, "Incorrect TokenType of token 9");
passed &= check(ultimate_test[9].type == TokenType::period, "Incorrect TokenType of token 10");
passed &= check(ultimate_test[10].type == TokenType::If, "Incorrect TokenType of token 11");
passed &= check(ultimate_test[11].type == TokenType::leftparentheses, "Incorrect TokenType of token 12");
passed &= check(ultimate_test[12].type == TokenType::rightparentheses, "Incorrect TokenType of token 13");
passed &= check(ultimate_test[13].type == TokenType::leftbracket, "Incorrect TokenType of token 14");
passed &= check(ultimate_test[14].type == TokenType::rightbracket, "Incorrect TokenType of token 15");
passed &= check(ultimate_test[15].type == TokenType::number, "Incorrect TokenType of token 16");
passed &= check(ultimate_test[16].type == TokenType::semicolon, "Incorrect TokenType of token 17");
passed &= check(ultimate_test[17].type == TokenType::assignment, "Incorrect TokenType of token 18");
passed &= check(ultimate_test[18].type == TokenType::asterisk, "Incorrect TokenType of token 19");
passed &= check(ultimate_test[19].type == TokenType::plus,"Incorrect TokenType of token 20");
passed &= check(ultimate_test[20].type == TokenType::minus, "Incorrect TokenType of token 21");
passed &= check(ultimate_test[21].type == TokenType::slash, "Incorrect TokenType of token 22");
passed &= check(ultimate_test[22].type == TokenType::end_token, "Incorrect TokenType of token 23");






return passed ? 0 : 1;
}

int if_tests() {
std::cout << "calling if_tests: \n";
bool passed = true;
auto if_A = tokenizer("if .think is am. [ write thing1; write thing2; write thing_3;]");
auto if_B = tokenizer("if .think is non. [write the_declaration_of_independence; make common_sense = 9; make mind = common_sense; make pi = 6/2; if .pi is 6/2. [write pi;]");
auto if_C = tokenizer( "if .1 < 2.[ if .4 > 2.[  if .3 not 5. [write 6;]]]");

passed &= check(if_A[0].type == TokenType::If, "incorrect TokenType of token 1");
passed &= check(if_A[0].pos == 0, "if_A[0] has wrong position");
passed &= check(if_A[6].type == TokenType::leftbracket, "incorrect TokenType of token 7");
passed &= check(if_A[8].lexeme == "thing1", "if_A[8] incorrect lexeme (not tokenizing thing1)");
passed &= check(if_A[9].type == TokenType::semicolon, "incorrect TokenType of token 10)");

passed &= check(if_B[1].type == TokenType::period, "if_B[1] incorrect TokenType at token 2");
passed &= check(if_B[4].type == TokenType::identifier, "if_B[4] Incorrect TokenType of token 5");
passed &= check(if_B[8].lexeme == "the_declaration_of_independence", "if_B[8]  incorrect lexeme (not tokenizing ''the_declaration_of_independence'')");
passed &= check(if_B[21].lexeme == "pi", "if_B[21] incorrect lexeme (not tokenizing pi)");
passed &= check(if_B[23].type == TokenType::number, "if_B[23] incorrect TokenType of token 22");

passed &= check(if_C[3].type == TokenType::less, "if_C[3] incorrect TokenType at token 4");
passed &= check(if_C[17].type == TokenType::Not, "if_C[17] incorrect TokenType at token 17");


return passed ? 0 : 1;
}

int write_tests() {
    std::cout << "calling write_tests: \n";
   bool passed = true;

auto write_A = tokenizer("write x;");
auto write_B = tokenizer("write x*5*4+3-p_u_l__s_e/tokenize_me_please+(400-token_me_lane);");
auto write_C = tokenizer("write halllllllllllllllllllllllllllliebunga;");
auto write_D = tokenizer("writequadrilater*quadrilateral*quadrisplatter;");

passed &= check(write_A[0].type == TokenType::write, " write_A[0] has incorrect TokenType");
passed &= check(write_A[0].pos == 0, "write_A[0] has wrong position");
passed &= check(write_A[0].lexeme == "write", "write_A[0] incorrect lexeme (not tokenizing ''write'')");

passed &= check( write_B[8].lexeme == "-", "write_B[8], expected ''-'' at token 9");
passed &= check(write_B[9].lexeme == "p_u_l__s_e", "write_B[9] expected p_u_l__s_e at index 10");
passed &= check(write_B[12].type == TokenType::plus, "write_B[12] expected TokenType plus at token 13");

passed &= check(write_C[0].type == TokenType::write, "write_C[0] has incorrect TokenType");
passed &= check(write_C[1].lexeme == "halllllllllllllllllllllllllllliebunga", "write_C[1] expected identiifer ''halllllllllllllllllllllllllllliebunga'' at index 1");

passed &= check(write_D[0].lexeme == "writequadrilater", "write_D[0] expected identiifer ''writequadrilater'' at token 1 ");
passed &- check(write_D[0].type == TokenType::identifier, "write_D[0] has incorrect TokenType");

    return passed ? 0 : 1;
}


int make_tests() {
    std::cout << "calling make_tests: \n";
   auto  make_A = tokenizer("make maker = 5;");
   auto make_B = tokenizer("make maker = makee;");
   auto make_C = tokenizer("make written = ism;");
   auto make_D = tokenizer("make some_variable = noted;");
   auto make_E = tokenizer("make p_u_l__s_e = 2500*3*4*5;");
   auto make_F = tokenizer("make maker = 5000000;");

bool passed = true;

passed &= check( make_A[0].pos == 0, "make_A[0] incorrect position");
passed &= check( make_A[1].type == TokenType::identifier, "make_A[1] incorrect TokenType");
passed &= check(make_A[1].lexeme == "maker", "make_A[1] incorrect lexeme (not tokenizing ''maker'')");
passed &= check(make_A.size() == 6, "make_A size is incorrect (missed or unloaded tokens)");

passed &= check(make_B[1].type == TokenType::identifier,"make_B[1] incorrectly mislabeled ''maker'' potentially as keyword ''make'');");
passed &= check(make_B[4].lexeme == ";", "make_[B} did not properly read the semicolon]");

passed &= check(make_C[3].type == TokenType::identifier, "make_C[3] incorrectly mislabeled ''ism'' potentially as keyword ''is'' ");

passed &= check (make_D[1].lexeme == "some_variable", "make_[D] incorrect lexeme (not tokenizing ''some_variable'')");
passed &= check (make_D[1].pos == 5, "make_D[1] incorrect position");
passed &= check (make_D[1].type == TokenType::identifier, "make_D[1] incorrect TokenType");
passed &= check (make_D[3].type == TokenType::identifier, "make_D[3] incorrectly mislabeled ''noted'' potentially as keyword not");

passed &= check (make_E[1].lexeme == "p_u_l__s_e", "make_E[1] mishandled underscores in identifier ''p_u_l__s_e''");
passed &= check (make_E[4].type == TokenType::asterisk, "make_E[4] wrong TokenType for operator ''*''");

passed &= check (make_F[3].lexeme == "5000000", "make_F[3] incorrect lexeme (not tokenizing ''5000000'')");
passed &= check (make_F[3].type == TokenType::number, "make_F[3] incorrect TokenType");




return passed ? 0 : 1;
}

int main() {
std::vector<std::vector<token>> make_tokens;
int passed = 0; 
int m = make_tests();
   if (m == 1) {
std::cout << m;
   passed = 1; }


int w =  write_tests();
if ( w == 1) {
    std:: cout << w;
    passed = 1;
}
int i = if_tests();
if ( i == 1) {
    std::cout << i;
    passed = i;
}
int u = ultimate_test();
if ( i == 1) {
    std::cout << u;
    passed = u;
}
    if (passed == 0){
        std::cout << "all tests passed";
    }
    

    return passed;
}
