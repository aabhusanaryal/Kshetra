// ===========================================================================
// Usage: Button btnName(path, width, height, posX, posY, state);
// ===========================================================================
// textureHovered is the texture that's to be rendered when the user hovers
// over the button. We set rect's texxture as textureHovered on hovering.
// ===========================================================================
// textureUnhovered exists because we need to set textureRendered back to the 
// original state when the user un-hovers.
// We set rect's texxture as textureUnovered on un-hovering.
// ===========================================================================


// ===================== POLLING FOR EVENTS IN MAIN.CPP =======================
// if(event.type==sf::Event::MouseMoved){ // If mouse is moved
//             // On hover
//                 if(btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
//                     btn1.hovered();
//             // On not hovering
//                 if(!btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
//                     btn1.unhovered();
//             }
// ===========================================================================

#include <button.hpp>
#include <iostream>
#include "SFML/Graphics.hpp"

std::vector<Button*> Button::list;

Button::Button(std::string path,int width,int height,int posX, int posY, std::vector<int> state){ // Constructor
    // Setting up member datas
    this->path = path;
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    this->state = state;
    list.push_back(this);
    // Creating a rectangle, that'll later be rendered using window.display()
    rectangle = sf::RectangleShape (sf::Vector2f(width, height));
    rectangle.setPosition(posX, posY);
    // =========================================================================
    // WARNING:
    // Rect is NOT the rectange that's being rendered, but rather a rectangular
    // space in screen. We need this to check if the button is being hovered on.
    // This basically "invisibly wraps" our rectangle
    // =========================================================================
    rect = sf::IntRect(posX, posY, width, height);
    // Loading different images in texture
    textureHover.loadFromFile(std::string("./assets/"+path+"_Hovered.png"));
    textureUnhovered.loadFromFile(std::string("./assets/"+path+".png"));
    textureHover.setSmooth(true);
    textureUnhovered.setSmooth(true);
    // Setting the initial textureRendered to be the unhovered one
    rectangle.setTexture(&textureUnhovered);
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

void Button::setAction(pointerFn action){
    this->action = action;
}


