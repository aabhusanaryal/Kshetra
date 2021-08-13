// ===========================================================================
// Usage: Grid gridName(posX, posY, cellSizeScalar);
// ===========================================================================

// ===================== How this component works =======================
// When a grid is instantiated, a cell size and the postion on the window is specified. The constructor sets the cell size as
// the scalar passed. The makeCells function, when called, makes individual cells and pushes it to a std::vector called cells. The 
// individual cells are made using values of the cell size, and position of the cell is set by looping through a nested loop, 
// where the iterating variable is checked against number of rows and number of columns. 

// Finally display() draws both the background bg(an sf::RectangleShape), and the cells (sf::RectangleShape).

// returnOrigin and returnCellWidth is used in the vector class to plot the vector on the graph.

// returnCellCol and returnCellRow returns total number of rows and columns in the grid, which is also used in the vector class
// to set the number of vectors in the grid. 
// ===========================================================================

#include<grid.hpp>
#include <iostream>

Grid::Grid(int posX,int posY, float scalar) :posX(posX), posY(posY)
{
    bg.setSize(sf::Vector2f(width,height));
    bg.setPosition(posX, posY);
    bg.setFillColor(sf::Color(229, 229, 229));

    //the size of each cell
    cellWidth= width/scalar; 
    cellHeight = cellWidth;
   
    //number of column and rows
    cellCol = scalar;
    cellRow = scalar;

}

//return the coordinate of the edges of the background rectangle
float Grid::top()   { return posY; }
float Grid::bottom(){ return (top() + height); }
float Grid::right() { return (posX+width); }
float Grid::left()  { return (right() - width); }

void Grid::display(sf::RenderWindow& window)
{
    makeBg(window);
    for(int i=0;i<cells.size();i++){
        window.draw(cells[i]);
    }
}

void Grid::makeBg(sf::RenderWindow& window)
{
    window.draw(bg);
}

void Grid::makeCells()
{
    cells.clear();
    for(int i =0; i*ogCellWidth+left() < (right()); i++)
    {
        for(int j=0; j*ogCellWidth+top() < bottom(); j++)
        {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellWidth-1.5, cellHeight-1.5));
            float initialPositionX = (left() + cellWidth*i);
            float initialPositionY = (top() + cellHeight*j);
            cell.setPosition
            (
                (left() + ogCellWidth*i) - (cellWidth - ogCellWidth)*(11-i) , 
                (top() + ogCellWidth*j) - (cellHeight - ogCellWidth)*(11-j)
            );
            cell.setFillColor(sf::Color(251, 245, 243)); //cell color
            cells.push_back(cell);
        }
    }
}

sf::Vector2f Grid::returnOrigin(){
    return sf::Vector2f(850, 358);
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