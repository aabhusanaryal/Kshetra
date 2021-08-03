#pragma once
#include "Tokenizer.h"

class Parser
{
	std::vector<Token> tokens;
public:
	double Numberify(Token& token);
	double CoeffX();
	double CoeffY();
	void tokenify(std::string& equation);
};
