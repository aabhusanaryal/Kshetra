#include "cells.h"

void Cells::setPosition()
{
    positions.insert({std::pair<float, float>(posX, posY), 
                      std::pair<int, int>(countX, countY)});
}