#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Cells
{
    float posX, posY, width, height;
    sf::RectangleShape cell;
    //trying to make a key value pair of pairs of coordinates
    //so that the coordinate 0,0 will store the actual float position of the 
    //point on the screen
    static std::map<int, float> positionX;
    static std::map<int, float> positionY;


public:

    Cells();
    static int countX, countY;
    //constructor should store the position and the actual value
    Cells(float x, float y, float w, float h)
    {
        posX = x;
        posY = y;
        width = w;
        height = h;
        cell.setPosition(x, y);
        cell.setSize(sf::Vector2f(width, height));
        cell.setOrigin(0, height);

        positionX.insert(std::pair<int, float> (countX, posX));
        positionY.insert(std::pair<int, float> (countY, posY));
    }

    void setPosition();
    void display(sf::RenderWindow &window);

    static std::pair<float, float> getPosition(int x, int y);
    static float getPositionX(int x);
    static float getPositionY(int y);
};
