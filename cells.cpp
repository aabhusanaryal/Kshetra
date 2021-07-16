#include "cells.h"

int Cells::countX = 0;
int Cells::countY = 0;

//sets the key value pair in the map
void Cells::setPosition()
{
    positionX.insert(std::pair<int, float> (countX, posX));
    positionY.insert(std::pair<int, float> (countY, posY));
}

//returns a std::pair of the actual position of the coordinate on the screen
//i.e. (0, 0) ---> (12.5, 14.5)

std::pair <float, float> Cells::getPosition(int x, int y)
{
    std::pair <float, float> temp;
    temp.first = getPositionX(x);
    temp.second = getPositionY(y);
    return temp;
}

float Cells::getPositionX(int x)
{
    //this is the way to find the value by giving the key. Couldn't find any other way
    std::map<int, float>::iterator it;
     it = positionX.find(x);
     if(it != positionX.end())
        return it->second;
}

float Cells::getPositionY(int y)
{
    std::map<int, float>::iterator it;
     it = positionX.find(y);
     if(it != positionY.end())
        return it->second;
}


