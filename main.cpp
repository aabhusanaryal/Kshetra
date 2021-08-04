#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "window.h"
#include "vector.hpp"
#include "canvas.hpp"
#include "Parser.h"

#define ALL_STATES 69


float coeffX, coeffY, constant;
int windowWidth = 1250;
int windowHeight = 850;
int something = 1;

Window window(sf::VideoMode(windowWidth, windowHeight), "Kshetra", sf::Style::None);

// Functions to be called on button click:
void changeStateTo1(){
    window.state = 1;
};
void changeStateTo0(){
    window.state = 0;
};
void exitProgram(){
    window.close();
};

// Plot fn
double forX(double x,double y){
    return -x;
}

double forY(double x,double y){
    return y;
}

double forX1(double x,double y){
    return pow(x,2*x+1);
}

double forY1(double x,double y){
    return 2*x*y;
}


void changeFunction(){
    if(something == 1){
        canvas::list[0]->reinitialiseVectors(forX1, forY1);
        something = 2;
    }
    else{
        canvas::list[0]->reinitialiseVectors(forX, forY);
        something = 1;
    }
}

// HL-> DELETE LATER: Debugging
void fnToggleGrid(){
    window.showGrid = !window.showGrid;
}
void fnToggleArrows(){
    window.showArrows = !window.showArrows;
}

double fnParserX(double x,double y){
    return coeffX*x + coeffY*y + constant;
}
double fnParserY(double x,double y){
    return x;
}


// HL-> TODO: merge in the vector.cpp and h files. Then, plot graphs based on inputs instead of static graph

int main(){
// Parser stuff
    Parser parser;
    std::string strExpression;
    std::cin>>strExpression;
    parser.tokenify(strExpression);

    coeffX = parser.CoeffX();
    coeffY = parser.CoeffY();
    constant = parser.Constant();


// Initialising Button and Slider components
    Button btn_Standard_Functions("main_Std_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+50, 0);
    Button btn_Custom_Functions("main_Custom_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+170, 0);
    Button btn_Exit("main_Exit", 62, 62, (windowWidth-62)-20, 20, ALL_STATES);
    Button btn_Back("one_Back", 33, 37, 30, (windowHeight-37)-30, 1);
    // State 1 components:
    Button changeFn("one_Plot", 183, 47, 30, 200, 1);
    Slider slider1(90, 100, 1);
    canvas canvas1(window.width-50, window.height+40, fnParserX, fnParserY, 1);
    // HL-> DELETE LATER: Debugging tools 
    Button toggleGrid("one_Back", 33, 37, 50, 300, 1);
    Button toggleArrows("one_Back", 33, 37, 95, 300, 1);
    toggleGrid.setAction(fnToggleGrid);
    toggleArrows.setAction(fnToggleArrows);
    // Assigning functions to be called on button click
    btn_Exit.setAction(exitProgram);
    btn_Standard_Functions.setAction(changeStateTo1);
    btn_Custom_Functions.setAction(changeStateTo1);
    btn_Back.setAction(changeStateTo0);
    changeFn.setAction(changeFunction);

    // window.draw(title);
    window.mainLoop();
}



