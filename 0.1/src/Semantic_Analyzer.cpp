#include <iostream>
#include <memory>
#include <unordered_map>
#include "Compiler_Parser.h"
#include "Semantic_Analyzer.h"



    int division_check(Node* node, std::unordered_map<std::string, std::pair<VariableInfo, std::string>>& Symbol_Table) {

                
         auto Operator = node->type;
             switch (Operator)         {    
             case (NodeType::add):
             return division_check(node->left.get(), Symbol_Table) + division_check(node->right.get(), Symbol_Table);
             case (NodeType::minus):
             return division_check(node->left.get(), Symbol_Table) - division_check(node->right.get(), Symbol_Table);
             case (NodeType::divide):
                if( division_check (node->right.get(), Symbol_Table) == 0)
             throw std::runtime_error("Undefined operation, [Division by Zero]");
             else
             return division_check(node->left.get(), Symbol_Table) / division_check(node->right.get(), Symbol_Table);
             case (NodeType::multiply): 
             return division_check(node->left.get(), Symbol_Table) * division_check(node->right.get(), Symbol_Table);
             default:  
             if(isdigit(node->string_token[0]))
             return stoi(node->string_token);
             else 
             return stoi(Symbol_Table[node->string_token].second);
    }


    }

    void Semantic_Analyzer::analyze_condition (Node* node, std::unordered_map<std::string, std::pair<VariableInfo, std::string>>& Symbol_Table) {

        auto left = analyze_expression(node->left.get(), Symbol_Table);
        auto right = analyze_expression(node->right.get(), Symbol_Table);

        if ( left != right)
        throw std::runtime_error ("Mismatched data types in condtition statement");

        return;
                                 
    }

    ValueType Semantic_Analyzer::analyze_expression(Node* node, std::unordered_map<std::string, std::pair<VariableInfo, std::string>>& Symbol_Table) {

// for case identifier


        switch (node->type) {

            case NodeType::unary:
            if ( analyze_expression(node->right.get(), Symbol_Table) == ValueType::integer)
            return ValueType::integer;
            else
            throw std::runtime_error ("negative sign attatched to non-numeric type");

        case NodeType::number:
        return ValueType::integer;

        case NodeType::identifier:  {


                 auto find_on_table = Symbol_Table.find(node->string_token);
       
                 
    

            if (find_on_table == Symbol_Table.end()) {
                throw  std::runtime_error(
                    "Undefined identifier: " + node->string_token + " at position " + std::to_string(node->pos)
                ); 
             }

            return find_on_table->second.first.value;
            }

            case NodeType::add: 
            case NodeType::minus:
            case NodeType::divide:
            case NodeType::multiply:{ 
            if ( division_check(node, Symbol_Table)  == std::string::npos)
             throw std::runtime_error("Undefined operation, [Division by Zero]");


                    

                    auto type_check= node->right->type;
             switch (type_check)         {    
             case (NodeType::add):
             case (NodeType::minus):
             case (NodeType::divide):
             case (NodeType::multiply): 
            ValueType left = analyze_expression(node->left.get(),  Symbol_Table);
            ValueType right = analyze_expression(node->right.get(), Symbol_Table);
            
          
    
        if (left != ValueType::integer ||  right
         != ValueType::integer ) {
            throw std::runtime_error(" Arithmetic requires integers");
        }
     }
        
    } default: return ValueType::integer;
     } 
     }
    
    void Semantic_Analyzer::analyze_assignment( Node* node, std::unordered_map<std::string, std::pair<VariableInfo, std::string>>& Symbol_Table)  {
        //make sure to check if its new assignment or existing assignment 

        if (node->left->type != NodeType::identifier)
        throw std::runtime_error ( "assignment may only apply to a valid identifier" + node->left->string_token + " is not a valid identifier");



          auto it = Symbol_Table.find(node->left->string_token);

         
          
            //Not found, first initialization
                VariableInfo v;
                v.initialized = true;
                v.value = analyze_expression(node->right.get(), Symbol_Table);
                
            if ( it == Symbol_Table.end()) {
                Symbol_Table.insert({node->left->string_token, make_pair(v, node->right->string_token)});
                return; }
            
          

          else {
   
        ValueType left = Symbol_Table[node->left->string_token].first.value;
        ValueType right = analyze_expression(node->right.get(), Symbol_Table);
        if ( left != right) 
            throw std::runtime_error("Value type of variable" + node->string_token + " at pos " + std::to_string(node->pos) +  " does not match Value Type of expression " );
            
     else   {
Symbol_Table[node->left->string_token] = make_pair(v, node->right->string_token);
     }
    return;
    }
   
    
    }

    void Semantic_Analyzer::analyze_write(Node* node, std::unordered_map<std::string, std::pair<VariableInfo, std::string>>& Symbol_Table) {

    analyze_expression(node->right.get(), Symbol_Table);

    return; //analyze_expresison will hold the errors 
    }





    void Semantic_Analyzer::analyze_if(Node* node,  std::unordered_map<std::string, std::pair<VariableInfo, std::string>>& Symbol_Table) {


        //handle a condition
        analyze_condition(node->left.get(), Symbol_Table);

       std::unordered_map<std::string, std::pair<VariableInfo, std::string>> branch_table = Symbol_Table;
       
        for (const auto& statement : node->block) {
        semantic_analysis(statement.get(), branch_table);
    }


    }

 

//we need to move recursively 

void Semantic_Analyzer::semantic_analysis( Node* root,  std::unordered_map<std::string, std::pair<VariableInfo, std::string>>& Symbol_Table) {


if (root == nullptr) return;
if(root->type == NodeType::var_assign) 
analyze_assignment(root, Symbol_Table);

if (root->type == NodeType::if_stmt)
analyze_if(root, Symbol_Table);

if (root->type == NodeType::print_stmt)
analyze_write(root, Symbol_Table);


}

void Semantic_Analyzer::The_router(const std::vector<std::unique_ptr<Node>>& roots) {
    std::unordered_map<std::string, std::pair<VariableInfo, std::string>> Symbol_Table;
    for (auto& root : roots) {
        semantic_analysis(root.get(), Symbol_Table);
    }



}
    
    
