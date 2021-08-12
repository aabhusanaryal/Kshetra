#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>
#include <Text.hpp>

typedef void (*pointerFn)();

class Button{
private:
    std::string labelString; // Where the texture image is located
    int height, width, posX, posY; // Basic props of the Button
    sf::Texture textureUnhovered, textureHovered; 
    bool isHovered = 0; // Stores if the currently active texture is textureHover
public:
    const static bool showLabel = 1;
    const static bool hideLabel = 0;
    std::vector<int> state;
    static std::vector<Button*> list;
    Text* label;
    bool clicked = false;
    sf::FloatRect rect; // Used to check if mouse is over the button
    pointerFn action; // Function to be called when the button is clicked
    sf::RectangleShape rectangle; // Rectangle that can be rendered using window.display()

    Button(std::string label, bool showLabel,int width,int height,int posX, int posY, std::vector<int> state);
    void setPosition(int x, int y); // Sets the position of button on screen
    void hovered();
    void unhovered();
    void setAction(pointerFn action);
};
