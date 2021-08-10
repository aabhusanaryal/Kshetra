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
            }
            break;

        case'+':
        case'*':
        case'/':
        case'^':
        case'(':
        case')':
            endToken(currentToken, tokens);
            currentToken._Type = OPERATOR;
            currentToken._Text.append(1, currentChar);
            break;

        case' ':
            endToken(currentToken, tokens);
            currentToken._Type = WHITESPACE;
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
void Token::print() const { std::cout << "Token(" << tk[_Type] << " , " << _Text << std::endl; }

std::string Token::returnTokenType()
{
    return tk[_Type];
}

std::string Token::returnTokenValue()
{
    return _Text;
}