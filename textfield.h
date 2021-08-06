#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>

class Textfield{
public:
    int state;
    std::string text = "";
    bool isFocused;
    bool isHovered;
    bool hoverTex = 0;
    bool focusTex = 0;
    static std::vector<Textfield*> list;
    int height, width, posX, posY;
    sf::Texture textureUnhovered, textureHover, textureFocused;
    sf::RectangleShape rectangle;
    sf::IntRect rect;

    Textfield(int width,int height,int posX, int posY, int state);
    void hovered();
    void unhovered();
    void focused();
    void unfocused(); // IK defocused huna parne ho but let that sink in
};