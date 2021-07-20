#include "cells.h"
#include "Grid.hpp"
#include <iostream>

Grid::Grid()
{
    bg.setSize(sf::Vector2f(width, height));
    bg.setOrigin(width/2, height/2);
    bg.setPosition((windowWidth - width/2- paddingRight) , windowHeight/2);
    bg.setFillColor(sf::Color(229, 229, 229));
}


//return the coordinate of the edges of the background rectangle
float Grid::top()   { return (paddingVertical/2);}
float Grid::bottom(){ return (top() + height);}
float Grid::right() { return (windowWidth-paddingRight);}
float Grid::left()  { return (right() - width);}

void Grid::display(sf::RenderWindow& window)
{
    make_bg(window);
    make_cells(window);
}

void Grid::make_bg(sf::RenderWindow& window)
{
    window.draw(bg);
}

void Grid::make_cells(sf::RenderWindow& window)
{

//the size if each cell
    float cellWidth= width/22.f; 
    float cellHeight = cellWidth;
//number of column and rows
    int cellCol = 0;
    int cellRow = 0;

//number of column and rows that will fit in the required area
    for(int i =0; (i+1)*cellWidth+left() < (right()); i++)
        cellCol +=1;
    for(int j=0; (j+1)*cellHeight+top() < bottom(); j++)
        cellRow +=1;  

//gap on the edges of the cells
//subtracts the background rect width with the number of cells * cell width and the value is divide by 2
//obtained value is applied to the left (makes the grid centered)  
    float topPaddingcell = (height - cellHeight*cellRow)/2; 
    float leftPaddingcell = (width - cellWidth*cellCol)/2;

//make cells

    for(int i =0; (i+1)*cellWidth+left() < (right()); i++)
    {
        for(int j=0; (j+1)*cellHeight+top() < bottom(); j++)
        {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellWidth-1.5, cellHeight-1.5));
            cell.setPosition
            (
                leftPaddingcell + left() + cellWidth*i, 
                topPaddingcell + top() + cellHeight*j
            );
            
            /* We can do grid by setting thickness of the rectangle 
            without decreasing its size
            remove set size from the setsize and uncomment bottom code*/
            cell.setFillColor(sf::Color(98, 96, 95));
            //cell.setOutlineThickness(1.5);
            //cell.setOutlineColor(sf::Color::Green);
            window.draw(cell);
        }
    }
}
    




