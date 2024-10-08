# Lexer Documentation

## Overview

This documentation provides an overview of the lexer implementation in C++ (GCC VERSION 13.2.0). A lexer (or lexical analyzer) is responsible for breaking down the input source code into tokens, which are the basic building blocks of the programming language.

## Project Structure

The project consists of the following files:

-   `main.cpp`: The main entry point of the program.
-   `lexer.hpp`: Header file containing the `Lexer` class and associated types.
-   `lexer.cpp`: Implementation file for the `Lexer` class.

## Compilation and Execution

To compile and run the lexer, use the following commands:

```bash
g++ main.cpp lexer.cpp -o main
./main ./examples/input.txt ./examples/output.txt
```

## Lexer Class

The `Lexer` class is responsible for tokenizing the input string. It uses various methods to handle different types of tokens, including keywords, identifiers, numbers, and operators.

### Public Methods

-   `void tokenize(const std::string& input)`:

    -   **Description**: Tokenizes the input string into tokens and prints them.
    -   **Parameters**:
        -   `input`: The string to tokenize.

-   `void writeTokensToFile(const std::string& filename)`:
    -   **Description**: Writes the token information to a specified file.
    -   **Parameters**:
        -   `filename`: The name of the file where the tokens will be written.

### Private Methods

-   `void printToken(const Token& token)`:

    -   **Description**: Prints the token type and value.
    -   **Parameters**:
        -   `token`: The token to print.

-   `void handleComment(const std::string& input, size_t& idx)`:

    -   **Description**: Skips comments in the input string.
    -   **Parameters**:
        -   `input`: The input string.
        -   `idx`: The current index in the input string.

-   `void handleNumber(const std::string& input, size_t& idx)`:

    -   **Description**: Handles integers and floating-point numbers in the input.
    -   **Parameters**:
        -   `input`: The input string.
        -   `idx`: The current index in the input string.

-   `void handleIdentifier(const std::string& input, size_t& idx)`:

    -   **Description**: Handles identifiers and keywords in the input string.
    -   **Parameters**:
        -   `input`: The input string.
        -   `idx`: The current index in the input string.

-   `void handleOperator(const std::string& input, size_t& idx)`:

    -   **Description**: Handles operators and other special characters in the input.
    -   **Parameters**:
        -   `input`: The input string.
        -   `idx`: The current index in the input string.

-   `std::string getTokenType(const Token &token)`:

    -   **Description**: Retrieves the string representation of a token's type.
    -   **Parameters**:
        -   `token`: The Token object for which to get the type.
    -   **Returns**: A string representing the type of the token (e.g., "Keyword", "Identifier", etc.).

## Token Structure

The `Token` structure is used to represent tokens in the lexer. Each token has a type and a value.

### Fields

-   `TokenType type`: The type of the token, defined by the `TokenType` enum.
-   `std::string value`: The string value of the token.

### TokenType Enum

The `TokenType` enum represents the different types of tokens that the lexer can recognize:

-   `Keyword`: Reserved words like `if`, `else`, `while`, etc.
-   `Identifier`: Variable names and function names.
-   `Integer`: Integer literals.
-   `Float`: Floating-point literals.
-   `Addition`, `Subtraction`, `Multiplication`, `Division`, `Power`, `Modulo`: Arithmetic operators.
-   `LThan`, `GThan`, `NotEqual`, `Equal`, `LEqual`, `GEqual`: Comparison operators.
-   `Assignment`: The assignment operator `=`.
-   `And`, `Or`, `Not`: Logical operators.
-   `LPar`, `RPar`, `LBrac`, `RBrac`: Parentheses and brackets.
-   `Semicolon`, `Comma`: Punctuation marks.
-   `Comment`: Represents comments (skipped in tokenization).
-   `Unknown`: Any unrecognized token.

## Tokenization Process

The lexer processes the input string one character at a time, determining the type of each token. It skips whitespace and comments, handles numbers (both integers and floating-point), identifies keywords and variable names, and recognizes operators and punctuation.

### Example

For the following input:

```
{
    while (i < 0) {i = anIdent234 12
    if i22!=0 return 4;
}
```

The lexer would produce the following tokens:

```bash
Token: LPar({)
Token: Keyword(while)
Token: LBrac(()
Token: Identifier(i)
Token: LThan(<)
Token: Integer(0)
Token: RBrac())
Token: LPar({)
Token: Identifier(i)
Token: Assignment(=)
Token: Identifier(anIdent234)
Token: Integer(12)
Token: Keyword(if)
Token: Identifier(i22)
Token: NotEqual(!=)
Token: Integer(0)
Token: Keyword(return)
Token: Integer(4)
Token: Semicolon(;)
Token: RPar(})
```
