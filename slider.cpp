#include "./slider.h"
#include <iostream>
#include "SFML/Graphics.hpp"

int width = 244;
int height = 4;
int radius = 27/2;

std::vector<Slider*> Slider::list;

Slider::Slider(int posX, int posY, int state){
    this->posX = posX;
    this->posY = posY;
    this->state = state;
    list.push_back(this);
    // Init rectangle and circle
    rectangle = sf::RectangleShape (sf::Vector2f(width, height));
    rectangle.setOrigin(0, height/2); // Setting up origin to align rect with circle
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    // Setting up RECT for click detection
    rect = sf::IntRect(posX-radius, posY-radius, width+radius*2, radius*2);
// HL-> testRectangle is used for debugging purpose and has no functional use
//      uncomment testRectangle line in the .draw() function overload for slider
//      to see the area where click is registered
    testRectangle = sf::RectangleShape(sf::Vector2f(width+radius*2, height));
    testRectangle.setFillColor(sf::Color::Red);
    testRectangle.setPosition(posX-radius, posY-radius);
    // Setting up positions
    
    circle.setPosition(posX, posY);
    rectangle.setPosition(posX, posY);
    // Loading up textures
    textureRect.loadFromFile(textureRectPath + ".png");
    textureCircle.loadFromFile(textureCirclePath + ".png");
    textureCircleClicked.loadFromFile(textureCirclePath + "Clicked.png");
    textureRect.setSmooth(true);
    textureCircle.setSmooth(true);
    textureCircleClicked.setSmooth(true);
    // Setting up textures
    rectangle.setTexture(&textureRect);
    circle.setTexture(&textureCircle);
};

void Slider::clicked(){
    std::cout<<"clicked"<<std::endl;
    sliding = true;
    circle.setTexture(&textureCircleClicked);
}
void Slider::unclicked(){
    std::cout<<"no"<<std::endl;
    sliding = false;
    circle.setTexture(&textureCircle);
}

void Slider::slide(float mouseX){
    if(mouseX>posX & mouseX<posX+width){
        circleX = mouseX;
    }
    if(mouseX<posX){
        circleX = posX;
    }
    if(mouseX>posX+width){
        circleX = posX+width;
    }
    circle.setPosition(circleX, posY);
    calculateProgress();
}

void Slider::calculateProgress(){
    // std::cout<<circleX<<"\t"<<posX<<"\t"<<width<<std::endl;
    progress = ((circleX-posX)/(float)width)*100;
    std::cout<<"Progress:"<<progress<<std::endl;
}


