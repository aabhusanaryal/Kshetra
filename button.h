#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>

typedef void (*pointerFn)();

class Button{
public:
    int state;
    bool clicked = false;
    static std::vector<Button*> list;
    std::string path; // Where the texture image is located
    int height, width, posX, posY; // Basic props of the Button
    // Texture [image] to be rendered as the button
    sf::Texture textureUnhovered, textureHover; 
    sf::RectangleShape rectangle; // Rectangle that can be rendered using window.display()
    sf::IntRect rect; // Used to check if mouse is over the button
    bool hoverTex = 0; // Stores if the currently active texture is textureHover
    pointerFn action;

    Button(std::string path,int width,int height,int posX, int posY, int state);

    sf::RectangleShape getElement(); // Returns sf::RectangleShape object
    void setPosition(int x, int y); // Sets the position of button on screen
    void hovered();
    void unhovered();
    void setAction(pointerFn action);
};