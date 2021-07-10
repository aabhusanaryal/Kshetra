#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"

int main(){
    int windowWidth = 1080;
    int windowHeight = 720;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");


    Button btn1("./assets/main_Std_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2);
    Button btn2("./assets/main_Custom_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+100);
    
    Slider slider(300, 100);
    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::MouseMoved){ // If mouse is moved
// =========================== FOR BUTTONS ===========================
        // Button 1:
            // On hover
                if(btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn1.hovered();
            // On not hovering
                if(!btn1.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn1.unhovered();

        // Button 2
            // On hover
                if(btn2.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn2.hovered();
            // On not hovering
                if(!btn2.rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    btn2.unhovered();
            }
// =========================== FOR Sliders ===========================
// FIX:
// Event handling not working as expected. The code under MouseButtonPressed
// also runs when the mouse button is released.
            if(event.type=sf::Event::MouseButtonPressed){ // <-----------
                if(event.mouseButton.button == sf::Mouse::Left){
                    // std::cout<<"mouse button pressed"<<event.mouseButton.x;
                    if(slider.rect.contains(event.mouseButton.x, event.mouseButton.y))
                        slider.clicked();
                }
            }
            if(event.type=sf::Event::MouseButtonReleased){ // <-----------
                if(event.mouseButton.button == sf::Mouse::Left){
                    // std::cout<<"mouse button pressed"<<event.mouseButton.x;
                    if(slider.rect.contains(event.mouseButton.x, event.mouseButton.y))
                        slider.unclicked();
                }
            }
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        // window.draw(btn1.rectangle);
        // window.draw(btn2.rectangle);
        slider.draw(window);
        window.display();
    }
}