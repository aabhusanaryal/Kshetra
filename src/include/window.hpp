#pragma once
#include "SFML/Graphics.hpp"
#include <button.hpp>
#include <slider.hpp>
#include <vector.hpp>
#include <canvas.hpp>
#include <textfield.hpp>

class Window : public sf::RenderWindow{
public:
    int state = 0;
    int mouseX, mouseY;
    int width = 1280;
    int height = 720;
    std::vector<int> legalChars = {'x', 'y', 's', 'i', 'n', 'c', 'o', 's', 't', 'a', 'n', '/', '*', '+', '-', '^', '(', ')', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'p', 'i', ' '}; // Characters that are allowed in a Textfield
// Constructor
    Window(sf::VideoMode video, const sf::String path, int style): sf::RenderWindow(video, path, style){};

// .draw() method overloads
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
    void draw(Vector* v){
        sf::RenderWindow::draw(v->sprite);
    }

// Main Loop
    void mainLoop();
};