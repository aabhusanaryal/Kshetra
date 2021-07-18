#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Color.hpp>
#include<cmath>
#include<iostream>

#define pi 3.1415926

class vector{
    private:
        double posX,posY,angle,magnitude,pixelX,pixelY; //posX,posY for graph coordinates, pixlX,pixelY for plotting
        sf::Texture texture;
    public:
        //expresson is a function pointer, have to pass a function for the parsed expression, maybe 1 for x, 1 for y
        vector(int posX,int posY,double (*expressionX)(double,double),double (*expressionY)(double,double)){ 
            this->posX=posX;
            this->posY=posY;
            this->pixelX=500+(this->posX*39.5); //origin at 500 pixels
            this->pixelY=500-((this->posY*39.5)); //origin at 500 pixels

            double magnX=expressionX(this->posX,this->posY); //temp to store value on i component
            double magnY=expressionY(this->posX,this->posY); //temp to store value at j component


            this->magnitude=sqrt(pow(magnX,2)+pow(magnY,2));
            

            //angle set according to quadrant
            if(magnX>0 && magnY>0) 
                this->angle=-(atan(magnY/magnX)*(180/pi));
            else if(magnX<0 && magnY>0)
                this->angle=-(180+(atan(magnY/magnX)*(180/pi)));
            else if(magnX<0 && magnY<0)
                this->angle=-(180+(atan(magnY/magnX)*(180/pi)));
            else if(magnX>0 && magnY<0)
                this->angle=-(360+(atan(magnY/magnX)*(180/pi)));
            else if(magnX==0){
                if(magnY>0){this->angle=-90;}
                else if(magnY<0){this->angle=90;}
            }
            else if(magnY==0){
                if(magnX>0){this->angle=0;}
                else if(magnX<0){this->angle=-180;}
            }
        }
        void displayArrow(sf::RenderWindow&);
};
