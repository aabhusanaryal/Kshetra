#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>

class Slider{
    std::string textureRectPath = "./assets/sliderRect";
    std::string textureCirclePath = "./assets/sliderCircle";
    sf::Texture textureRect, textureCircle, textureCircleClicked;
    int posX, posY; // Coords of the left side of the slider
    int circleX; // Coords of the circle
    int width = 244;
    int height = 4;
    int radius = 27/2;
public:
    std::vector<int> state;
    static std::vector<Slider*> list; // Contains the pointer to all the slider objects
    sf::IntRect rect; // Click detection
    sf::RectangleShape rectangle, testRectangle; // Test rectangle helps visualise the bounds of the slider. Check out the function overload in window.hpp to turn on the testRectangle
    sf::CircleShape circle;
    int progress=0;
    bool sliding=0;
    // Methods
    Slider(int posX, int posY, std::vector<int> state);
    void calculateProgress();
    void clicked();
    void unclicked();
    void slide(float x);
};
