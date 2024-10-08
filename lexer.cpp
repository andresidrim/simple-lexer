#include "include/lexer.hpp"
#include <fstream>

// Tokenize the input string into tokens
void Lexer::tokenize(const std::string &input) {
    size_t idx = 0;

    while (idx < input.size()) {
        if (isspace(input[idx])) { // skip whitespace
            idx++;
            continue;
        }
        else if (input[idx] == '#') {
            handleComment(input, idx);
        }
        else if (isdigit(input[idx])) {
            handleNumber(input, idx);
        }
        else if (isalpha(input[idx]) || input[idx] == '_') {
            handleIdentifier(input, idx);
        }
        else {
            handleOperator(input, idx);
        }

        idx++;
    }

    // Print all tokens after tokenization
    for (const auto &token : tokens) {
        printToken(token);
    }
}

void Lexer::handleComment(const std::string &input, size_t &idx) {
    while (idx < input.size() && input[idx] != '\n') { // skips to the end of the line
        idx++;
    }
}

void Lexer::handleNumber(const std::string &input, size_t &idx) {
    std::string num;
    while (isdigit(input[idx]) || input[idx] == '.') {
        num += input[idx++];
    }
    idx--; // move index back to the last processed character

    // if it contains a '.', its identified as a float 
    if (num.find('.') != std::string::npos) {
        tokens.emplace_back(TokenType::Float, num);
    }
    else {
        tokens.emplace_back(TokenType::Integer, num);
    }
}

void Lexer::handleIdentifier(const std::string &input, size_t &idx) {
    // check if the first character is a letter or underscore
    if (!isalpha(input[idx]) && input[idx] != '_') return;

    std::string identifier;

    // append the first valid character to the identifier
    identifier += input[idx++];

    while (isalnum(input[idx]) || input[idx] == '_') {
        identifier += input[idx++];
    }

    idx--; // move index back to the last processed character

    if (identifier == "if" || identifier == "else" || identifier == "while" ||
        identifier == "break" || identifier == "read" || identifier == "write" ||
        identifier == "function" || identifier == "return") {
        tokens.emplace_back(TokenType::Keyword, identifier);
    }
    else {
        tokens.emplace_back(TokenType::Identifier, identifier);
    }
}

void Lexer::handleOperator(const std::string &input, size_t &idx) {
    switch (input[idx]) {
    case '+':
        tokens.emplace_back(TokenType::Addition, "+");
        break;
    case '-':
        tokens.emplace_back(TokenType::Subtraction, "-");
        break;
    case '*':
        // if the next char is a '*', the token identified as a power operator (**)
        if (input[idx + 1] == '*') {
            tokens.emplace_back(TokenType::Power, "**");
            idx++;
        }
        // if not, its a multiplication (*)
        else {
            tokens.emplace_back(TokenType::Multiplication, "*");
        }
        break;
    case '/':
        tokens.emplace_back(TokenType::Division, "/");
        break;
    case '%':
        tokens.emplace_back(TokenType::Modulo, "%");
        break;
    case '<':
        tokens.emplace_back(TokenType::LThan, "<");
        break;
    case '>':
        tokens.emplace_back(TokenType::GThan, ">");
        break;
    case '=':
        tokens.emplace_back(TokenType::Assignment, "=");
        break;
    case '!':
        // if the next character is a '=', the token is identified as not equals operator (!=)
        if (input[idx + 1] == '=') {
            tokens.emplace_back(TokenType::NotEqual, "!=");
            idx++;
        }
        //  if not, its an unknown token
        else {
            tokens.emplace_back(TokenType::Unknown, std::string(1, input[idx]));
        }
        break;
    case '&':
        tokens.emplace_back(TokenType::And, "&");
        break;
    case '|':
        tokens.emplace_back(TokenType::Or, "|");
        break;
    case '(':
        tokens.emplace_back(TokenType::LBrac, "(");
        break;
    case ')':
        tokens.emplace_back(TokenType::RBrac, ")");
        break;
    case '{':
        tokens.emplace_back(TokenType::LPar, "{");
        break;
    case '}':
        tokens.emplace_back(TokenType::RPar, "}");
        break;
    case ';':
        tokens.emplace_back(TokenType::Semicolon, ";");
        break;
    case ',':
        tokens.emplace_back(TokenType::Comma, ",");
        break;
    default:
        // if the token didnt fit any other type, its set as an unknown token by default
        tokens.emplace_back(TokenType::Unknown, std::string(1, input[idx]));
        break;
    }
}

std::string Lexer::getTokenType(const Token &token) {
    std::string typeName;

    switch (token.type) {
    case TokenType::Keyword:
        typeName = "Keyword";
        break;
    case TokenType::Identifier:
        typeName = "Identifier";
        break;
    case TokenType::Integer:
        typeName = "Integer";
        break;
    case TokenType::Float:
        typeName = "Float";
        break;
    case TokenType::Addition:
        typeName = "Addition";
        break;
    case TokenType::Subtraction:
        typeName = "Subtraction";
        break;
    case TokenType::Multiplication:
        typeName = "Multiplication";
        break;
    case TokenType::Division:
        typeName = "Division";
        break;
    case TokenType::Power:
        typeName = "Power";
        break;
    case TokenType::Modulo:
        typeName = "Modulo";
        break;
    case TokenType::LThan:
        typeName = "LThan";
        break;
    case TokenType::GThan:
        typeName = "GThan";
        break;
    case TokenType::NotEqual:
        typeName = "NotEqual";
        break;
    case TokenType::Equal:
        typeName = "Equal";
        break;
    case TokenType::LEqual:
        typeName = "LEqual";
        break;
    case TokenType::GEqual:
        typeName = "GEqual";
        break;
    case TokenType::Assignment:
        typeName = "Assignment";
        break;
    case TokenType::And:
        typeName = "And";
        break;
    case TokenType::Or:
        typeName = "Or";
        break;
    case TokenType::Not:
        typeName = "Not";
        break;
    case TokenType::LBrac:
        typeName = "LBrac";
        break;
    case TokenType::RBrac:
        typeName = "RBrac";
        break;
    case TokenType::LPar:
        typeName = "LPar";
        break;
    case TokenType::RPar:
        typeName = "RPar";
        break;
    case TokenType::Semicolon:
        typeName = "Semicolon";
        break;
    case TokenType::Comma:
        typeName = "Comma";
        break;
    case TokenType::Comment:
        typeName = "Comma";
        break;
    case TokenType::Unknown:
        typeName = "Unknown";
        break;
    }

    return typeName;
}

void Lexer::printToken(const Token &token) {
    std::string typeName;

    // getting the token type as a string
    typeName = getTokenType(token);

    std::cout << "Token: " << typeName << "(" << token.value << ")\n";
}

void Lexer::writeTokensToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    std::string typeName;

    for (const auto& token : tokens) {
        typeName = getTokenType(token);
        outFile << "Token: " << typeName << " (" << token.value << ")\n";
    }

    outFile.close();
    std::cout << "\nTokens successfully written to " << filename << std::endl;
}