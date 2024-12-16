# Kotlin Parser Project

## Requirements
To run this project make sure your system has `make`, `flex` and `bison` installed.

## Compilation
To compile the project, use the following commands:
```bash
make all       # Build the project
make install   # Install the target binary (optional)
```

## Running the Compiler
To see the created AST, Intermediate Code and resulting MIPS Assembly
```bash
build/kotlin.o file.kt
bin/kotlin file.kt
```
depending on if you ran `make build` or `make install`.

## Test Files
There exist 3 test files in the folder `test/files/`.
All test files run correctly in Mars4_5.

## Project Overview
This project implements a parser that reads a subset of Kotlin code and generates the corresponding MIPS Assembly.
The subset of Kotlin supported includes specific expressions, commands, and structures, as detailed below.

## Supported Language Constructs

### Expressions
- Arithmetic expressions: Basic mathematical operations (e.g., +, -, *, /)
- Boolean expressions: Logical operations (e.g., &&, ||, !)
- Function calls: Invocation of functions within the program
- Print function: Supports output with the print function
- Read function: Supports input with the readln function

### Statements
- Variable declarations and assignments: Definition and updating of variables
- Conditional expressions: if and if-else branches for conditional execution
- Loop statements:
  - while loops: Supports standard while loops
  - do loops: do-while loop support
  - for loops: Initialization, condition, and increment expressions within for loops

### Function Structure
- Function parameters: Ability to define and parse function parameters
- Return types: Definition of function return types

### Control Flow
- Return statements: Return expressions to terminate function execution
- When statements: when branch support for multi-condition checks

### Type Definitions (Note: not implemented in the assembly, only in the AST)
- Basic types: Support for various Kotlin types
- Enums: Block structure for defining enumerations within the program

## Authors
- Henrique Teixeira, Student ID: 202306640
- Rafael Silva, Student ID: 202108429

**Group:** T01_G13roup: T01_G13
