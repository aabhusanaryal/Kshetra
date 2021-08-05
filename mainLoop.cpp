#include "./window.h"
#include "SFML/Graphics.hpp"
#include "canvas.hpp"
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
            #include "./events/keypress.h"
        }
        
// Rendering stuff   
        clear(sf::Color(251, 245, 243));
        // clear(sf::Color(0, 0, 0));

        // Drawing Canvas and arrows and all handling zomming in
        if(Slider::list[0]->sliding && (state == Slider::list[0]->state || (Slider::list[0]->state==420 && (state == 1 || state == 2)))){
            canvas::list[0]->reinitialiseGrid(22-Slider::list[0]->progress*0.08); // For zoom in/ out
        }
        if(state == canvas::list[0]->state || (canvas::list[0]->state==oneAndTwo && (state == 1 || state == 2))){
            if(showGrid)
                canvas::list[0]->grid.display(*(this));
            if(showArrows){
                for(int i=0;i<canvas::list[0]->arrows.size();i++){
                    draw(canvas::list[0]->arrows[i]);
                }
            }
        }

        // Making overlay for state 1
        sf::RectangleShape overlay(sf::Vector2f(width, height));
        sf::Texture overlayTexture;
        overlayTexture.loadFromFile("./assets/one_Overlay.png");
        overlay.setTexture(&overlayTexture);
        overlay.setPosition(0,0);
        if(state==1 || state == 2)
            draw(overlay);

// Drawing other components such as buttons and sliders
// Only draw the component if it belongs to the current state
        for(int i=0; i<Button::list.size(); i++){
            if((state == Button::list[i]->state || Button::list[i]->state == magicNumber) || (Button::list[0]->state==oneAndTwo && (state == 1 || state == 2)))
                draw(Button::list[i]);
        }

        for(int i=0; i<Slider::list.size(); i++){
            if((state == Slider::list[i]->state || Slider::list[i]->state == magicNumber) || (Slider::list[0]->state==oneAndTwo && (state == 1 || state == 2))){
                draw(Slider::list[i]);
            }
        }

        for(int i=0; i<Textfield::list.size(); i++){
            if((state == Textfield::list[i]->state || Textfield::list[i]->state == magicNumber) || (Textfield::list[0]->state==oneAndTwo && (state == 1 || state == 2))){
                draw(Textfield::list[i]);
            }
        }
        

// Drawing Title Text
        if(state == 0) draw(title);
        display();
    }
}