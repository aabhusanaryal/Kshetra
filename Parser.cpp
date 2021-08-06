#include "Parser.h"

double Parser::Numberify(Token& token)
{
	float number;
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

void Parser::evaluateRPN()
{
	int currentIndex = 0;
	Token operand1, operand2, operation, function;
	while(output.size() != 1)
	{
		if (output[currentIndex]._Type == OPERATOR)
		{
			operand1 = output[currentIndex - 2];
			operand2 = output[currentIndex - 1];
			operation = output[currentIndex];

			output.erase(output.begin() + currentIndex-2 ,output.begin()+currentIndex+1);

			Token result = evaluate(operand1, operand2, operation);
			currentIndex -= 2;
			output.insert(output.begin()+currentIndex, result);
		}

		if (output[currentIndex]._Type == FUNCTION)
		{
			function = output[currentIndex];
			operand1 = output[currentIndex - 1];

			output.erase(output.begin() + currentIndex - 1, output.begin() + currentIndex + 1);

			Token result = evaluate(function, operand1);
			currentIndex -= 1;
			output.insert(output.begin() + currentIndex, result);
		}
		currentIndex += 1;

		for (Token current : output)
		{
			std::cout << current._Text << " ";
		}
		std::cout <<std::endl;
	}
	
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



