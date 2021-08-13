#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>
#include <text.hpp>

class Textfield{
    std::string label;
    Text* content;
    int contentPosX;
    int contentPosY;
    int height, width, posX, posY;
    sf::Texture textureUnhovered, textureHover, textureFocused, textureError;
public:
    static std::vector<Textfield*> list;
    std::vector<int> state;
    std::string text = "";
    Text* name;
    bool isFocused = 0;
    bool isHovered = 0;
    bool isError = 0;
    sf::RectangleShape rectangle;
    sf::IntRect rect;

    Textfield(std::string label, int width,int height,int posX, int posY, std::vector<int> state);
    void hovered();
    void unhovered();
    void focused();
    void unfocused(); // IK defocused huna parne ho but let that sink in
    void error();
    void setContent(bool isBackspace);
};