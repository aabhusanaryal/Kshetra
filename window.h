#pragma once
#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "vector.hpp"
#include "canvas.hpp"
#include "textfield.h"

class Window : public sf::RenderWindow{
public:
    static std::vector<std::vector<doublePointerFn>> stdFunctions;
    static int functionIndex;
    int state = 1;
    int mouseX, mouseY;
    int magicNumber = 69;
    int oneAndTwo = 420;
    int width = 1250;
    int height = 850;
// HL-> DELETE LATER: Debiugging
    bool showGrid = true;
    bool showArrows = true;
//HL-> Constructor
    Window(sf::VideoMode video, const sf::String path, int style): sf::RenderWindow(video, path, style){};

//HL-> .draw() method overloads
    void draw(Button* btn){
        sf::RenderWindow::draw(btn->rectangle);
    }
    void draw(Textfield* textfield){
        sf::RenderWindow::draw(textfield->rectangle);
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
    void draw(sf::Text text){
        sf::RenderWindow::draw(text);
    }
    void draw(vector* v){
        sf::RenderWindow::draw(v->sprite);
    }

//HL-> Main Loop
    void mainLoop();
};