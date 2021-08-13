#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Color.hpp>
#include<cmath>
#include<iostream>
#include<map>
#include"Grid.hpp"
#include<text.hpp>

#define pi 3.1415926

class Vector{
    private:
        double posX,posY,angle,pixelX,pixelY; //posX,posY for graph coordinates, pixlX,pixelY for plotting on sfml window
        sf::Color arrowColor; 
        static bool textureLoaded; //Checks if the texture for arrow is loaded or not
    public:
        double magnitude; //Magnitude of a vector
        static sf::Texture* texture;
        static Text* magnValue;
        static Text* angleValue;
        static Text* posValue;
        sf::Sprite sprite;
        static int lowerX,lowerY,higherX,higherY; //Limits of the graph to plot to

        //In the constrcutor below, expresson is a function pointer, one expression for i component, other for j
        //The grid that is used is passed too
        Vector(int posX,int posY,double (*expressionX)(double,double),double (*expressionY)(double,double),Grid);
        void displayArrow(sf::RenderWindow&); //Function to display a single arrow on screen
        void setTexture();
        static void setLimits(Grid); 
        static void setHighest(std::vector<Vector*>&); //Setting highest magnitude vector
        static void setColor(std::vector<Vector*>&); //Setting color of a vector according to magnitude
        void hovered(); //Called when an arrow is hovered on
        void unhovered(); //Called when an arrow is unhovered
        std::string roundNumber(double a);
};