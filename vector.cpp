#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Color.hpp>
#include "vector.hpp"

double highestMagn;
void vector::displayArrow(sf::RenderWindow& window){
    if(magnitude!=0){
        sf::Sprite sprite;
        texture.loadFromFile("assets/Arrow10(1).png");
        sprite.setTexture(texture);
       // sf::Color current_color(sf::Color((scalar*dark.r)+((1-scalar)*light.r),(scalar*dark.g)+((1-scalar)*light.g), (scalar*dark.b)+((1-scalar)*light.b)));
        sprite.setColor(arrowColor);
        sprite.setPosition(pixelX,pixelY);
        sprite.setRotation(angle);
        sprite.setOrigin(0,12);
        window.draw(sprite);
    }
}

void vector::setHighest(std::vector<vector>& arrows){
    highestMagn=arrows[0].magnitude;
    for(int i=0;i<arrows.size();i++){
        if(arrows[i].magnitude>highestMagn){highestMagn=arrows[i].magnitude;}
    }
}

void vector::setColor(std::vector<vector>& arrows){
    sf::Color dark(255, 0, 0);
    sf::Color light(0, 0, 255);
    for(int i=0;i<arrows.size();i++){
        double scalar=(arrows[i].magnitude/highestMagn);
        arrows[i].arrowColor=sf::Color((scalar*dark.r)+((1-scalar)*light.r),(scalar*dark.g)+((1-scalar)*light.g), (scalar*dark.b)+((1-scalar)*light.b));
    }
}




