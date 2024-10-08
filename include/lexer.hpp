#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <unordered_map>

enum class TokenType {
    Keyword,
    Identifier,
    Integer,
    Float,
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Power,
    Modulo,
    LThan,
    GThan,
    NotEqual,
    Equal,
    LEqual,
    GEqual,
    Assignment,
    And,
    Or,
    Not,
    LPar,
    RPar,
    LBrac,
    RBrac,
    Semicolon,
    Comma,
    Comment,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string& value) : type(type), value(value) {}
};

class Lexer {
public:
    void tokenize(const std::string& input);
    void writeTokensToFile(const std::string& filename);
private:
    void printToken(const Token& token);
    void handleComment(const std::string& input, size_t& idx);
    void handleNumber(const std::string& input, size_t& idx);
    void handleIdentifier(const std::string& input, size_t& idx);
    void handleOperator(const std::string& input, size_t& idx);
    std::string getTokenType(const Token &token);

    std::vector<Token> tokens;
};

#endif