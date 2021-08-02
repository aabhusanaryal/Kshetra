#include "canvas.hpp"


std::vector<canvas*> canvas::list;

canvas::canvas(int windowWidth,int windowHeight,double (*expressionX)(double,double),double (*expressionY)(double,double), int state){
    list.push_back(this);
    this->state = state;
    grid=Grid(windowWidth,windowHeight);
    grid.make_cells();
    vector::setLimits(grid);
    for(int i=vector::lowerX;i<vector::higherX;i++){
        for(int j=vector::lowerY;j<vector::higherY;j++){
            arrows.push_back(new vector(i,j,expressionX,expressionY,grid));
        }
    }
    vector::setHighest(arrows);
    vector::setColor(arrows);
}