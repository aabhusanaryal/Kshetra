#include "Parser.h"
#include <limits>


double Parser::Numberify(Token& token)
{
	float number = 0;
	if (token._Type == NUM_LITERAL)
		number = std::stod(token.returnTokenValue());
	if (token._Text == "pi")
		number = 3.141596;
	if (token._Text == "-pi")
		number = -3.141596;
	return number;
}

std::string Parser::Textify(double num)
{
	std::string str;
	str = std::to_string(num);
	return str;
}


bool Parser::isNegative(Token& token)
{
	if (token._Type == UNKNOWN && (token._Text == "-x" || token._Text == "-y"))
		return true;
	else
		return false;

	if (token._Type == NUM_LITERAL && Numberify(token) < 0)
		return true;
	else
		return false;
}

void Parser::tokenify(std::string& equation)
{
	Tokenizer tokenizer;
	tokens = tokenizer.parse(equation);
}


void Parser::raiseSyntaxError()
{
	syntaxError = true;
}

void Parser::raiseNumError()
{
	numError = true;
}

int Parser::checkSyntaxError()
{

	//if no input is given
	if (tokens.empty())
	{
		raiseSyntaxError();
		std::cout << "Error: No input\n";
		return 1;
	}
	else
	{
		//error checking for wrong operators
		for (int i = 0; i < tokens.size() - 1; i++)
		{
			if (tokens[i]._Type == OPERATOR && tokens[i + 1]._Type == OPERATOR)
			{
				if (tokens[i]._Text == "(" && (tokens[i + 1]._Text == "(" || tokens[i]._Text == ")"))
					continue;
				else if (tokens[i + 1]._Text == ")" && (tokens[i]._Text == "(" || tokens[i]._Text == ")"))
					continue;
				else if (tokens[i]._Text != ")" && tokens[i + 1]._Text == "(")
					continue;
				else if (tokens[i]._Text == ")" && tokens[i + 1]._Text != "(")
					continue;
				else
				{
					raiseSyntaxError();
					std::cout << "Error: " << tokens[i]._Text << tokens[i + 1]._Text << std::endl;
				}
			}
		}

		//start and end check
		if (tokens[0]._Type == OPERATOR && tokens[0]._Text != "(")
		{
			raiseSyntaxError();
			std::cout << "Error4:" << tokens[0]._Text << tokens[1]._Text << std::endl;

		}

		if (tokens[tokens.size() - 1]._Type == OPERATOR && tokens[tokens.size() - 1]._Text != ")")
		{
			std::cout << "Error5:" << tokens[tokens.size() - 2]._Text << tokens[tokens.size() - 1]._Text << std::endl;
			raiseSyntaxError();
		}
	}

	//error checking for syntax
	for (Token current : tokens)
	{
		int count = 0;
		if (current._Type == FUNCTION)
		{
			for (int i = 0; i < functions.size(); i++)
			{
				if (current._Text != functions[i])
					count++;
			}
			if (count == functions.size())
				raiseSyntaxError();
		}
	}
}

void Parser::AddtoOutput(Token& token)
{
	output.push_back(token);
}

void Parser::AddtoStack(Token& token)
{
	operatorStack.insert(operatorStack.begin(), token);
}

void Parser::RemovefromStack()
{
	operatorStack.erase(operatorStack.begin());
}

void Parser::MovetoOutput()
{
	AddtoOutput(operatorStack[0]);
	RemovefromStack();
}


int Parser::Precedence(Token& token)
{
	if (token._Type == OPERATOR)
	{
		if (token._Text == "+" || token._Text == "-")
			return 2;
		if (token._Text == "*" || token._Text == "/")
			return 3;
		if (token._Text == "^")
			return 4;
	}
}


std::string Parser::Associavity(Token& token)
{
	if (token._Type == OPERATOR)
		return (token._Text == "^" ? "Right" : "Left");
}

void Parser::RPN()
{
	output.clear();
	operatorStack.clear();
	checkSyntaxError();
	for (Token current : tokens)
	{
		//push numbers to output stack
		if (current._Type == NUM_LITERAL || current._Type == CONSTANT || current._Type == UNKNOWN)
		{
			AddtoOutput(current);
		}
		//push functions to operatorstack
		if (current._Type == FUNCTION)
		{
			AddtoStack(current);
		}

		//If the operator type is other than a left paranthesis
		if (current._Type == OPERATOR && current._Text !="(")
		{
			if ( current._Text !=")" && !operatorStack.empty() && (Precedence(current) < Precedence(operatorStack[0]) || Precedence(current) == Precedence(operatorStack[0]) && Associavity(current) == "Left"))
			{
				MovetoOutput();
				AddtoStack(current);
			}
			else
			{
				AddtoStack(current);
			}
		}

		if (current._Type == OPERATOR && current._Text == "(")
		{
			AddtoStack(current);
		}

		if (current._Type == OPERATOR && current._Text == ")")
		{
			RemovefromStack();
			while (!operatorStack.empty() &&operatorStack[0]._Text != "(")
			{
				MovetoOutput();
				if (operatorStack.empty())
					raiseSyntaxError();
			}

			if (!operatorStack.empty() && operatorStack[0]._Text == "(")
			{
				RemovefromStack();
			}

			if ( !operatorStack.empty() && operatorStack[0]._Type == FUNCTION)
			{
				MovetoOutput();
			}
		}
	}

	while (!operatorStack.empty())
	{
		if (operatorStack[0]._Text == "(")
			raiseSyntaxError();
		MovetoOutput();
	}

	if (output.empty())
	{
		raiseSyntaxError();
	}
}

void Parser::displayRPN()
{
	for (Token current : output)
	{
		std::cout << current._Text << " ";
	}
}

double Parser::evaluateRPN(double x=0, double y=0)
{
	numError = false;
	if (syntaxError)
	{
		std::cout << "There is an error in the equation, can't parse it" << std::endl;
		return 0;
	}

	std::vector<Token> tempout = output;
	int currentIndex = 0;
	Token operand1, operand2, operation, function;

	while(tempout.size() != 1)
	{
		if (tempout[currentIndex]._Type == OPERATOR)
		{
			operand1 = tempout[currentIndex - 2];
			operand2 = tempout[currentIndex - 1];
			operation = tempout[currentIndex];
			Token result;

			if (operand1._Type == UNKNOWN)
			{
				if (isNegative(operand1))
					operand1._Text = (operand1._Text == "-x") ? Textify(-x) : Textify(-y);
				else
					operand1._Text = (operand1._Text == "x") ? Textify(x) : Textify(y);
				operand1._Type = NUM_LITERAL;
			}

			if (operand2._Type == UNKNOWN)
			{
				if(isNegative(operand2))
					operand2._Text = (operand2._Text == "-x") ? Textify(-x) : Textify(-y);
				else
					operand2._Text = (operand2._Text == "x") ? Textify(x) : Textify(y);
				operand2._Type = NUM_LITERAL;
			}

			tempout.erase(tempout.begin() + currentIndex-2 ,tempout.begin()+currentIndex+1);
			result = evaluate(operand1, operand2, operation);
			
			currentIndex -= 2;
			tempout.insert(tempout.begin()+currentIndex, result);
		}

		if (tempout[currentIndex]._Type == FUNCTION)
		{
			Token result;
			function = tempout[currentIndex];
			operand1 = tempout[currentIndex - 1];

			if (operand1._Type == UNKNOWN)
			{
				if (isNegative(operand1))
					operand1._Text = (operand1._Text == "-x") ? Textify(-x) : Textify(-y);
				else
					operand1._Text = (operand1._Text == "x") ? Textify(x) : Textify(y);
				operand1._Type = NUM_LITERAL;
			}

			tempout.erase(tempout.begin() + currentIndex - 1, tempout.begin() + currentIndex + 1);
			
			result = evaluate(function, operand1);

			currentIndex -= 1;
			tempout.insert(tempout.begin() + currentIndex, result);
		}
		currentIndex += 1;

		//check the steps of parcing from here
		//for (Token current : tempout)
		//{
		//	std::cout << current._Text<<" ";
		//}
		//std::cout<<std::endl;
	}

	if (tempout.size() == 1 && tempout[0]._Type == UNKNOWN)
	{
		double value;
		if (tempout[0]._Text == "-x" && x !=0)
			return -(x);
		else if (tempout[0]._Text == "-y" && y != 0)
			return(-y);
		else if (tempout[0]._Text == "x")
			return (x);
		else if (tempout[0]._Text == "y")
			return (y);
	}

	if (numError)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

		//std::cout << tempout[0]._Text << std::endl;
	return Numberify(tempout[0]);
}

Token Parser::evaluate(Token operand1, Token operand2, Token& operation)
{
	Token temp;
	temp._Type = NUM_LITERAL;
	char opr[2];
	strcpy_s(opr, operation._Text.c_str());
	char op = opr[0];

	switch (op)
	{
	case '+':
		temp._Text = Textify(Numberify(operand1) + Numberify(operand2));
		break;
	case '-':
		temp._Text = Textify(Numberify(operand1) - Numberify(operand2));
		break;
	case '*':
		temp._Text = Textify(Numberify(operand1) * Numberify(operand2));
		break;
	case '/':
		if (Numberify(operand2) == 0)
		{
			raiseNumError();
			temp._Text = "0";
			return temp;
		}
		temp._Text = Textify(Numberify(operand1) / Numberify(operand2));
		break;

	case '^':
		if (findFraction(Numberify(operand2)))
		{
			if (Numberify(operand1) < 0)
			{
				std::cout << "Invalid" << std::endl;
				raiseNumError();
			}
			else
				temp._Text = Textify(pow(Numberify(operand1), Numberify(operand2)));
		}
		else if (Numberify(operand1) < 0)
			temp._Text = Textify(-pow(-Numberify(operand1), Numberify(operand2)));
		else
			temp._Text = Textify(pow(Numberify(operand1), Numberify(operand2)));

		break;
	}
	return temp;
}

Token Parser::evaluate(Token function, Token operand)
{
	Token temp;
	temp._Type = NUM_LITERAL;
	
	if (function._Text == "sin")
		temp._Text = Textify(sin(Numberify(operand)));
	if (function._Text == "-sin")
		temp._Text = Textify(-sin(Numberify(operand)));
	if (function._Text == "cos")
		temp._Text = Textify(cos(Numberify(operand)));
	if (function._Text == "-cos")
		temp._Text = Textify(-cos(Numberify(operand)));
	if (function._Text == "tan")
		temp._Text = Textify(tan(Numberify(operand)));
	if (function._Text == "-tan")
		temp._Text = Textify(-tan(Numberify(operand)));
	return temp;
}

bool Parser::findFraction(double input)
{

		double integral = std::floor(input);
		double frac = input - integral;

		const long precision = 100000; // This is the accuracy.

		long gcd_ = gcd(round(frac * precision), precision);

		long denominator = precision / gcd_;
		long numerator = round(frac * precision) / gcd_;
		//std::cout << numerator << "/" << denominator << std::endl;
		if ((numerator == 1 && denominator % 2 == 0) || (numerator %2 != 0 && denominator % 2==0))
			return true;
		return false;
}


long Parser::gcd(long a, long b)
{
	if (a == 0)
		return b;
	else if (b == 0)
		return a;

	if (a < b)
		return gcd(a, b % a);
	else
		return gcd(b, a % b);
}