#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Color.hpp>
#include<cmath>
#include<iostream>
#include"Grid.hpp"

#define pi 3.1415926
// const int lowerX=-10;
// const int lowerY=-10;
// const int higherX=10;
// const int higherY=10;

class vector{
    private:
        double posX,posY,angle,magnitude,pixelX,pixelY; //posX,posY for graph coordinates, pixlX,pixelY for plotting
        sf::Texture texture;
        sf::Color arrowColor;
    public:
        static int lowerX,lowerY,higherX,higherY;
        //expresson is a function pointer, one expression for i component, other for j
        //sf::vector2f is origin, and last int is cell width
        vector(int posX,int posY,double (*expressionX)(double,double),double (*expressionY)(double,double),Grid);
        void displayArrow(sf::RenderWindow&);
        static void setLimits(Grid);
        static void setHighest(std::vector<vector>&);
        static void setColor(std::vector<vector>&);
};
