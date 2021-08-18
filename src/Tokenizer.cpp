// ===========================================================================
// Usage: tokenizer tokenizer_name;
//        tokenizer_name.parse(equation);
// ===========================================================================

// ===================== How this component works =======================
// The object is first initialized, then the parse member function of the tokenizer class can be
// called, the parse function then tokenizes the equation into respective tokens  

// The tokens can hence be made from anywhere by the mentioned method
// In this project, the tokenizer class has been only used from the Parse class while tokenizing
// the equation

// The parse member function returns a std::vector of Token objects
// The token object holds the information of the type of token created like the text in it,
// the type of token and if the token is negative or not

// ===========================================================================



#include<tokenizer.hpp>

std::vector<Token> Tokenizer::parse(const std::string& inProgram)
{
    std::vector<Token> tokens;
    Token currentToken;
    bool negative = false;

    for (char currentChar : inProgram)
    {
        switch (currentChar)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':

            if (negative)
            {
                endToken(currentToken, tokens);

                currentToken._Text.append(1, '-');
                currentToken._Type = NUM_LITERAL;
                currentToken._Text.append(1, currentChar);
                negative = false;
            }

            else if (currentToken._Type == NUM_LITERAL)
                currentToken._Text.append(1, currentChar);

            else 
            {    
                endToken(currentToken, tokens);
                currentToken._Type = NUM_LITERAL;
                currentToken._Text.append(1, currentChar);
            }
            break;

        case'.':
            if (currentToken._Type == NUM_LITERAL)
                currentToken._Text.append(1, currentChar);
            break;

        case'-':
            if (!negative && ((currentToken._Type == OPERATOR && currentToken._Text != ")")|| currentToken._Type == WHITESPACE))
            {
                negative = true;
            }
            else
            {
                negative = false;
                endToken(currentToken, tokens);
                currentToken._Type = OPERATOR;
                currentToken._Text.append(1, currentChar);
                currentToken.precedence = 2;
            }
            break;

        case'+':
            endToken(currentToken, tokens);
            currentToken._Type = OPERATOR;
            currentToken._Text.append(1, currentChar);
            currentToken.precedence = 2;
            break;
        case'*':
        case'/':
            endToken(currentToken, tokens);
            currentToken._Type = OPERATOR;
            currentToken._Text.append(1, currentChar);
            currentToken.precedence = 3;
            break;
        case'^':
            endToken(currentToken, tokens);
            currentToken._Type = OPERATOR;
            currentToken._Text.append(1, currentChar);
            currentToken.associavity = "Right";
            currentToken.precedence = 4;
            break;
        case'(':
        case')':
            endToken(currentToken, tokens);
            currentToken._Type = OPERATOR;
            currentToken._Text.append(1, currentChar);
            break;

        case' ':
            if (negative)
            {
                endToken(currentToken, tokens);
                currentToken._Text.append(1, '-');
                currentToken._Type = OPERATOR;
                negative = false;
            }
            else
            {
                endToken(currentToken, tokens);
                currentToken._Type = WHITESPACE;
            }
            break;

        case'x':
        case'y':
            endToken(currentToken, tokens);
            if (negative)
            {
                currentToken._Text.append(1, '-');
            }
            currentToken._Type = UNKNOWN;
            currentToken._Text.append(1, currentChar);
            break;

         default:
             if (negative)
             {
                 endToken(currentToken,tokens);
                 currentToken._Text.append(1, '-');
                 if (currentToken._Type != FUNCTION)
                 {
                     currentToken._Type = FUNCTION;
                     currentToken._Text.append(1, currentChar);
                 }
                 negative = false;
             }
             else
             {
                 if (currentToken._Type != FUNCTION)
                 {
                     endToken(currentToken, tokens);
                     currentToken._Type = FUNCTION;
                     currentToken._Text.append(1, currentChar);
                 }
                 else if (currentToken._Type == FUNCTION)
                     currentToken._Text.append(1, currentChar);
             }

             if (currentToken._Text == "pi" || currentToken._Text == "-pi")
             {
                 currentToken._Type = CONSTANT;
             }
        }
    }

    endToken(currentToken, tokens);

    return tokens;
}

void Tokenizer::endToken(Token& token, std::vector<Token>& tokens)
{
    if (token._Type != WHITESPACE)
    {
        tokens.push_back(token);
    }
    token._Type = WHITESPACE;
    token._Text.erase();
}