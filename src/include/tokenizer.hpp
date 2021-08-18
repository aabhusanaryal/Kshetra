#pragma once
#include <string>
#include <vector>

enum TokenType {
    WHITESPACE,
    OPERATOR,
    NUM_LITERAL,
    UNKNOWN,
    FUNCTION,
    CONSTANT
};

static const char *tk[] =
{
    "WHITESPACE",
    "OPERATOR",
    "NUM_LITERAL",
    "UNKNOWN",
    "FUNCTION",
    "CONSTANT"
};


class Token {
public:
    std::string _Text;
    enum TokenType _Type {WHITESPACE};
    bool isNegative = false;
    std::string associavity = "Left";
    int precedence = 0;
};

class Tokenizer
{
    void endToken(Token&, std::vector<Token> &tokens);
public:
    std::vector<Token> parse(const std::string&);
};