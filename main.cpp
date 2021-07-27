#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "window.h"
#define ALL_STATES 69

int windowWidth = 1250;
int windowHeight = 850;

Window window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");

void changeStateTo1(){
    window.state = 1;
};
void changeStateTo0(){
    window.state = 0;
};
void exitProgram(){
    window.close();
};

int main(){

    Button btn_Standard_Functions("main_Std_Functions", 311, 80, (windowWidth-298)/2, (windowHeight-70)/2+50, 0);
    Button btn_Custom_Functions("main_Custom_Functions", 311, 80, (windowWidth-298)/2, (windowHeight-70)/2+170, 0);
    Button btn_Exit("main_Exit", 62, 62, (windowWidth-62)-20, 20, ALL_STATES);
    Button btn_Back("one_Back", 33, 37, 30, (windowHeight-37)-30, 1);
    

    Slider slider1(20, 20, 0);

    btn_Exit.setAction(exitProgram);
    btn_Standard_Functions.setAction(changeStateTo1);
    btn_Custom_Functions.setAction(changeStateTo1);
    btn_Back.setAction(changeStateTo0);

    // Slider slider1((windowWidth-298)/2+10, (windowHeight-70)/2+80, ALL_STATES);
    // Slider slider2(300, 500, 1);

    // window.draw(title);
    window.mainLoop();
}



