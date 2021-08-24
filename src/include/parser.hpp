#pragma once
#include <math.h>
#include <string.h>
#include <tokenizer.hpp>
#include <limits>
#include<cmath>

class Parser : private Tokenizer
{
private:
//Data members -equation -Tokens -Outputstack -Operatorstack - Available functions
    std::string equation;
    std::vector<Token> tokens;
    std::vector<Token> output;
    std::vector<Token> operatorStack;
    const std::vector<std::string> functions = { "sin", "cos", "tan","-sin", "-cos", "-tan"};
    
    // numError is true for any mathematical errors during calculation
    // example: division by zero or the square root of a negative number
    bool numError;

public:
    // syntaxError is true for any error in the equations 
    bool syntaxError;

private:
//functions for operation of the parser but are not only based for the class
    double Numberify(Token& token);
    std::string Textify(double num);
    bool isNegative(Token& token);
    bool findFraction(double input);
    long gcd(long a, long b);

private:
//essential parsing functions
    void RPN();
    inline void AddtoOutput(Token&);
    inline void AddtoStack(Token&);
    inline void RemovefromStack();
    inline void MovetoOutput();

private:
//functions to evaluate the notation
    Token evaluate(Token, Token, Token&);
    Token evaluate(Token, Token);

private:
//error handling functions
    inline void raiseSyntaxError();
    inline void raiseNumError();
    int checkSyntaxError();
    

public:
    double evaluateRPN(double, double);
    void parse(std::string);
};