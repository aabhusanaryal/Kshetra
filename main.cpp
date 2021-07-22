#include "SFML/Graphics.hpp"
#include "components.h"
#include "vector.hpp"
#include<vector>

double forX(double x,double y){
    return x;
}

double forY(double x,double y){
    return y;
}

int main(){

    std::vector<vector> arrows;
    int windowWidth = 1920;
    int windowHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Kshetra");
    for(int i=lowerX;i<higherX;i++){
        for(int j=lowerY;j<higherY;j++){
            arrows.push_back(vector(i,j,forX,forY));
        }
    }
    
    vector::setHighest(arrows);
    vector::setColor(arrows);
    
    Grid grid;
    std::cout<<"Top: "<<grid.top()<<std::endl;
    std::cout<<"left: "<<grid.left()<<std::endl;
    std::cout<<"bottom: "<<grid.bottom()<<std::endl;
    std::cout<<"right: "<<grid.right()<<std::endl;


    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(251, 245, 243));
        // Draw stuff here
        for(int i=0;i<arrows.size();i++){
            arrows[i].displayArrow(window);
        }
        //window.draw(rect);
        //window.draw(rect2);
        grid.display(window);
        window.display();
    }
}
