#include "SFML/Graphics.hpp"
#include "components.h"

int main(){
    int windowWidth = 1080;
    int windowHeight = 720;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");

#pragma region Button
//    Button btn1("./assets/Button.png", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2);
//    sf::RectangleShape rect = btn1.getElement();
//    sf::Texture texture;
//    texture.loadFromFile(btn1.path);
//    rect.setTexture(&texture);
//
//
//    sf::Texture texture2;
//    texture2.loadFromFile("./assets/Button2.png");
//    sf::RectangleShape rect2(sf::Vector2f(298, 70));
//    rect2.setTexture(&texture2);
//    rect2.setPosition((windowWidth-298)/2, (windowHeight-70)/2+110);
//    
//    
//    
//    rect.setTexture(&texture2);
#pragma endregion

    Grid grid;
    std::cout<<"Top: "<<grid.top()<<std::endl;
    std::cout<<"left: "<<grid.left()<<std::endl;
    std::cout<<"bottom: "<<grid.bottom()<<std::endl;
    std::cout<<"right: "<<grid.right()<<std::endl;


    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        //window.draw(rect);
        //window.draw(rect2);
        grid.display(window);
        window.display();
    }
}
