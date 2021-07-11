#include "./slider.h"
#include <iostream>
#include "SFML/Graphics.hpp"

int width = 244;
int height = 4;
int radius = 27/2;
Slider::Slider(int posX, int posY){
    this->posX = posX;
    this->posY = posY;
    // Init rectangle and circle
    rectangle = sf::RectangleShape (sf::Vector2f(width, height));
    rectangle.setOrigin(0, height/2); // Setting up origin to align rect with circle
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    // Setting up RECT for click detection
    rect = sf::IntRect(posX-radius, posY-radius, radius*2, radius*2);
    testRectangle = sf::RectangleShape(sf::Vector2f(radius*2, radius*2));
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

void Slider::draw(sf::RenderWindow &window){
    window.draw(rectangle);
    // window.draw(testRectangle);
    window.draw(circle);
}

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

void Slider::slide(float x){
    if(x>posX & x<posX+width){
        circleX = x;
        circle.setPosition(circleX, posY);
        rect = sf::IntRect(circleX-radius, posY-radius, radius*2, radius*2);
        calculateProgress();
    }
}

void Slider::calculateProgress(){
    // std::cout<<circleX<<"\t"<<posX<<"\t"<<width<<std::endl;
    progress = ((circleX-posX)/(float)width)*100;
    std::cout<<"Progress:"<<progress<<std::endl;
}


