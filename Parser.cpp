#include "Parser.h"

double Parser::Numberify(Token& token)
{
	int number = std::stoi(token.returnTokenValue());
	return number;
}

void Parser::tokenify(std::string& equation)
{
	Tokenizer tokenizer;
	tokens = tokenizer.parse(equation);
}

double Parser::CoeffX()
{
	int length = 0;
	for (Token current : tokens)
		length += 1;

	int pos = 0;
	for (Token current : tokens)
	{
		if (current._Text != "x")
			pos += 1;
		else
			break;
	}

	if (pos == length)
		return 0;
	else if (pos == 0 || (tokens[pos - 1].returnTokenType() == "OPERATOR" && tokens[pos - 1].returnTokenValue() == "+"))
		return 1;
	else if (tokens[pos - 1].returnTokenType() == "OPERATOR" && tokens[pos - 1].returnTokenValue() == "-")
		return -1;
	else if (pos == 1)
		return Numberify(tokens[pos - 1]);
	else if (tokens[pos - 2].returnTokenValue() == "+" && tokens[pos - 1].returnTokenType() == "NUM_LITERAL")
		return Numberify(tokens[pos - 1]);
	else
		return -Numberify(tokens[pos - 1]);
}

double Parser::CoeffY()
{

	int length = 0;
	for (Token current : tokens)
		length += 1;

	int pos = 0;
	for (Token current : tokens)
	{
		if (current._Text != "y")
			pos += 1;
		else
			break;
	}
	if (pos == length)
		return 0;
	else if (pos == 0 || (tokens[pos - 1].returnTokenType() == "OPERATOR" && tokens[pos - 1].returnTokenValue() == "+"))
		return 1;
	else if (tokens[pos - 1].returnTokenType() == "OPERATOR" && tokens[pos - 1].returnTokenValue() == "-")
		return -1;
	else if (pos == 1)
		return Numberify(tokens[pos - 1]);
	else if (tokens[pos - 2].returnTokenValue() == "+" && tokens[pos - 1].returnTokenType() == "NUM_LITERAL")
		return Numberify(tokens[pos - 1]);
	else
		return -Numberify(tokens[pos - 1]);
}

double Parser::Constant()
{
	int length = 0;
	for (Token current : tokens)
		length += 1;

	//case equation = 69
	if (length == 1 && tokens[0]._Type == NUM_LITERAL)
		return Numberify(tokens[0]);
	//case equation = -69
	if (length == 2 && tokens[1]._Type == NUM_LITERAL && tokens[0]._Text == "-")
		return -Numberify(tokens[1]);

	int pos = 0;
	bool PossibleConstant = false;

	//search for constants
	for (Token current : tokens)
	{
		PossibleConstant = false;
		if (current._Type == NUM_LITERAL)
			PossibleConstant = true;
		if (PossibleConstant)
		{
			//case ax+b and ax-b
			if (pos == length-1)
				return (tokens[pos - 1]._Text == "-" ? -Numberify(tokens[pos]) : Numberify(tokens[pos]));

			//case b+ax and -b+ax
			else if (tokens[pos + 1]._Type == OPERATOR && (tokens[pos + 1]._Text == "+" || tokens[pos + 1]._Text == "-"))
				return (tokens[pos - 1]._Text == "-" ? -Numberify(tokens[pos]) : Numberify(tokens[pos]));
		}
		pos += 1;
	}
	//none of the conditions is satisfied
	return 0;
}