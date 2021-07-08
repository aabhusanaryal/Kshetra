#include "./components.h"
#include <iostream>
#include "SFML/Graphics.hpp"

sf::RectangleShape Button::getElement(){
    sf::Texture texture;
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(posX, posY);
    return rect;
}


