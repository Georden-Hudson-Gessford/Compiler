
# August 8, 2026
## Goals
* Tokenize an if statement such as:
* if . Polar is 5. [ write Polar; ]
* Add whitespace skipping.
* Begin using CMake.
* Create a JSON debugging configuration.
## Achieved
* Successfully tokenized complete statements such as:
* if . Polar is 5. [ write Polar; ]
* Extended the tokenizer to process multiple statements in a single pass, including programs such as:
* make x = 6; write 7; if . x not 7. [ write x; ]
* Added whitespace skipping to the tokenizer.
* Created a JSON debugging configuration and integrated the project with CMake to streamline building and debugging.
## Milestone

The tokenizer could now process small multi-statement programs rather than isolated tokens.

# August 9, 2026
## Goals
* Create tokenizer error-handling functions.
* Add parentheses support.
* Fix tokenizer bugs involving token positions and keyword/identifier conflicts.
## Achieved
* Added comment support and allowed the lexer to skip comments.
* Created lexer error handling for:
* incomplete comments
* expected tokens
* unsupported tokens
* Added parentheses support.
* Fixed bugs involving returned token positions.
* Fixed conflicts between keyword recognition and identifiers.
* Began implementing the parser.
## Milestone

The lexer moved from basic token recognition toward a more complete lexical front end with error handling and syntax support.

# August 10, 2026
## Goals
* Begin tokenizer unit tests.
* Parse if, write, and make statements.
## Achieved
* Completed the basic parser structure.
* Inspected AST construction using debugger breakpoints.
* Completed approximately half of the tokenizer tests.
* Began learning the x86 assembly concepts needed for the compiler backend.
## Design Note

Representing unary minus as its own AST node may require clarifying the EBNF grammar so the grammar and implementation match cleanly.

## Milestone

Source code was now beginning to transform from a token stream into a structured Abstract Syntax Tree.

# August 11, 2026
## Goals
* Finish tokenizer tests.
* Automate tests using CTest.
* Begin parser tests.
* Implement AST traversal for easier inspection.
* Finish the parser.
## Progress
* Continued development and debugging of parser behavior.
* Continued building automated testing infrastructure.
* Worked toward replacing breakpoint-only AST inspection with a printable tree representation.
* Refined the AST node structure and parser handling needed for expressions and statements.
## Focus

This day primarily connected the lexer, parser, tests, and AST-debugging infrastructure in preparation for completing the parser.

#August 12, 2026
## Achieved
* Finished the parser.
* Implemented recursive AST traversal that prints the syntax tree sideways.
* Inspected parser behavior using CMake debug builds.
* Began implementing semantic analysis.
* Added basic compile-time division-by-zero checking.
* Introduced a symbol table to validate variable semantics.
 ## Milestone

The compiler front end was now capable of producing an AST and beginning semantic validation rather than only checking syntax.

# August 13, 2026
## Achieved
* Added semantic handling for if statement scopes.
* Used temporary symbol tables for nested scopes.
* Variables defined outside an if block remained visible inside the block.
* Variables created inside the block were tracked separately so their scope could be restricted appropriately.
* Began generating Three-Address Code (TAC).
* Added TAC printing to manually inspect generated intermediate instructions.
## Milestone

The compiler gained both lexical scoping behavior and an intermediate representation between the AST and machine-specific assembly.

# August 14, 2026
## Achieved
Began implementing the ASSEMBLY_GENERATOR.
Started translating TAC instructions into NASM-compatible x86-64 assembly.
## Milestone

Development moved from the compiler front end and intermediate representation into the backend.

# August 15, 2026
## Achieved
* Worked on implementing the write statement at the assembly level.
* Implemented the functionality required for compiled programs to print output.
* Ran generated code through the assembler/toolchain and tested execution on the CPU.
* Finished the Token Maker test suite.
## Milestone

The compiler reached native execution: source code could travel through the compiler pipeline and ultimately execute as machine code.

# August 17, 2026
## Achieved
* Fixed architectural crossover between TAC and NASM syntax.
* Previously, the TAC generator inserted assembly-specific bracket syntax.
* Removed NASM-specific representation from TAC.
* Moved memory/address formatting into ASSEMBLY_GENERATOR, where machine-specific syntax belongs.
* Began improving division-by-zero analysis.
## Design Improvement

* The compiler pipeline now had a cleaner separation of responsibilities:

* Source → AST → Semantic Analysis → TAC → Assembly

* TAC remained machine-independent, while NASM-specific syntax became the responsibility of the backend.

# August 20, 2026
## Achieved

* Enhanced compile-time division-by-zero detection.

* The semantic analyzer could now detect indirect constant-zero expressions such as:

* make x = 0;
* make y = 1 / (x + 1 - 1);

 and correctly report division by zero.

## Milestone

Semantic analysis progressed beyond simple literal checks and began performing limited compile-time expression evaluation.

# August 26, 2026
## Achieved
* Added proper lexer termination when unidentified or unsupported tokens are encountered.
* Invalid lexical input now produces an explicit compiler error instead of allowing processing to continue incorrectly.
## Milestone

Improved compiler robustness by ensuring malformed source programs terminate cleanly during lexical analysis.



