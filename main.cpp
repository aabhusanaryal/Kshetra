#include "SFML/Graphics.hpp"
#include "components.h"
#include "vector.hpp"

double forX(double x,double y){
    return x;
}

double forY(double x,double y){
    return y;
}

int main(){
    int windowWidth = 1920;
    int windowHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");
    // Button btn1("./assets/Button.png", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2);
    // sf::RectangleShape rect = btn1.getElement();
    // sf::Texture texture;
    // texture.loadFromFile(btn1.path);
    // rect.setTexture(&texture);


    // sf::Texture texture2;
    // texture2.loadFromFile("./assets/Button2.png");
    // sf::RectangleShape rect2(sf::Vector2f(298, 70));
    // rect2.setTexture(&texture2);
    // rect2.setPosition((windowWidth-298)/2, (windowHeight-70)/2+110);
    
    
    
    // rect.setTexture(&texture2);

    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        for(int i=-15;i<=15;i++){
            for(int j=-15;j<=15;j++){
                vector a(i,j,forX,forY);
                a.displayArrow(window);
            }
        }
        window.display();
    }
}