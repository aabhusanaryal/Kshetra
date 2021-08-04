/*
make an object of class parser for each equations
parser.tokenify() makes the tokens of the equations
parser.coeffX and parser.Coeffy returns the coefficient of xy terms in the equations
DISCLAIMER: THIS IS VERY KAAM CHALAU PARSER AND ONLY HANDLES ax+by
*/


#pragma once
#include "Tokenizer.h"

class Parser
{
	std::vector<Token> tokens;
public:
	double Numberify(Token& token);
	double CoeffX();
	double CoeffY();
	double Constant();
	void tokenify(std::string& equation);
};
