#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Grid.hpp"

class Button{
public:
    std::string path; // Where the image is located
    int height, width, posX, posY;

    Button(std::string path,int width,int height,int posX, int posY){
        this->path = path;
        this->width = width;
        this->height = height;
        this->posX = posX;
        this->posY = posY;
    };

    sf::RectangleShape getElement();
};
