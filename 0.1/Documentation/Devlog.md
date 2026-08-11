
# August 8th 2026
## Goals:
Tokenize "if .Polar is 5. [ write Polar; ]
Add Skip whitespace
Use CMake
make JSON
## Achieved:
properly tokenized : if .Polar is 5. [ write Polar; ] and multiple statements such as make x = 6; write 7; if . x not 7. [write x]; all through one pass;
Created a JSON configuration combined with CMake to streamline debugging
Added whitespace skipping to the tokenizer;
# August 9th 2026

## Goal : 
Tokenizer: create error function
Tokenizer: added parentheses support
Tokenizer: fixed bugs in end_pos return, key word and identifier conflict.
## Achieved:
Created comment line support (skipping them)
created error functions (incomplete comment, expected token, unsupported token)
created parentheses support
began working on parser

# August 10th 2026

## Goal :
begin creating tests for tokenizer
be able to parse if, write, and make statements;

##Achieved :
finished parser structure
inspected the AST formation using breakpoints (looks cool)
finished approximately half of tokenizer tests
learning basic assembly
##Note :
use of unary minus as a tree node may require editing EBNF for clarity

# August 11th 2026
##Goal :
finish tests for tokenizer
automate tests using Ctests
write tests for parser
print the AST through traversal to check formation quickly and easily
finish parser
