#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>

class Slider{
public:
    static std::vector<Slider*> list; // Contains the pointer to all the slider objects
    std::string textureRectPath = "./assets/sliderRect";
    std::string textureCirclePath = "./assets/sliderCircle";
    sf::RectangleShape rectangle, testRectangle;
    sf::CircleShape circle;
    sf::Texture textureRect, textureCircle, textureCircleClicked;
    sf::IntRect rect; // Click detection
    int posX, posY; // Coords of the left side of the slider
    int circleX; // Coords of the circle
    int progress=0;
    bool sliding=0;
    int state;
    // Methods
    Slider(int posX, int posY, int state);
    void calculateProgress();
    void draw(sf::RenderWindow &window);
    void clicked();
    void unclicked();
    void slide(float x);
};
