// ===========================================================================
// Usage: Button btnName(path, width, height, posX, posY, state);
// ===========================================================================
// textureHovereded is the texture that's to be rendered when the user hovers
// over the button. We set rect's texxture as textureHovereded on hovering.
// ===========================================================================
// textureUnhovered exists because we need to set textureRendered back to the 
// original state when the user un-hovers.
// We set rect's texxture as textureUnovered on un-hovering.
// ===========================================================================


// ===================== POLLING FOR EVENTS IN MOUSEMOVE.H =======================
// if(event.type==sf::Event::MouseMoved){ // If mouse is moved
//             // On hover
//                 if(btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
//                     btn1.hovered();
//             // On not hovering
//                 if(!btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
//                     btn1.unhovered();
//             }
// ===========================================================================

// ===================== How this component works =======================
// To create the button, we first create a sf::RectangleShape and then add a texture
// which essentially is the image that's rendered as the button.

// So we poll for events in the mousemove.h and mouseclick.h, which are included in the
// main loop. Whenever the button is being hovered on, the texture changes to textureHovered
// and as soon as the mouse goes out of bound of the button, the texture changes to 
// textureUnhovered.

// Then, when the button is clicked, it calles a function called action which is of type
// pointerFn, which basically means it is a pointer to a function. This function takes 
// in no parameter and returns void.
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
    rect = rectangle.getGlobalBounds();
    // Loading different images in textures
    textureHovered.loadFromFile(std::string("./assets/"+path+"_Hovered.png"));
    textureUnhovered.loadFromFile(std::string("./assets/"+path+".png"));
    textureHovered.setSmooth(true); // Avoids pixelation of texture
    textureUnhovered.setSmooth(true);
    rectangle.setTexture(&textureUnhovered); // Setting the initial textureRendered to be the unhovered one
}

void Button::setPosition(int x, int y){  // Sets the position of button on screen
    rectangle.setPosition(x, y);
}

void Button::hovered(){ // Sets the right texture when the button is hovered
    if(!isHovered){ // Setting texture to textureHovered iff it's not already textureHovered
        rectangle.setTexture(&textureHovered);
        isHovered = 1;
    }
}

void Button::unhovered(){ // Sets the right texture when the button is not hovered
    if(isHovered){ // Setting texture to textureUnover iff it's not already textureUnhover
        rectangle.setTexture(&textureUnhovered);
        isHovered = !isHovered;
    }
}

void Button::setAction(pointerFn action){
    this->action = action;
}


