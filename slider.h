#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Slider{
public:
    std::string textureRectPath = "./assets/sliderRect";
    std::string textureCirclePath = "./assets/sliderCircle";
    sf::RectangleShape rectangle, testRectangle;
    sf::CircleShape circle;
    sf::Texture textureRect, textureCircle, textureCircleClicked;
    sf::IntRect rect; // Click detection
    int posX, posY; // Coords of the left side of the slider
    int circleX; // Coords of the circle
    int progress;
    // Methods
    Slider(int posX, int posY);
    void calculateProgress();
    void draw(sf::RenderWindow &window);
    void clicked();
    void unclicked();
};
