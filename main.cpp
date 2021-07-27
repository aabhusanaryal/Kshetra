#include "SFML/Graphics.hpp"
#include "components.h"
#include "vector.hpp"
#include "canvas.hpp"
#include <vector>

double forX(double x,double y){
    return x;
}

double forY(double x,double y){
    return y;
}

int vector::lowerX=0;
int vector::lowerY=0;
int vector::higherX=0;
int vector::higherY=0;

int windowWidth = 1250;
int windowHeight = 850;

int main(){

    canvas canvas(windowWidth,windowHeight,forX,forY);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");

    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        canvas.grid.display(window);
        for(int i=0;i<canvas.arrows.size();i++){
            canvas.arrows[i].displayArrow(window);
        }
        window.display();
    }
}
