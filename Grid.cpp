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
//16 is the golden number
    float cellWidth= width/11; 
    float cellHeight = width/11;
//number of column and rows
    int cellCol = (width)/cellWidth;
    int cellRow = (height)/cellHeight;

//gap on the edges of the cells  
    float topPaddingcell = (height - cellHeight*cellRow)/2; 
    float leftPaddingcell = (width - cellWidth*cellCol)/2;

//color of the cells
    sf::Color color = sf::Color::Black;

//make the cells (will oop prolly)
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
            without decreasing its size*/
            
            cell.setFillColor(color);
            //cell.setOutlineThickness(1.5);
            //cell.setOutlineColor(sf::Color::Green);
            window.draw(cell);
        }
    }
}



