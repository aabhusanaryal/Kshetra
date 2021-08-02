#pragma once
#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "vector.hpp"

class Window : public sf::RenderWindow{
public:
    int state = 0;
    int mouseX, mouseY;
    int magicNumber = 69;
    int width = 1250;
    int height = 850;

//HL-> Constructor
    Window(sf::VideoMode video, const sf::String path, int style): sf::RenderWindow(video, path, style){};

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
    void draw(sf::Sprite sprite){
        sf::RenderWindow::draw(sprite);
    }
    void draw(vector* v){
        sf::RenderWindow::draw(v->sprite);
    }

//HL-> Main Loop
    void mainLoop();
};