#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>
#include "text.h"

class Textfield{
public:
    static std::vector<Textfield*> list;
    std::vector<int> state;
    std::string text = "";
    std::string label;
    Text* name;
    Text* content;
    int contentPosX;
    int contentPosY;
    bool isFocused = 0;
    bool isHovered = 0;
    bool hoverTex = 0;
    bool focusTex = 0;
    int height, width, posX, posY;
    sf::Texture textureUnhovered, textureHover, textureFocused;
    sf::RectangleShape rectangle;
    sf::IntRect rect;

    Textfield(std::string label, int width,int height,int posX, int posY, std::vector<int> state);
    void hovered();
    void unhovered();
    void focused();
    void unfocused(); // IK defocused huna parne ho but let that sink in
    void setContent(bool isBackspace);
};