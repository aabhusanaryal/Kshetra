#include "./window.h"
#include "SFML/Graphics.hpp"

void Window::mainLoop(){

// Creating the title for home screen
    sf::Sprite title;
    sf::Texture titleTexture;
    titleTexture.loadFromFile("./assets/main_Kshetra.png");
    title.setTexture(titleTexture);
    title.setPosition((width-431)/2, 250);

// Polling for events
    while(isOpen()){
    // Everything inside the main "game loop" goes here
        sf::Event event;
        while(pollEvent(event)){
            if(event.type==sf::Event::Closed) close();
            #include "./events/mousemove.h"
            #include "./events/mouseclick.h"
        }
        
// Rendering stuff   
        clear(sf::Color(251, 245, 243));
// Only draw the component if it belongs to the current state
        for(int i=0; i<Button::list.size(); i++){
            if((state == Button::list[i]->state || Button::list[i]->state == magicNumber))
                draw(Button::list[i]);
        }

        for(int i=0; i<Slider::list.size(); i++){
            if((state == Slider::list[i]->state || Slider::list[i]->state == magicNumber)){
                draw(Slider::list[i]);
            }
        }

// Drawing Title Text
        if(state == 0) draw(title);
        display();
    }
}