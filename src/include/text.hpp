// ===========================================================================
// Usage: Text text("Content", fontSize, posX, posY, [optional: font face], state);
// ===========================================================================

// ===================== How this component works =======================
// It just creates a sf::Text and sets the font to Roboto-Regular by default. Other fonts 
// may be supplied through the constructor but its not necessary. Then, it draws the
// sf::Text to the appropriate state(s).
// ======================================================================
#pragma once
#include "SFML/Graphics.hpp"

class Text : public sf::Text{
    sf::Font font;
    int size;
    int posX, posY;
public:
    static std::vector<Text*> list;
    std::vector<int> state;
    std::string content;
    sf::Text text;
// If no font is provided
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
// If a font is provided
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