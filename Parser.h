#pragma once
#include "Tokenizer.h"
#include <string.h>
#include <math.h>
class Parser
{
private:
	std::vector<Token> tokens;
	std::vector<Token> output;
	std::vector<Token> operatorStack;
	double Numberify(Token& token);
	std::string Textify(double num);
	int Precedence(Token& token);
	std::string Associavity(Token& token);
	Token evaluate(Token operand1, Token operand2, Token& operation);
	Token evaluate(Token function, Token operand);
	void AddtoOutput(Token& token);
	void AddtoStack(Token& token);
	void RemovefromStack();
	void MovetoOutput();

public:
	void displayRPN();
	void RPN();
	double evaluateRPN(double x, double y);
	void tokenify(std::string& equation);
};
