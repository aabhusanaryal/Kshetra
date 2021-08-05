#include "./textfield.h"

std::vector<Textfield*> Textfield::list;

Textfield::Textfield(int width,int height,int posX, int posY, int state){
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    this->state = state;
    list.push_back(this);

    rectangle = sf::RectangleShape (sf::Vector2f(width, height));
    rectangle.setPosition(posX, posY);
// =========================================================================
// HL->WARNING:
// Rect is NOT the rectange that's being rendered, but rather a rectangular
// space in screen. We need this to check if the button is being hovered on.
// This basically "invisibly wraps" our rectangle
// =========================================================================
    rect = sf::IntRect(posX, posY, width, height);
    // Loading different images in texture
    textureHover.loadFromFile(std::string("./assets/textbox_Hovered.png"));
    textureUnhovered.loadFromFile(std::string("./assets/textbox.png"));
    textureFocused.loadFromFile(std::string("./assets/textbox_Focused.png"));
    // Setting the initial textureRendered to be the unhovered one
    rectangle.setTexture(&textureUnhovered);
}

void Textfield::hovered(){ // Sets the right texture when the textbox is hovered
    if(!isHovered && !isFocused){ // Setting texture to textureHover iff it's not already textureHover
        rectangle.setTexture(&textureHover);
        isHovered = 1;
    }
}

void Textfield::unhovered(){ // Sets the right texture when the textbox is not hovered
    if(isHovered && !isFocused){ // Setting texture to textureUnover iff it's not already textureUnhover
        rectangle.setTexture(&textureUnhovered);
        isHovered = 0;
    }
}

void Textfield::focused(){ // Sets the right texture when the textbox is focused (clicked)
    if(!isFocused){ // Setting texture to textureHover iff it's not already textureHover
        rectangle.setTexture(&textureFocused);
        isFocused = 1;
        isHovered = 0;
    }
}

void Textfield::unfocused(){ // Sets the right texture when the textbox is not hovered
    if(isFocused){ // Setting texture to textureUnover iff it's not already textureUnhover
        rectangle.setTexture(&textureUnhovered);
        isFocused = 0;
    }
}