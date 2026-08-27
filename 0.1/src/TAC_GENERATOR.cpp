#include "TAC_GENERATOR.h"



    std::string TAC::new_temp()
    {
        return "t" + std::to_string(temp_counter++);
    }

    std::string TAC::new_label() {
        return "L" + std::to_string(label_counter++);
    }

void TAC::write_generate(Node* node ) {
std::string left = Express_Generate(node->right.get());
instruct write;

write.arg1 = left;
write.operation = TAC_OP::write;
tac.push_back(write);
}


void TAC::assigment_generate(Node*  node ) {

instruct assignment;

assignment.result =  node->left->string_token;
assignment.declarer = node->left->string_token;
assignment.arg1 = Express_Generate(node->right.get());
assignment.operation = TAC_OP::assignment;

tac.push_back(assignment);
}



std::string TAC::Express_Generate(Node*  node) {


  if (!node)
        throw std::runtime_error("Null expression in TAC generator");

instruct expression;

if (node->type == NodeType::number)
return node->string_token;

if ( node->type == NodeType::identifier) {

return node->string_token;}

std::string temp = new_temp();

if (node->type == NodeType::unary){
    auto right = Express_Generate(node->right.get());
    expression.result =  temp;
    expression.declarer = temp;
    expression.arg1 = right;
    expression.operation = TAC_OP::unary;
    tac.push_back(expression);
    return temp;
}


auto left = Express_Generate(node->left.get());
auto right = Express_Generate(node->right.get());

    expression.declarer = temp;
    expression.result = temp;
    expression.arg1 = left;
    expression.arg2 = right;

    switch (node->type) {

        case NodeType::add:
            expression.operation = TAC_OP::add;
            break;

        case NodeType::minus:
            expression.operation = TAC_OP::subtract;
            break;

        case NodeType::multiply:
            expression.operation = TAC_OP::multiply;
            break;

        case NodeType::divide:
            expression.operation = TAC_OP::divide;
            break;
        

        default:
            throw std::runtime_error(
                "Invalid expression node in TAC generation");
        
   
    }
tac.push_back(expression);


 return temp;
}



std::string TAC::Condition_Generate(Node* node) {


  if (!node)
        throw std::runtime_error("Null expression in TAC generator");


auto left = Express_Generate(node->left.get());
auto right = Express_Generate(node->right.get());
 
std::string temp = new_temp();
instruct condition;
condition.arg1 = left;
condition.arg2 = right;
condition.declarer = temp;
condition.result = temp;


switch (node->type) {

        case NodeType::less:
            condition.operation = TAC_OP::less;
            break;

        case NodeType::greater:
            condition.operation = TAC_OP::greater;
            break;

        case NodeType::leq:
            condition.operation = TAC_OP::leq;
            break;

        case NodeType::greq:
            condition.operation = TAC_OP::greq;
            break;

        case NodeType::is:
            condition.operation = TAC_OP::equal;
            break;

        case NodeType::Not:
            condition.operation = TAC_OP::not_equal; 
            break;

        default:
            throw std::runtime_error(
                "Invalid expression node in TAC generation");
            }
       
        tac.push_back(condition);
        return temp;
}

void TAC::if_generate(Node* node) {

instruct  branch;
std::string end_label = new_label();

branch.arg1 = Condition_Generate(node->left.get());
branch.result = end_label;
branch.operation = TAC_OP::jump_if_false;
tac.push_back(branch);

generate_block(node->right->block);

instruct label;
label.result = end_label;
label.operation = TAC_OP::label;
tac.push_back(label);


}

 void TAC::generate_block(const std::vector<std::unique_ptr<Node>>& roots) {


    for (const auto& ptr : roots) {
          Node* root = ptr.get();
    
             switch (root->type) {

            case NodeType::var_assign:
                assigment_generate(root);
                break;

            case NodeType::print_stmt:
                write_generate(root);
                break;

            case NodeType::if_stmt:
                if_generate(root);
                break;

            default:
                throw std::runtime_error(
                    "Unsupported statement in TAC generator"
                );
        }
    }



 }

  std::vector<instruct> TAC::generate(const std::vector<std::unique_ptr<Node>>& roots) {


//reset for new compilation
     tac.clear();
    temp_counter = 0;
    label_counter = 0;

    generate_block(roots);

    return tac;

}

  
