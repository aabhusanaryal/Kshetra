#include "SFML/Graphics.hpp"
#include "button.h"
#include "slider.h"
#include "window.h"


int state = 0;
int windowWidth = 1080;
int windowHeight = 720;

Window window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");

void changeStateTo1(){
    state = 1;
};
void changeStateTo0(){
    state = 0;
};
void exitProgram(){
    window.close();
};

int main(){
    int mouseX, mouseY;
    
    sf::RectangleShape title(sf::Vector2f(493, 186));
    sf::Texture titleText;
    titleText.loadFromFile("./assets/main_Title.png");
    title.setTexture(&titleText);
    title.setPosition((windowWidth - 493)/2, 150); 

    Button btn_Standard_Functions("main_Std_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+50, 0);
    Button btn_Custom_Functions("main_Custom_Functions", 298, 70, (windowWidth-298)/2, (windowHeight-70)/2+150, 0);
    Button btn_Exit("main_Exit", 62, 62, (windowWidth-60-20), 30, 0);
    Button btn_Back("one_Back", 33, 37, 20, windowHeight-62-20, 1);

    btn_Exit.setAction(exitProgram);
    btn_Standard_Functions.setAction(changeStateTo1);
    btn_Custom_Functions.setAction(changeStateTo1);
    btn_Back.setAction(changeStateTo0);

    Slider slider1(300, 200, 1);
    Slider slider2(300, 500, 1);

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
            for(int i=0; i<Button::list.size(); i++){
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
                    for(int i=0; i<Slider::list.size(); i++){
                        if(state == Slider::list[i]->state && Slider::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                            // HL-> Add method to be called when a slider is pressed here
                            Slider::list[i]->clicked();
                        }
                    }
                }            
                    
//           ================= FOR BUTTONS' CLICK HANDLING =================
                for(int i=0; i<Button::list.size(); i++){
                    if(state == Button::list[i]->state && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
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
                    if(state == Button::list[i]->state && Button::list[i]->clicked && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                        // HL-> Add method to be called when a button is pressed here
                        (*(Button::list[i]->action))();
                    }
                }
            // FOR SLIDERS
                for(int i=0; i<Slider::list.size(); i++){
                        Slider::list[i]->unclicked();
                }
            }
            
        }
        for(int i=0; i<Slider::list.size(); i++){
            if(state == Slider::list[i]->state && Slider::list[i]->sliding){
                Slider::list[i]->slide(mouseX);
            }
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        // Only drawing the button if it belongs to the said state
        for(int i=0; i<Button::list.size(); i++){
            if(state == Button::list[i]->state)
                window.draw(Button::list[i]);
        }

        for(int i=0; i<Slider::list.size(); i++){
            if(state == Slider::list[i]->state){
                window.draw(Slider::list[i]);
            }
        }
        window.draw(title);
        window.display();
    }
}

