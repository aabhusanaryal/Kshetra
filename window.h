#pragma once
#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"

class Window : public sf::RenderWindow{
public:
    int state = 0;
    int mouseX, mouseY;
    int magicNumber = 69;

//HL-> Constructor
    Window(sf::VideoMode video, const sf::String path): sf::RenderWindow(video, path){};

//HL-> .draw() method overloads
    void draw(Button* btn){
        sf::RenderWindow::draw(btn->rectangle);
    }
    void draw(Slider* slider){
        sf::RenderWindow::draw(slider->rectangle);
        sf::RenderWindow::draw(slider->circle);
        // sf::RenderWindow::draw(slider->testRectangle); // Uncomment for debugging
    }
    void draw(sf::RectangleShape rectangle){
        sf::RenderWindow::draw(rectangle);
    }

//HL-> Main Loop
    void mainLoop();
};