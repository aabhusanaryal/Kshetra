#pragma once
#include "Tokenizer.h"
#include <math.h>
#include <string.h>

class Parser
{
private:
	std::vector<Token> tokens;
	std::vector<Token> output;
	std::vector<Token> operatorStack;
	std::vector<std::string> functions = { "sin", "cos", "tan","-sin", "-cos", "-tan"};
	std::string equation;

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
	void raiseSyntaxError();
	void raiseNumError();
	bool isNegative(Token& token);
	int checkSyntaxError();
	void tokenify(std::string& equation);
	void RPN();
	bool findFraction(double input);
	long gcd(long a, long b);


public:
	static std::vector<Parser*> list;
	Parser()
	{
		list.push_back(this);
	}

	void parse(std::string eq)
	{
		equation = eq;
		tokenify(equation);
		RPN();
	}
	void displayRPN();
	bool syntaxError;
	bool numError;
	double evaluateRPN(double x, double y);
};
