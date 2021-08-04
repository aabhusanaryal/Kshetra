#include "canvas.hpp"
#include "window.h"

std::vector<canvas*> canvas::list;

canvas::canvas(int windowWidth,int windowHeight,doublePointerFn expressionX, doublePointerFn expressionY, int state){
    this->fnX = expressionX;
    this->fnY = expressionY;
    list.push_back(this);
    this->state = state;
    grid=Grid(windowWidth,windowHeight, 22);
    grid.make_cells();
    vector::setLimits(grid);
    for(int i=vector::lowerX;i<vector::higherX;i++){
        for(int j=vector::lowerY;j<vector::higherY;j++){
            arrows.push_back(new vector(i,j,fnX,fnY,grid));
        }
    }
    vector::setHighest(arrows);
    vector::setColor(arrows);
}

void canvas::reinitialiseVectors(doublePointerFn expressionX, doublePointerFn expressionY){
    fnX = expressionX;
    fnY = expressionY;
    arrows.clear();
    for(int i=vector::lowerX;i<vector::higherX;i++){
        for(int j=vector::lowerY;j<vector::higherY;j++){
            arrows.push_back(new vector(i,j,expressionX,expressionY,grid));
        }
    }
    vector::setHighest(arrows);
    vector::setColor(arrows);
}

void canvas::reinitialiseGrid(float scalar){
    // HL-> Need to un-hardcode windowWidth and windowHeight
    grid=Grid(1250-50, 850+40, scalar);
    grid.make_cells();
    vector::setLimits(grid);
    reinitialiseVectors(fnX, fnY);
}