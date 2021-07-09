// ===========================================================================
// So, why exactly do we have 3 textures?
// textureRendered[initially equal to textureUnhovered] is the texture
// that's being rendered as the button's bg
// ===========================================================================
// textureHovered is the texture that's to be rendered when the user hovers
// over the button. We set textureRendered = textureHovered on hovering.
// ===========================================================================
// textureUnhovered exists because we need to set textureRendered back to the 
// original state when the user un-hovers.
// We set textureRendered = textureUnovered on un-hovering.
// ===========================================================================

#include "./button.h"
#include <iostream>
#include "SFML/Graphics.hpp"

Button::Button(std::string path,int width,int height,int posX, int posY){ // Constructor
    // Setting up member datas
    this->path = path;
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    // Creating a rectangle, that'll later be rendered using window.display()
    rectangle = sf::RectangleShape (sf::Vector2f(width, height));
    rectangle.setPosition(posX, posY);
    // =========================================================================
    // Rect is NOT the rectange that's being rendered, but rather a rectangular
    // space in screen. We need this to check if the button is being hovered on.
    // This basically "invisibly wraps" our rectangle
    // =========================================================================
    rect = sf::IntRect(posX, posY, width, height);
    // Loading different images in texture
    textureHover.loadFromFile(std::string(path+"_Hovered.png"));
    textureUnhovered.loadFromFile(std::string(path+".png"));
    // Setting the initial textureRendered to be the unhovered one
    textureRendered = textureUnhovered;
    rectangle.setTexture(&textureRendered);
}

void Button::setPosition(int x, int y){  // Sets the position of button on screen
    rectangle.setPosition(x, y);
}

void Button::hovered(){ // Sets the right texture when the button is hovered
    if(!hoverTex){ // Setting texture to textureHover iff it's not already textureHover
        rectangle.setTexture(&textureHover);
        hoverTex = !hoverTex;
    }
}

void Button::unhovered(){ // Sets the right texture when the button is not hovered
    if(hoverTex){ // Setting texture to textureUnover iff it's not already textureUnhover
        rectangle.setTexture(&textureUnhovered);
        hoverTex = !hoverTex;
    }
}


