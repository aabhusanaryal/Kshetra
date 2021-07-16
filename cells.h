#include <iostream>
#include <SFML/Graphics.hpp>


class Cells
{
    float posX, posY, originX, originY;

    //trying to make a key value pair of pairs of coordinates
    //so that the coordinate (0,0) will store the actual float position of the 
    //point on the screen i.e.(0,0) = (100.5, 200.5)

    static std::map<int, float> positionX;
    static std::map<int, float> positionY;


public:
    static int countX, countY;
    //constructor should store the position and the actual value
    Cells(float x, float y, float Ox, float Oy)
    {
        posX = x;
        posY = y; 
        originX = Ox;
        originY = Oy;
    }

    void setPosition();

    std::pair<float, float> getPosition(int x, int y);
    float getPositionX(int x);
    float getPositionY(int y);
};
