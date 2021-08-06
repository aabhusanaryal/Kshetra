#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "textfield.h"
#include "window.h"
#include "text.h"
#include "vector.hpp"
#include "canvas.hpp"
#include "Parser.h"


#define ALL_STATES 69
#define ONE_AND_TWO 420

// ============ States ============
// 0. Main Menu                   ||
// 1. Custom Functions           ||
// 2. Standard Functions        ||
// =========================== ||

std::vector<Text*> Text::list;
std::vector<std::vector<doublePointerFn>> Window::stdFunctions;
int Window::functionIndex = 0;

float coeffXi=0, coeffYi=-1, constanti=0;
float coeffXj=1, coeffYj=0, constantj=0;
int windowWidth = 1250;
int windowHeight = 850;
int something = 1;

Window window(sf::VideoMode(windowWidth, windowHeight), "Kshetra", sf::Style::None);

//=======================================

// Standard Functions
double std1X(double x,double y){
    return -y;
}
double std1Y(double x,double y){
    return x;
}

double std2X(double x,double y){
    return x;
}
double std2Y(double x,double y){
    return y;
}

double std3X(double x,double y){
    return -x;
}
double std3Y(double x,double y){
    return -y;
}

double std4X(double x,double y){
    return x;
}
double std4Y(double x,double y){
    return x;
}

//=======================================

// Plot fn
double forX(double x,double y){
    return 0;
}

double forY(double x,double y){
    return 0;
}


// Functions to be called on button click:
void changeStateTo2(){
    window.state = 2;
};
void changeStateTo1(){
    window.state = 1;
};
void changeStateTo0(){
    window.state = 0;
};
void exitProgram(){
    window.close();
};
void previousFn(){
    if(Window::functionIndex == 0){
        Window::functionIndex = Window::stdFunctions.size()-1;
    }
    else{
        Window::functionIndex -= 1;
    }
    int i = Window::functionIndex;
    canvas::list[0]->reinitialiseVectors(Window::stdFunctions[i][0], Window::stdFunctions[i][1]);
};



void nextFn(){
    if(Window::functionIndex == Window::stdFunctions.size()-1){
        Window::functionIndex = 0;
    }
    else{
        Window::functionIndex += 1;
    }
    int i = Window::functionIndex;
    canvas::list[0]->reinitialiseVectors(Window::stdFunctions[i][0], Window::stdFunctions[i][1]);
};


// HL-> DELETE LATER: Debugging
void fnToggleGrid(){
    window.showGrid = !window.showGrid;
}
void fnToggleArrows(){
    window.showArrows = !window.showArrows;
}

double fnParserX(double x,double y){
    return coeffXi*x + coeffYi*y + constanti;
}
double fnParserY(double x,double y){
    return coeffXj*x + coeffYj*y + constantj;
}

void changeFunction(){
// Parser stuff
    Parser parseri, parserj;
    std::string strExpressioni, strExpressionj;
    strExpressioni = Textfield::list[0]->text;
    strExpressionj = Textfield::list[1]->text;
    parseri.tokenify(strExpressioni);
    parserj.tokenify(strExpressionj);

    coeffXi = parseri.CoeffX();
    coeffYi = parseri.CoeffY();
    constanti = parseri.Constant();

    coeffXj = parserj.CoeffX();
    coeffYj = parserj.CoeffY();
    constantj = parserj.Constant();
    canvas::list[0]->reinitialiseVectors(fnParserX, fnParserY);
}

// HL-> TODO: merge in the vector.cpp and h files. Then, plot graphs based on inputs instead of static graph

int main(){


    std::vector<doublePointerFn> fnPair1 = {std1X, std1Y};
    std::vector<doublePointerFn> fnPair2 = {std2X, std2Y};
    std::vector<doublePointerFn> fnPair3 = {std3X, std3Y};
    std::vector<doublePointerFn> fnPair4 = {std4X, std4Y};
    window.stdFunctions = {fnPair1, fnPair2, fnPair3, fnPair4};

// Initialising Button and Slider components
    Button btn_Standard_Functions("main_Std_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+50, 0);
    Button btn_Custom_Functions("main_Custom_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+170, 0);
    Button btn_Exit("main_Exit", 62, 62, (windowWidth-62)-20, 20, ALL_STATES);
    Button btn_Back("one_Back", 33, 37, 30, (windowHeight-37)-30, ALL_STATES);
    

    // State 1 components:
    Button btn_Plot("one_Plot", 183, 47, 108, 250, 1);
    Slider slider1(90, 350, ONE_AND_TWO);
    Textfield fx("Fx",201, 54, 100, 100, 1);
    Textfield fy("Fy",201, 54, 100, 170, 1);
    canvas canvas1(window.width-50, window.height+40, fnParserX, fnParserY, ONE_AND_TWO);
    

    // Text text1("Hello World", 20, 100, 100, ALL_STATES);
    // Text text2("Aloha", 50, 100, 200, ALL_STATES);
// ============================================================
// HL-> DELETE LATER: Debugging tools 
    Button toggleGrid("one_Back", 33, 37, 50, 700, 1);
    Button toggleArrows("one_Back", 33, 37, 95, 700, 1);
    toggleGrid.setAction(fnToggleGrid);
    toggleArrows.setAction(fnToggleArrows);
// ============================================================

    // State 2 components
    Button btnPrevious("two_Previous", 33, 37, 100, 300, 2);
    Button btnNext("two_Next", 33, 37, 150, 300, 2);
    // Assigning functions to be called on button click
    btn_Exit.setAction(exitProgram);
    btn_Standard_Functions.setAction(changeStateTo2);
    btn_Custom_Functions.setAction(changeStateTo1);
    btn_Back.setAction(changeStateTo0);
    btn_Plot.setAction(changeFunction);
    btnPrevious.setAction(previousFn);
    btnNext.setAction(nextFn);

    window.mainLoop();
}



