
# TAC Generation
* The Intermediate Representation (IR) takes the structure represented by the AST and converts it into a simpler form that can be more easily analyzed and eventually transformed into assembly.
* This compiler uses Three-Address Code (TAC) as its intermediate representation.

* Whereas the AST is a hierarchical structure of nodes, TAC is generally represented as a linear sequence of simple operations.

* A TAC instruction can contain up to three names or addresses: usually two input operands and one output/result.
* For a binary operation, an instruction can have the form:
* (result = Operand_1 (operation) Operand_2)
* EX: make y = x + 3 * 4; 
* becomes:
* t0 = 3*4
* t1 = x + t0
* y = t1
* The final instruction:

* y = t1

* is a simple assignment and has the general form:

* A unary operation such as the unary minus might look like: 
* (result = (operation) Operand_1)
* EX: make y = -x; becomes :
* t0 = - x;
* y = t0;
## Temporary Variables
* Temporary variables such as t0, t1, and t2 are compiler-generated names used to represent intermediate values.

* For example:

* t0 = 3 * 4

* means that the result of 3 * 4 is represented by the temporary t0. Later TAC instructions can use t0 as an operand.

* Temporary variables are not necessarily actual memory locations. During assembly generation, a temporary could eventually be represented using a register, stack location, memory location, or possibly optimized away.

## Labels
Control flow in TAC is represented with labels
* For example: (if .x > 5, [ write x; ])  Becomes:
* t0 = x > 5
* ifFalse t0 goto L0
* write x
* L0;
* Importantly, L0 is not a variable or piece of data. It identifies a location in the instruction sequence.
* causes the program to skip write x and continue execution at:

* L0:
* A label itself does not perform a jump. It simply provides a target that branch instructions can reference.
## Jumps
* TAC can contain both conditional and unconditional jumps.

* An unconditional jump has the form:

* goto Label

* For example:

* goto L3

* Execution immediately continues at L3.

* A conditional jump can be represented in several ways.
* However, they have the general form of if x relop y goto L
* where the relational operator may be <, >, <=, >=, ==, etc.
* One form first evaluates the comparison:

* t0 = a < b
* ifFalse t0 goto L0

* Another common TAC representation places the comparison directly in the branch:

* if a < b goto L0

* where the relational operator may be <, >, <=, >=, ==, etc.

* Both representations express the same general idea: control flow can change depending on the result of a condition.

