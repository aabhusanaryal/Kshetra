#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "window.h"

#define arrayLength(a) (sizeof(a)/(sizeof(a[0])))

int state = 0;

int main(){
    int windowWidth = 1080;
    int windowHeight = 720;

    int mouseX, mouseY;


    Window window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");


    Button btn1("./assets/main_Std_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2, 0);
    Button btn2("./assets/main_Custom_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+100, 0);
    Button btn3("./assets/main_Custom_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+200, 1);
    

    Slider slider(300, 100, 1);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed) window.close();
// HL->MOUSEMOVE:
// ======================== HANDLING MOUSE MOVES ========================
            if(event.type==sf::Event::MouseMoved){ // If mouse is moved
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
//           ================= FOR BUTTONS' HOVER ANIMATION =================
            for(int i=0; i<arrayLength(Button::list); i++){
                // On hover
                if(state == Button::list[i]->state && Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y))
                 // If mouse is over btn1
                    Button::list[i]->hovered();
                // On not hovering
                if(state == Button::list[i]->state && !Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
                    Button::list[i]->unhovered();
            }
        }

// HL->MOUSECLICKS:
// ======================== HANDLING MOUSE CLICKS ========================
            if(event.type==sf::Event::MouseButtonPressed){ // <-----------
                if(event.mouseButton.button == sf::Mouse::Left){
                    // std::cout<<"mouse button pressed"<<event.mouseButton.x;
//           ================= FOR SLIDERS =================
                    for(int i=0; i<arrayLength(Slider::list); i++){
                        if(state == Slider::list[i]->state && Slider::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                            // HL-> Add method to be called when a slider is pressed here
                            Slider::list[i]->clicked();
                        }
                    }
                }            
                    
//           ================= FOR BUTTONS' CLICK HANDLING =================
                for(int i=0; i<arrayLength(Button::list); i++){
                    if(state == Button::list[i]->state && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                        // HL-> Add method to be called when a button is pressed here
                        std::cout<<1;
                        state = 1;
                    }
                }
            }
            if(event.type==sf::Event::MouseButtonReleased){ // <-----------
                for(int i=0; i<arrayLength(Slider::list); i++){
                    if(state == Slider::list[i]->state && Slider::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                        // HL-> Add method to be called when a slider is unclicked here
                        Slider::list[i]->unclicked();
                    }
                }
            }
            
        }
        for(int i=0; i<arrayLength(Slider::list); i++){
            if(state == Slider::list[i]->state && Slider::list[i]->sliding){
                Slider::list[i]->slide(mouseX);
            }
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        // Only drawing the button if it belongs to the said state
        for(int i=0; i<arrayLength(Button::list); i++){
            if(state == Button::list[i]->state)
                window.draw(Button::list[i]);
        }
// HL-> FIXME: I dont even know what the error is
        for(int i=0; i<1; i++){
            if(state == Slider::list[0]->state){
                Slider::list[0]->draw(window);
            }
        }
        window.display();
    }
}