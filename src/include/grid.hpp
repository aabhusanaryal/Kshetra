#pragma once
#include "SFML/Graphics.hpp"

class Grid
{
private:
    sf::RectangleShape bg;
    int posX, posY;
    int width = 700;
    int height = 700;
    int cellWidth,cellHeight,cellCol,cellRow;
    int ogCellWidth = 700/22.f;
    std::vector<sf::RectangleShape> cells;


public:
    Grid(int=0,int=0, float=22.f);
    void display(sf::RenderWindow& window);
    void make_bg(sf::RenderWindow& window);
    void make_cells();
    float top();
    float right();
    float bottom();
    float left();
    sf::Vector2f returnOrigin();
    int returnCellWidth();
    int returnCellCol();
    int returnCellRow();
};