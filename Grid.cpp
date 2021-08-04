#include "Grid.hpp"
#include <iostream>

Grid::Grid(int wwidth,int wheight, float scalar)
{
    windowWidth=wwidth;
    windowHeight=wheight;
    bg.setSize(sf::Vector2f(width,height));
    bg.setOrigin(width/2, height/2);
    bg.setPosition((windowWidth - width/2- paddingRight) , windowHeight/2);
    bg.setFillColor(sf::Color(229, 229, 229));
    //the size of each cell
    cellWidth= width/scalar; 
    cellHeight = cellWidth;
    //number of column and rows
    //number of column and rows that will fit in the required area
    // for(int i =0; (i+1)*cellWidth+left() < (right()); i++)
    //     cellCol +=1;
    // for(int j=0; (j+1)*cellHeight+top() < (bottom()); j++)
    //     cellRow +=1;  

    cellCol = scalar;
    cellRow = scalar;

//gap on the edges of the cells
//subtracts the background rect width with the number of cells * cell width and the value is divide by 2
//obtained value is applied to the left (makes the grid centered)  
    // topPaddingcell = (height - cellHeight*cellRow)/2; 
    // leftPaddingcell = (width - cellWidth*cellCol)/2;
}


//return the coordinate of the edges of the background rectangle
float Grid::top()   { return ((windowHeight-height)/2);}
float Grid::bottom(){ return (top() + height);}
float Grid::right() { return (windowWidth-paddingRight);}
float Grid::left()  { return (right() - width);}

void Grid::display(sf::RenderWindow& window)
{
    make_bg(window);
    for(int i=0;i<cells.size();i++){
        window.draw(cells[i]);
    }
}

void Grid::make_bg(sf::RenderWindow& window)
{
    window.draw(bg);
}

void Grid::make_cells()
{
//make cells

    for(int i =0; i*cellWidth+left() < (right()); i++)
    {
        for(int j=0; j*cellHeight+top() < bottom(); j++)
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
            cell.setFillColor(sf::Color(251, 245, 243));
            //cell.setOutlineThickness(1.5);
            //cell.setOutlineColor(sf::Color::Green);
            cells.push_back(cell);
            //std::cout<<"No of rows:"<<cellRow<<"\nNo of columns:"<<cellCol;
        }
    }
}

sf::Vector2f Grid::returnOrigin(){
    //leftPaddingcell+left()+(cellWidth*(cellCol/2)),topPaddingcell+top()+(cellWidth*(cellRow/2))
    return sf::Vector2f(830, 445);
}

int Grid::returnCellWidth(){
    return cellWidth;
}

int Grid::returnCellCol(){
    return cellCol;
}

int Grid::returnCellRow(){
    return cellRow;
}
    




