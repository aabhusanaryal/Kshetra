#pragma once
#include "SFML/Graphics.hpp"

class Grid
{
private:
    sf::RectangleShape bg; //gray bg behind the cells
    int posX, posY; //position of grid 
    int width = 700; //size of grid 
    int height = 700;
    int cellWidth,cellHeight,cellCol,cellRow; //parameters for a single cell in the grid
    int ogCellWidth = 700/22.f; //default cell width before zooming in
    std::vector<sf::RectangleShape> cells; //collection of all cells


public:
    Grid(int=0,int=0, float=22.f);
    void display(sf::RenderWindow& window);
    void makeBg(sf::RenderWindow& window);
    void makeCells(); //populates the "cells" std::vector
    float top(); //returns top most pixel value of grid
    float right(); //returns right most pixel value of grid
    float bottom(); //returns bottom most pixel value of grid
    float left(); //returns left most pixel value of grid
    sf::Vector2f returnOrigin();
    int returnCellWidth();
    int returnCellCol();
    int returnCellRow();
};