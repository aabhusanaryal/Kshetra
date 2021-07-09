#include "SFML/Graphics.hpp"
#include "button.h"

int main(){
    int windowWidth = 1080;
    int windowHeight = 720;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");

    Button btn1("./assets/main_Std_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2);
    Button btn2("./assets/main_Custom_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+100);
  
    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::MouseMoved){ // If mouse is moved
            // On hover
                if(btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn1.hovered();
            // On not hovering
                if(!btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn1.unhovered();
            }
            if(event.type==sf::Event::MouseMoved){ // If mouse is moved
            // On hover
                if(btn2.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn2.hovered();
            // On not hovering
                if(!btn2.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn2.unhovered();
            }
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        window.draw(btn1.rectangle);
        window.draw(btn2.rectangle);
        window.display();
    }
}