#include "canvas.hpp"

canvas::canvas(int windowWidth,int windowHeight,double (*expressionX)(double,double),double (*expressionY)(double,double)){
    grid=Grid(windowWidth,windowHeight);
    vector::setLimits(grid);
    for(int i=vector::lowerX;i<vector::higherX;i++){
        for(int j=vector::lowerY;j<vector::higherY;j++){
            arrows.push_back(vector(i,j,expressionX,expressionY,grid));
        }
    }
    vector::setHighest(arrows);
    vector::setColor(arrows);
}