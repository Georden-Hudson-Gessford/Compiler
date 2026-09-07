
# Grammar 

program ::= { statement };

statement ::= variable_assignment
            | if_statement
            | print_statement
            ;

variable_assignment ::= "make" identifier "=" expression ";" ;

if_statement ::= "if" "." condition "." "[" { statement } "]" ;

print_statement ::= "write" expression ";" ;

condition ::= expression comparison_operator expression ;

comparison_operator ::= "<"
                      | "<="
                      | ">"
                      | ">="
                      | "is"
                      | "not"
                      ;

expression ::= term { ("+" | "-") term } ;

term ::= factor { ("*" | "/") factor } ;

factor ::= "-" factor
         | primary
         ;

primary ::= integer
          | identifier
          | "(" expression ")"
          ;

identifier ::= letter { letter | digit | "_" } ;

integer ::= digit { digit } ;
comment ::= "|" you can really write anything here except | "|" ; 



# Decision Reasoning:
The language is intended to have clear visibility of when a variable is being adjusted. All variables must be initialized once declared and use the make keyword
the negate operator is "not" for readabilty
This version of the coompiler will use a single, global scope.
make is required for every operation that creates or mutates a variable. If the identifier does not yet exist in the current scope (which can only be global right now), make creates it. Otherwise, make updates its value.
The language is intended to have quick typing ability and uses less characters that normally require shift
examples are blocks utilizing "[]" and not "{}", "." replacing parentheses and also uses static type inference, arithmetic still uses parentheses;

# Language examples:


## variable initializaiton and declaration
make x = 8;

## if_statement
if .x is 8. [
 make x = x +1;
]

## arithemtic

make x = 5 * x;
write 4 / 4;
make x = 1 - x ;

## Logic
x is 2;
x not 2;
x > 2;
x < 2;
x >= 2;
x <= ;

## printing
write x (prints out the data x represents)


## Example program
make x = 8;
make y = 4;

make result = x + y * 2;

if .result is 16. [
    write result;
]

if .result not 10. [
    make result = result + 1;
]


