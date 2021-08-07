#include "Parser.h"


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

void Parser::tokenify(std::string& equation)
{
	Tokenizer tokenizer;
	tokens = tokenizer.parse(equation);
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


bool isNegative(Token& token)
{
	if (token._Type == UNKNOWN && (token._Text == "-x" || token._Text == "-y"))
		return true;
	return false;
}

std::string Parser::Associavity(Token& token)
{
	if (token._Type == OPERATOR)
		return (token._Text == "^" ? "Right" : "Left");
}

void Parser::RPN()
{
	for (Token current : tokens)
	{
		if (current._Type == NUM_LITERAL || current._Type == CONSTANT || current._Type == UNKNOWN)
		{
			AddtoOutput(current);
		}

		if (current._Type == FUNCTION)
		{
			AddtoStack(current);
		}

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

		if (!operatorStack.empty() && current._Type == OPERATOR && current._Text == ")")
		{
			RemovefromStack();
			while (operatorStack[0]._Text != "(")
			{
				MovetoOutput();
			}

			if (operatorStack[0]._Text == "(")
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
		MovetoOutput();
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
			
			//if(operand1._Type == NUM_LITERAL &&operand2._Type == NUM_LITERAL)
			//else if (operand1._Type == UNKNOWN && operand2._Type == NUM_LITERAL)
			//	result = evaluate(op1, operand2, operation);
			//else if (operand1._Type == NUM_LITERAL && operand2._Type == UNKNOWN)
			//	result = evaluate(operand1, op2, operation);
			//else
			//	result = evaluate(op1, op2, operation);

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
		else if (tempout[0]._Text == "x" || x == 0)
			return (x);
		else
			return (y);
	}
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
		temp._Text = Textify(Numberify(operand1) / Numberify(operand2));
		break;
	case '^':
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