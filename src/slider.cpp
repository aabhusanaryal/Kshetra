// ===========================================================================
// Usage: Slider sldName(posX, posY, state);
// ===========================================================================

// ===================== How this component works =======================
// When the user clicks anywhere on the slider (even outside the circle part), the slider
// attains a "sliding" state whereby it changes its texture and snaps to the mouse's
// x position as long as the mouse position remains within the bounds of the slider.
// A user may access the progress of the slider on a scale of 0 to 100 using as
// slider.progress
// ======================================================================
#include<slider.hpp>
#include <iostream>
#include "SFML/Graphics.hpp"

std::vector<Slider*> Slider::list;

Slider::Slider(int posX, int posY, std::vector<int> state){
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
    sliding = true;
    circle.setTexture(&textureCircleClicked);
}
void Slider::unclicked(){
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
    progress = ((circleX-posX)/(float)width)*100;
}



