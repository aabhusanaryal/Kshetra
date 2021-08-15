// ===========================================================================
// Usage: Parser parser_name;
// 		  Parser.parse(equation_string);
// ===========================================================================

// ===================== How this component works =======================
// The object is first initialized, then the parse member function of the Parser class can be
// called, the parse function then tokenizes the equation from the tokenizer class and then
// changes the tokens into Reverse Polish Notation
// if there is error is in the syntax, it can be checked through the bool value syntaxError
// token_name.syntaxError = true (if there is syntax error)
//=========================================================================
// The equation can be evaluated after calling the parse() method by calling the evaluateRPN()
// method. The method takes in 2 arguments x and y and returns the value after substituting
// them in the valid equation provided
// If the values provided to the equation evaluates to an imaginary number or infinity,
// NaN is returned from the function
// ===========================================================================

#include <parser.hpp>

double Numberify(Token& token)
{
	float number = 0;
	if (token._Type == NUM_LITERAL)
		number = std::stod(token._Text);
	if (token._Text == "pi")
		number = 3.141596;
	if (token._Text == "-pi")
		number = -3.141596;
	return number;
}

std::string Textify(double num)
{
	std::string str;
	str = std::to_string(num);
	return str;
}

//returns true if the given value is negative
//can be used for unknown, numbers and constant

bool isNegative(Token& token)
{
	if (token._Type == UNKNOWN && (token._Text == "-x" || token._Text == "-y"))
		return true;
	else
		return false;
}

// makes the tokens of the provided equations and stores them in the data member token
// the tokens are made from the class Tokenizer

void Parser::tokenify(std::string& equation)
{
	Tokenizer tokenizer;
	tokens = tokenizer.parse(equation);
}

// funciton to raise the respective types of errors
void Parser::raiseSyntaxError()
{
	syntaxError = true;
}

void Parser::raiseNumError()
{
	numError = true;
}

// Any type of error in the token type are handled in the checkSyntaxError function
// this function also checks if the operators are placed correctly or not
// in case an error is found, the syntaxError value is set to true

int Parser::checkSyntaxError()
{
    bool num = false;
    //if no input is given
    if (tokens.empty())
    {
        raiseSyntaxError();
        return 1;
    }
    else
    {
        //error checking for wrong operators
        for (int i = 0; i < tokens.size() - 1; i++)
        {
            if (tokens[i]._Type == OPERATOR && tokens[i + 1]._Type == OPERATOR)
            {
                if (tokens[i]._Text == "(" && tokens[i + 1]._Text == "(")
                    continue;
                else if (tokens[i + 1]._Text == ")" && tokens[i]._Text == ")")
                    continue;
                else if (tokens[i]._Text != ")" && tokens[i + 1]._Text == "(")
                    continue;
                else if (tokens[i]._Text == ")" && tokens[i + 1]._Text != "(")
                    continue;
                else
                {
                    raiseSyntaxError();
                    return 1;
                }
            }
            if (tokens[i]._Type == UNKNOWN || tokens[i]._Type == CONSTANT || tokens[i]._Type == NUM_LITERAL)
            {
                if (tokens[i + 1]._Type != OPERATOR)
                {
                    raiseSyntaxError();
                    return 1;
                }
            }
			if (tokens[i+1]._Type == UNKNOWN || tokens[i+1]._Type == CONSTANT || tokens[i+1]._Type == NUM_LITERAL)
            {
                if (tokens[i]._Type != OPERATOR || tokens[i]._Text == ")")
                {
                    raiseSyntaxError();
                    return 1;
                }
            }
        }

        //start and end check
        if (tokens[0]._Type == OPERATOR && tokens[0]._Text != "(")
        {
            raiseSyntaxError();
            return 1;
        }

        if (tokens[tokens.size() - 1]._Type == OPERATOR && tokens[tokens.size() - 1]._Text != ")")
        {
            raiseSyntaxError();
            return 1;
        }

    }
    //error checking for syntax
	//also checks if the tokens have any UNKNOWN, CONSTANT or NUM_LITERAL type or not
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
        if (current._Type == UNKNOWN || current._Type == CONSTANT || current._Type == NUM_LITERAL)
            num = true;
    }
    if (num == false)
    {
        raiseSyntaxError();
        return 1;
    }

}

// the functions below are used to modify the output vector and the operator stack
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

// returns the precedence of the current operand
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

//returns the associavity of the current operand
std::string Parser::Associavity(Token& token)
{
	if (token._Type == OPERATOR)
		return (token._Text == "^" ? "Right" : "Left");
}


//to make the tokens and convert them to RPN
void Parser::parse(std::string eq)
{
    equation = eq;
    tokenify(equation);
    RPN();
}


// the tokens are added to an output vector in the Reverse Polish Notation
void Parser::RPN()
{

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
		if (current._Type == OPERATOR && current._Text != "(")
		{
			if (current._Text != ")" && !operatorStack.empty() && (Precedence(current) < Precedence(operatorStack[0]) || Precedence(current) == Precedence(operatorStack[0]) && Associavity(current) == "Left"))
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
			while (!operatorStack.empty() && operatorStack[0]._Text != "(")
			{
				MovetoOutput();
				if (operatorStack.empty())
					raiseSyntaxError();
			}

			if (!operatorStack.empty() && operatorStack[0]._Text == "(")
			{
				RemovefromStack();
			}

			if (!operatorStack.empty() && operatorStack[0]._Type == FUNCTION)
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

// this function goes through the output stack
// everytime a token of the type operand is encountered, the 2 value before it are operated
// based on the type of the OPERAND and the result is inserted in the place of the first of 
// them after removing the 3 tokens
// in case of a FUNCTION type token, the value before it is taken and evaluated based on the 
// type of the available function and the result is stored in the place of it
// finally, the result is the only member in the output stack and it is returned

double Parser::evaluateRPN(double x = 0, double y = 0)
{
	numError = false;
	if (syntaxError)
	{
		return 0;
	}

	std::vector<Token> tempout = output;
	int currentIndex = 0;
	Token operand1, operand2, operation, function;

	while (tempout.size() != 1)
	{
		//for the type OPERAND
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
				if (isNegative(operand2))
					operand2._Text = (operand2._Text == "-x") ? Textify(-x) : Textify(-y);
				else
					operand2._Text = (operand2._Text == "x") ? Textify(x) : Textify(y);
				operand2._Type = NUM_LITERAL;
			}

			tempout.erase(tempout.begin() + currentIndex - 2, tempout.begin() + currentIndex + 1);
			result = evaluate(operand1, operand2, operation);

			currentIndex -= 2;
			tempout.insert(tempout.begin() + currentIndex, result);
		}

		//for the type FUNCTION
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

	//if a numError is encountered in the calculation, the operation is halted and NaN is returned
		if (numError)
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
	}

	//for the case that the only member of the output stack is of the type UNKNOWN
	if (tempout.size() == 1 && tempout[0]._Type == UNKNOWN)
	{
		double value;
		if (tempout[0]._Text == "-x" && x != 0)
			return -(x);
		else if (tempout[0]._Text == "-y" && y != 0)
			return(-y);
		else if (tempout[0]._Text == "x")
			return (x);
		else if (tempout[0]._Text == "y")
			return (y);
	}
	return Numberify(tempout[0]);
}


//called on the operation being a binary operation
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
		}
		temp._Text = Textify(Numberify(operand1) / Numberify(operand2));
		break;
	case '^':
		if (Numberify(operand2) != 0 && findFraction(Numberify(operand2)))
		{
			if (Numberify(operand1) <= 0)
			{
				raiseNumError();
			}
			else
				temp._Text = Textify(pow(Numberify(operand1), Numberify(operand2)));
		}
		else if (Numberify(operand1) < 0 && fmod(Numberify(operand2), 2) != 0)
			temp._Text = Textify(-pow(-Numberify(operand1), Numberify(operand2)));
		else if (Numberify(operand1) == 0 && Numberify(operand2) <= 0) // 0^0
			raiseNumError();
		else
			temp._Text = Textify(pow(Numberify(operand1), Numberify(operand2)));

		break;
	}
	return temp;
}

//calculation done when the function is operating on a value
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

//function to find the fractional form of a double value
//it returns true if the numerator of the fraction is odd and the denominator is even
//this is to check if the given power contains the square root or not

bool Parser::findFraction(double input)
{

	double integral = std::floor(input);
	double frac = input - integral;

	const long precision = 100000; // This is the accuracy.

	long gcd_ = gcd(round(frac * precision), precision);

	long denominator = precision / gcd_;
	long numerator = round(frac * precision) / gcd_;

	if ((numerator == 1 && denominator % 2 == 0) || (numerator % 2 != 0 && denominator % 2 == 0))
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