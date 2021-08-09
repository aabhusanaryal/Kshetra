#pragma once

#include <string>
#include <vector>
#include <iostream>

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
	void print() const;
	std::string returnTokenType();
	std::string returnTokenValue();
	bool isNegative = false;
};

class Tokenizer
{
public:
	std::vector<Token> parse(const std::string& inProgram);
	void endToken(Token &token, std::vector<Token>& tokens);
};