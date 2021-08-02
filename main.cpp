#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "window.h"
#include "vector.hpp"
#include "canvas.hpp"

#define ALL_STATES 69

int windowWidth = 1250;
int windowHeight = 850;

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
    return x;
}

double forY(double x,double y){
    return y;
}


// HL-> TODO: merge in the vector.cpp and h files. Then, plot graphs based on inputs instead of static graph

int main(){
    // Initialising Button and Slider components
    Button btn_Standard_Functions("main_Std_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+50, 0);
    Button btn_Custom_Functions("main_Custom_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+170, 0);
    Button btn_Exit("main_Exit", 62, 62, (windowWidth-62)-20, 20, ALL_STATES);
    Button btn_Back("one_Back", 33, 37, 30, (windowHeight-37)-30, 1);
    

    Slider slider1(90, 50, 1);

    canvas canvas1(window.width-50, window.height+40, forX, forY, 1);

    // Assigning functions to be called on button click
    btn_Exit.setAction(exitProgram);
    btn_Standard_Functions.setAction(changeStateTo1);
    btn_Custom_Functions.setAction(changeStateTo1);
    btn_Back.setAction(changeStateTo0);


    // window.draw(title);
    window.mainLoop();
}



