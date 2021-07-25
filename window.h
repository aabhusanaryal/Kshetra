#pragma once
#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"

class Window : public sf::RenderWindow{
public:
    int state = 0;
    int mouseX, mouseY;
    int magicNumber = 69;
//HL-> Constructor
    Window(sf::VideoMode video, const sf::String path): sf::RenderWindow(video, path){}
//HL-> .draw() method overloads
    void draw(Button* btn){
        sf::RenderWindow::draw(btn->rectangle);
    }
    void draw(Slider* slider){
        sf::RenderWindow::draw(slider->rectangle);
        sf::RenderWindow::draw(slider->circle);
        // sf::RenderWindow::draw(slider->testRectangle); // Uncomment for debugging
    }
    void draw(sf::RectangleShape rectangle){
        sf::RenderWindow::draw(rectangle);
    }
//HL-> Main Loop
    void mainLoop(){

    while(isOpen()){
    // Everything inside the main "game loop" goes here
        sf::Event event;
        while(pollEvent(event)){
            if(event.type==sf::Event::Closed) close();
// HL->MOUSEMOVE:
// ======================== HANDLING MOUSE MOVES ========================
            if(event.type==sf::Event::MouseMoved){ // If mouse is moved
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
//           ================= FOR BUTTONS' HOVER ANIMATION =================
            for(int i=0; i<Button::list.size(); i++){
                // On hover
                if(((state == Button::list[i]->state || Button::list[i]->state == magicNumber) || (state == Button::list[i]->state || Button::list[i]->state == magicNumber) == magicNumber)&& Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y))
                 // If mouse is over btn1
                    Button::list[i]->hovered();
                // On not hovering
                if((state == Button::list[i]->state || Button::list[i]->state == magicNumber) && !Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    Button::list[i]->unhovered();
            }
        }

// HL->MOUSECLICKS:
// ======================== HANDLING MOUSE CLICKS ========================
            if(event.type==sf::Event::MouseButtonPressed){ // <-----------
                if(event.mouseButton.button == sf::Mouse::Left){
                    // std::cout<<"mouse button pressed"<<event.mouseButton.x;
//           ================= FOR SLIDERS =================
                    for(int i=0; i<Slider::list.size(); i++){
                        if((state == Slider::list[i]->state || Slider::list[i]->state == magicNumber) && Slider::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                            // HL-> Add method to be called when a slider is pressed here
                            Slider::list[i]->clicked();
                        }
                    }
                }            
                    
//           ================= FOR BUTTONS' CLICK HANDLING =================
                for(int i=0; i<Button::list.size(); i++){
                    if((state == Button::list[i]->state || Button::list[i]->state == magicNumber) && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                        // HL-> Add method to be called when a button is pressed here
                        Button::list[i]->clicked = true;
                    }
                }
            }
//           ================= FOR BUTTON RELEASE =================           
            if(event.type==sf::Event::MouseButtonReleased){ // <-----------
            // FOR BUTTONS
                for(int i=0; i<Button::list.size(); i++){
                // Checking if the button is being clicked and is in correct state
                    if((state == Button::list[i]->state || Button::list[i]->state == magicNumber) && Button::list[i]->clicked && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                        // HL-> Add method to be called when a button is pressed here
                        (*(Button::list[i]->action))();
                        Button::list[i]->unhovered(); // Unhovering the button
                    }
                }
            // FOR SLIDERS
                for(int i=0; i<Slider::list.size(); i++){
                        Slider::list[i]->unclicked();
                }
            }
            
        }
        for(int i=0; i<Slider::list.size(); i++){
            if((state == Slider::list[i]->state || Slider::list[i]->state == magicNumber) && Slider::list[i]->sliding){
                Slider::list[i]->slide(mouseX);
            }
        }
        
        clear(sf::Color(251, 245, 243));
        // Draw stuff here
        // Only drawing the button if it belongs to the said state
        for(int i=0; i<Button::list.size(); i++){
            if((state == Button::list[i]->state || Button::list[i]->state == magicNumber))
                draw(Button::list[i]);
        }

        for(int i=0; i<Slider::list.size(); i++){
            if((state == Slider::list[i]->state || Slider::list[i]->state == magicNumber)){
                draw(Slider::list[i]);
            }
        }

        display();
    }

    }
};