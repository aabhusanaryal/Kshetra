#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Color.hpp>
#include "vector.hpp"


void vector::displayArrow(sf::RenderWindow& window){
    if(magnitude!=0){
        sf::Sprite sprite;
        texture.loadFromFile("assets/Arrow7.png");
        sprite.setTexture(texture);
        sprite.setPosition(pixelX,pixelY);
        sprite.setRotation(angle);
        sprite.setOrigin(0,12);
        window.draw(sprite);
    }
}


