#pragma once
#include "Tokenizer.h"
#include <stack>

class Parser
{
	std::vector<Token> tokens;
	std::vector<Token> output;
	std::vector<Token> operatorStack;

public:
	double Numberify(Token& token);
	std::string Textify(double num);
	int Precedence(Token& token);
	std::string Associavity(Token& token);

	void displayRPN();
	void AddtoOutput(Token& token);
	void AddtoStack(Token& token);
	void RemovefromStack();
	void MovetoOutput();
	void RPN();
	void evaluateRPN();
	Token evaluate(Token operand1, Token operand2, Token& operation);
	Token evaluate(Token function, Token operand);


	void tokenify(std::string& equation);
};
