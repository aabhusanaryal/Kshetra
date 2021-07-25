#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "window.h"
#define ALL_STATES 69

int windowWidth = 1080;
int windowHeight = 720;


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

    sf::RectangleShape title(sf::Vector2f(493, 186));
    sf::Texture titleText;
    titleText.loadFromFile("./assets/main_Title.png");
    title.setTexture(&titleText);
    title.setPosition((windowWidth - 493)/2, 150); 

    Button btn_Standard_Functions("main_Std_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+50, 0);
    Button btn_Custom_Functions("main_Custom_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+150, 0);
    Button btn_Exit("main_Exit", 62, 62, (windowWidth-60-20), 30, ALL_STATES);
    Button btn_Back("one_Back", 33, 37, 20, windowHeight-62-20, 1);

    btn_Exit.setAction(exitProgram);
    btn_Standard_Functions.setAction(changeStateTo1);
    btn_Custom_Functions.setAction(changeStateTo1);
    btn_Back.setAction(changeStateTo0);


    Slider slider1(400, 200, 1);
    Slider slider2(300, 500, 1);

    window.draw(title);
    window.mainLoop();
}

