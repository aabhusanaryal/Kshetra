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