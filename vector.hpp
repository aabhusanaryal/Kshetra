#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Color.hpp>
#include<cmath>
#include<iostream>
#include<map>
#include"Grid.hpp"
#include"text.h"

#define pi 3.1415926
// const int lowerX=-10;
// const int lowerY=-10;
// const int higherX=10;
// const int higherY=10;

class vector{
    private:
        double posX,posY,angle,pixelX,pixelY; //posX,posY for graph coordinates, pixlX,pixelY for plotting
        sf::Color arrowColor;
        static bool textureLoaded;
    public:
        double magnitude;
        static sf::Texture* texture;
        static Text* magnValue;
        static Text* angleValue;
        static Text* posValue;
        // static std::map<std::string,std::string> details {{"Magnitude",std::to_string(magnitude)},{"Angle",std::to_string(angle)},{"Position",(std::to_string(posX)+","+std::to_string(posY))}};
        sf::Sprite sprite;
        static int lowerX,lowerY,higherX,higherY;
        //expresson is a function pointer, one expression for i component, other for j
        //sf::vector2f is origin, and last int is cell width
        vector(int posX,int posY,double (*expressionX)(double,double),double (*expressionY)(double,double),Grid);
        void displayArrow(sf::RenderWindow&);
        void setTexture();
        static void setLimits(Grid);
        static void setHighest(std::vector<vector*>&);
        static void setColor(std::vector<vector*>&);
        void hovered();
        void unhovered();
        std::string roundNumber(double a);
};
