#pragma once
#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"

class Window : public sf::RenderWindow{
public:
    Window(sf::VideoMode video, const sf::String path): sf::RenderWindow(video, path){}
    void draw(Button* btn){
        sf::RenderWindow::draw(btn->rectangle);
    }
};