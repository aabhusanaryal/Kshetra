#pragma once
#include "SFML/Graphics.hpp"

class Text : public sf::Text{
public:
    static std::vector<Text*> list;
    std::vector<int> state;
    std::string content;
    sf::Text text;
    sf::Font font;
    int size;
    int posX, posY;

    Text(std::string content, int size, int posX, int posY, std::vector<int> state){
        this->content = content;
        this->size = size;
        this->posX = posX;
        this->posY = posY;
        this->state = state;
        this->list.push_back(this);

        font.loadFromFile("./assets/Fonts/Roboto-Regular.ttf");
        text.setFont(font);
        text.setString(content);
        text.setCharacterSize(size);
        text.setPosition(posX, posY);
        text.setFillColor(sf::Color::Black);
    }
    Text(std::string content, int size, int posX, int posY, std::string type, std::vector<int> state){
        this->content = content;
        this->size = size;
        this->posX = posX;
        this->posY = posY;
        this->state = state;
        this->list.push_back(this);

        font.loadFromFile(std::string("./assets/Fonts/"+type+".ttf"));
        text.setFont(font);
        text.setString(content);
        text.setCharacterSize(size);
        text.setPosition(posX, posY);
        text.setFillColor(sf::Color::Black);
    }
    void setString(std::string content){
        text.setString(content);
    }
    Text(){};
};