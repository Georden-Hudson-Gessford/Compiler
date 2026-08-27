#include <string>
#include <vector>
#include <unordered_set>
#include "TAC_GENERATOR.h"
#include "ASSEMBLY_GENERATOR.h"
#include <iostream>


operand opera(std::string c) {
  operand O;
 
    if (!isalpha(c[0])) {
    O.type = operand_type::immutable;
    O.output = c;

    }
    
    else {
    O.type = operand_type::variable;
    O.output =  "[" + c + "]";  
   }

    return O;
}




void SECTION_BSS (const std::vector<instruct>& instructions) {

std::unordered_set<std::string> check_set;
std::cout <<  "default rel \n" 
<< "section .bss\n";

for (const auto& instruction : instructions) {

    if ( instruction.declarer != ""){
        if (!check_set.count(instruction.declarer)) {
   std::cout << instruction.declarer << ": resq 1 \n";
    check_set.insert(instruction.declarer); }
    }

}

}
void GENERATE_ASSIGNMENT(const instruct& instruction) {

std::string registered = "rax";
std::string variable = opera(instruction.result).output;
std::string arg1 = opera(instruction.arg1).output;
std::string move = "mov ";

std::cout << move << registered << ", " << "" << arg1 << " \n"
 << move  <<  variable << "," << " " << registered << "\n \n";

} 




void GENERATE_LABEL(const instruct& instruction) {

std::string label = instruction.result;



std::cout << label << ": \n";



}


void GENERATE_PRINT(const instruct& instruction) {

std::string arg1 = opera(instruction.arg1).output;
std::string move = "mov ";
std::string registered = "rax, ";

std::cout << "lea rdi, [rel fmt]\n" 
<< move << "rsi, " <<  arg1 << "\n" 
<<  "xor " << "eax, " "eax\n"
"call printf \n";

}
void GENERATE_JUMP(const instruct& instruction)  {
std::string arg1 = instruction.arg1;
std::string label = instruction.result;

std::cout <<  " " << label << "\n";



}

void GENERATE_CONDITION(const instruct& instruction) {
std::string move = "mov ";
std::string operation = "cmp ";
std::string registered = "rax";




std::string arg1 = opera(instruction.arg1).output;
std::string arg2 = opera(instruction.arg2).output;
std::string jump;
switch (instruction.operation) {

    case TAC_OP::equal:
    jump = "jne";
    break;
    case TAC_OP::not_equal:
    jump = "je";
    break;
    case TAC_OP::leq:
    jump = "jg";
    break;
    case TAC_OP::less:
    jump = "jge";
    break;
    case TAC_OP::greater:
    jump = "jle";
    break;
    case TAC_OP::greq:
    jump = "jl";
    break;

}

std::cout << move << registered << ", " << arg1 << "\n" 
<< operation <<  registered << ", "  << arg2 << "\n" 
<< jump << " ";
}


//to handle the division by 0 . Just handle the denominator expression
//expression equivalent to 0 or a variable holding 0
// the data strucutre 'operand' can be used?
//it has to be a semantics issue 

void GENERATE_DIVISION(const instruct& instruction) {
std::string operation = "idiv";
std::string addr1 = "rbx";
std::string addr2 = "rax";
std::string move = "mov ";
std::string arg1 = opera(instruction.arg1).output;
std::string arg2 = opera(instruction.arg2).output;


std::cout << move << addr2 << ", " << arg1 << "\n"
  << "cqo"  << "\n" 
  << move << addr1 << ", " << arg2 << "\n" 
  <<  operation << " " << addr1  << "\n" 
  << move <<  opera(instruction.result).output << ", " << addr2 << "\n";


}

void GENERATE_UNARY (const instruct& instruction) {

std::string arg1 = opera(instruction.arg1).output;
std::string move = "mov ";
 std::string  operation = "neg ";

std::string registered = "rax";
std::cout << move << registered << ", " << arg1 << "\n"
<< operation << registered  << "\n" << move << "" << instruction.result << ", " << registered << "\n";  
 
}



void GENERATE_OPERATION (const instruct& instruction) {
std::string operation;
std::string move = "mov ";
std::string registered = "rax";
std::string arg1 = opera(instruction.arg1).output;
std::string arg2 = opera(instruction.arg2).output;

switch (instruction.operation) {

    case TAC_OP::add:
    operation = "add ";
    break;
    case TAC_OP::subtract:
    operation = "sub ";
    break;
    case TAC_OP::multiply:
    operation = "imul ";
    break;
   
     
}
//this no longer handles unary 
std::cout << move << registered << ", " <<  arg1 << "\n" 
<<  operation << registered  << ", " << arg2 <<"\n"
  << move << "" << instruction.result << ", " << registered << "\n";
}





void ASSEMBLE_ME(const std::vector<instruct>& instructions) {
    
SECTION_BSS (instructions);
std::cout << "section .data\n" 
<< " fmt: db \"%ld\", 10, 0\n \n";

std::cout << "section .text \n" 
          << "global main\n \n"
          << "extern printf\n"
          << " main: \n";

for  (const auto& instruction : instructions) {

    switch (instruction.operation) {
    case TAC_OP::add:
    case TAC_OP::subtract:
    case TAC_OP::multiply:
      GENERATE_OPERATION(instruction);
      break;
    case TAC_OP::unary:
    GENERATE_UNARY(instruction);
    break;
    case TAC_OP::assignment:
    GENERATE_ASSIGNMENT(instruction);
    break;
     case TAC_OP::divide:
      GENERATE_DIVISION(instruction);
      break;
    case TAC_OP::write:
    GENERATE_PRINT(instruction);
    break;
    case TAC_OP::leq:
    case TAC_OP::less:
    case TAC_OP::greater:
    case TAC_OP::greq:
    case TAC_OP::equal:
    case TAC_OP::not_equal:
    GENERATE_CONDITION(instruction);
    break;
    case TAC_OP::jump:
    case TAC_OP::jump_if_false:
    GENERATE_JUMP(instruction);
    break;
    case TAC_OP::label:
    GENERATE_LABEL(instruction);
    break;
    default :
    throw std::runtime_error("No TAC_OP has been assigned");
    
    }
    
}
std:: cout <<" mov rax, 60\n" 
<< "mov rdi, 0\n"
<< "syscall";


}
