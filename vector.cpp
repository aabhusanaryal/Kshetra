#include "vector.hpp"

double highestMagn;
int vector::lowerX=0;
int vector::lowerY=0;
int vector::higherX=0;
int vector::higherY=0;

sf::Texture* vector::texture = new sf::Texture;
bool vector::textureLoaded = 0;
vector::vector(int posX,int posY,double (*expressionX)(double,double),double (*expressionY)(double,double),Grid grid){
    this->posX=posX;
    this->posY=posY;
    this->pixelX=grid.returnOrigin().x+(this->posX*grid.returnCellWidth()); //origin set at middle of graph
    this->pixelY=grid.returnOrigin().y-((this->posY*grid.returnCellWidth())); 

    if(!textureLoaded){
        setTexture();
        textureLoaded = 1;
    }
    double magnY=expressionY(this->posX,this->posY); //temp to store value at j component
    double magnX=expressionX(this->posX,this->posY); //temp to store value on i component

    this->magnitude=sqrt(pow(magnX,2)+pow(magnY,2));

    //angle set according to quadrant
    if(magnX>0 && magnY>0) 
        this->angle=-(atan(magnY/magnX)*(180/pi));
    else if(magnX<0 && magnY>0)
        this->angle=-(180+(atan(magnY/magnX)*(180/pi)));
    else if(magnX<0 && magnY<0)
        this->angle=-(180+(atan(magnY/magnX)*(180/pi)));
    else if(magnX>0 && magnY<0)
        this->angle=-(360+(atan(magnY/magnX)*(180/pi)));
    else if(magnX==0){
        if(magnY>0){this->angle=-90;}
        else if(magnY<0){this->angle=90;}
    }
    else if(magnY==0){
        if(magnX>0){this->angle=0;}
        else if(magnX<0){this->angle=-180;}
    }
    if(magnitude!=0){
        sprite.setTexture(*(texture));
        sprite.setPosition(pixelX,pixelY);
        sprite.setRotation(angle);
        sprite.setOrigin(0,12);
    }
}

void vector::displayArrow(sf::RenderWindow& window){
    window.draw(sprite);
}


void vector::setHighest(std::vector<vector*>& arrows){
    highestMagn=arrows[0]->magnitude;
    for(int i=0;i<arrows.size();i++){
        if(arrows[i]->magnitude>highestMagn){highestMagn=arrows[i]->magnitude;}
    }
}

void vector::setColor(std::vector<vector*>& arrows){
    sf::Color dark(255, 0, 0);
    sf::Color light(0, 0, 255);
    for(int i=0;i<arrows.size();i++){
        double scalar=(arrows[i]->magnitude/highestMagn);
        arrows[i]->arrowColor=sf::Color((scalar*dark.r)+((1-scalar)*light.r),(scalar*dark.g)+((1-scalar)*light.g), (scalar*dark.b)+((1-scalar)*light.b));
        arrows[i]->sprite.setColor(arrows[i]->arrowColor);
    }
}

void vector::setLimits(Grid grid){
    lowerX=-(grid.returnCellCol()/2)-1;
    lowerY=-(grid.returnCellRow()/2)-1;
    higherX=(grid.returnCellCol()/2)+1;
    higherY=(grid.returnCellRow()/2)+1;
}

void vector::setTexture(){
    texture->loadFromFile("./assets/one_Arrow.png");
}

void vector::hovered(){
    sprite.setColor(sf::Color(0,0,0));
}

void vector::unhovered(){
    sprite.setColor(arrowColor);
}