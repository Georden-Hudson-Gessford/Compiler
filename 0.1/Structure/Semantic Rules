
# Semantic Rules

#make x = expression; creates x if it does not already exist. If x already exists, the statement updates its value.

An identifier used in an expression must already be definitely initialized before that expression is evaluated.

Example:

write x;

is invalid unless x has previously been initialized.

A variable's type is inferred when it is first created.

Example:

make x = 8;

infers:

x : integer
Once additional data types are introduced, a variable will retain the type inferred when it was first created. Reassigning a value of an incompatible type will be a semantic error.
Arithmetic operators +, -, *, and / require integer operands.
Comparison operators <, <=, >, >=, is, and not require compatible operand types. In compiler version 0.1, integers are the only supported type.

Division by a compile-time-known zero is a compile-time error.

Example:

make x = 5 / 0;

produces an error.

Division by a value that cannot be proven to be zero at compile time must be handled at runtime.

Example:

make x = 5 / y;

cannot necessarily be rejected during compilation because the value of y may not be known.

Definite Initialization and Global Scope

Compiler version 0.1 uses a single global scope.

However, being globally scoped does not mean that a variable is necessarily initialized.

A variable is considered definitely initialized only when the compiler can guarantee that its initialization executes before every possible use.

For example:

make x = 5;

if .x > 10. [
    make y = 7;
]

write y;

is rejected because the condition may be false, meaning y may never be initialized.

The following is valid:

make x = 5;
make y = 0;

if .x > 10. [
    make y = 7;
]

write y;

because y is guaranteed to have been initialized before write y; executes.
