#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "textfield.h"
#include "window.h"
#include "text.h"
#include "vector.hpp"
#include "canvas.hpp"
#include "Parser.h"
#include <math.h>

#define ALL_STATES 69
#define ONE_AND_TWO 420


Parser *parseri, *parserj;

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
// The windowWidth and windowHeight is 1250 and 850 for a FHD monitor,
// and scales likewise for other screen resolutions preserving the 
// aspect ratio
int windowWidth = (1250/1920.f) * sf::VideoMode::getDesktopMode().width;
int windowHeight = (850/1250.f) * windowWidth;
int something = 1;
Text* vector::magnValue;
Text* vector::angleValue;
Text* vector::posValue;

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
    float r = sqrt(pow(x,2) + pow(y,2));
    float phi;
    if(x>=0 && y>=0) //First quad
        phi = atan(y/x);
    else if(x<0 && y>=0) //Second quad
        phi = 3.1415+atan(y/x);
    else if(x<0 && y<0) //Third quad
        phi = 3.1415 + atan(y/x);
    else if(x>=0 && y<0) //Fourth quad
        phi = atan(y/x);
    return (1/r)*cos(phi);
}
double std2Y(double x,double y){
    float r = sqrt(pow(x,2) + pow(y,2));
    float phi;
    if(x>=0 && y>=0) //First quad
        phi = atan(y/x);
    else if(x<0 && y>=0) //Second quad
        phi = 3.1415+atan(y/x);
    else if(x<0 && y<0) //Third quad
        phi = 3.1415 + atan(y/x);
    else if(x>=0 && y<0) //Fourth quad
        phi = atan(y/x);
    return (1/r)*sin(phi);
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
    return parseri->evaluateRPN(x,y);
}
double fnParserY(double x,double y){
    return parserj->evaluateRPN(x,y);
}

void changeFunction(){
// Parser stuff
    delete parseri;
    delete parserj;

    parseri = new Parser();
    parserj = new Parser();

    std::string strExpressioni, strExpressionj;
    strExpressioni = Textfield::list[0]->text;
    strExpressionj = Textfield::list[1]->text;

    parseri->tokenify(strExpressioni);
    parserj->tokenify(strExpressionj);

    parseri->RPN();
    parserj->RPN();
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
    Button btn_Back("one_Back", 33, 37, 22, 777, ALL_STATES);
    

    // State 1 components:
    Button btn_Plot("one_Plot", 183, 47, 175, 495, 1);
    Slider slider1(698, 803, ONE_AND_TWO);
    Textfield fx("Fx",201, 54, 165, 345, 1);
    Textfield fy("Fy",201, 54, 165, 418, 1);
    canvas canvas1(window.width-50, window.height+40, forX, forY, ONE_AND_TWO);

    Text* magnitude=new Text("Magnitude:",18,131,662,1);
    Text* angle=new Text("Angle:",18,131,689,1);
    Text* position=new Text("Position:",18,131,716,1);
    Text* function=new Text("Enter Function",36,131,290,1,1);
    Text* details=new Text("Details:",36,131,620,1,1);
    
    vector::magnValue=new Text("NA",18,225,662,1);
    vector::angleValue=new Text("NA",18,185,689,1);
    vector::posValue=new Text("NA",18,205,716,1);



    // Text text1("Hello World", 20, 100, 100, ALL_STATES);
    // Text text2("Aloha", 50, 100, 200, ALL_STATES);
// ============================================================
// HL-> DELETE LATER: Debugging tools 
    //Button toggleGrid("one_Back", 33, 37, 50, 700, 1);
    //Button toggleArrows("one_Back", 33, 37, 95, 700, 1);
    //toggleGrid.setAction(fnToggleGrid);
    //toggleArrows.setAction(fnToggleArrows);
// ============================================================

    // State 2 components
    Button btnPrevious("two_Arrow_Left", 36, 80, 44, 385, 2);
    Button btnNext("two_Arrow_Right", 36, 80, window.width-80, 385, 2);
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



