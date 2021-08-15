#include<window.hpp>
#include<Canvas.hpp>
#include<text.hpp>
#include<commonfunctions.hpp>
#include "SFML/Graphics.hpp"
#include <algorithm>
#include <SFML/Window/Keyboard.hpp>

void Window::mainLoop(){

// Creating the title for home screen
    sf::Sprite title;
    sf::Texture titleTexture;
    titleTexture.loadFromFile("./assets/main_Kshetra.png");
    title.setTexture(titleTexture);
    title.setPosition((width-431)/2, 190);



// Polling for events
    while(isOpen()){
    // Everything inside the main "game loop" goes here
        sf::Event event;
        while(pollEvent(event)){
            if(event.type==sf::Event::Closed) close();
            #include "../events/mousemove.h"
            #include "../events/mouseclick.h"
            #include "../events/keypress.h"
        }
        
// Rendering stuff   
        clear(sf::Color(251, 245, 243));
        // clear(sf::Color(0, 0, 0));

        // Drawing Canvas and arrows and all handling zomming in
        if(Slider::list[0]->sliding && (std::find(Slider::list[0]->state.begin(), Slider::list[0]->state.end(), state) != Slider::list[0]->state.end())){
            Canvas::list[0]->reinitialiseGrid(22-Slider::list[0]->progress*0.08); // For zoom in/ out
        }
        if(std::find(Canvas::list[0]->state.begin(), Canvas::list[0]->state.end(), state) != Canvas::list[0]->state.end()){
                Canvas::list[0]->grid.display(*(this));
                for(int i=0;i<Canvas::list[0]->arrows.size();i++){
                    draw(Canvas::list[0]->arrows[i]);
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
            if(std::find(Button::list[i]->state.begin(), Button::list[i]->state.end(), state) != Button::list[i]->state.end())
                draw(Button::list[i]);
        }

        for(int i=0; i<Slider::list.size(); i++){
            if(std::find(Slider::list[i]->state.begin(), Slider::list[i]->state.end(), state) != Slider::list[i]->state.end()){
                draw(Slider::list[i]);
            }
        }
        

        for(int i=0; i<Textfield::list.size(); i++){
            if(std::find(Textfield::list[i]->state.begin(), Textfield::list[i]->state.end(), state) != Textfield::list[i]->state.end()){
                draw(Textfield::list[i]);
            }
        }

        for(int i=0; i<Text::list.size(); i++){
            if(std::find(Text::list[i]->state.begin(), Text::list[i]->state.end(), state) != Text::list[i]->state.end()){
                draw(Text::list[i]->text);
            }
        }
        

// Drawing Title Text
        if(state == 0) draw(title);
        display();
    }
}