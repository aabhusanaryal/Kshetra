// ===========================================================================
// Usage: Vector vectName(posX, posY, functionForiComponent, functionForjComponent, Grid);
// ===========================================================================

// ===================== How this component works =======================
// When the above constructor is called, the angle, magnitude and pixel positions of a vector are calculated 
// based on the functions passed, and origin provided by the grid. If the magnitude calculated is finite, the sf::sprite of 
// the vector is given an arrow shaped sf::texture and the angle of the sprite is set as calculated.

// Throughput the project, an array of vectors is used. The array is formed by calculating the various parameters at 
// each posX and posY by calling the above constrcutor. The upper and lower limits of posX and posY values are specified 
// by the setLimits function. This array is then passed to the setHighest and setColor functions which set the highest
// magnitude of the array, and then color of each individual array respectively.  

// After drawing using displayArrow, hover and unhover functions are triggered when an arrow is hovered on, or unhovered,
// by polling for mouseMoved event.
// ===========================================================================

#include<vector.hpp>
#include <cmath>

double highestMagn;
int Vector::lowerY=0;
int Vector::lowerX=0;
int Vector::higherX=0;
int Vector::higherY=0;

sf::Texture* Vector::texture = new sf::Texture;
bool Vector::textureLoaded = 0;
Vector::Vector(int posX,int posY,double (*expressionX)(double,double),double (*expressionY)(double,double),Grid grid){
    this->posX=posX;
    this->posY=posY;
    this->pixelX=grid.returnOrigin().x+(this->posX*grid.returnCellWidth()); //Pixel position of vector set according to grid's origin, and cell width
    this->pixelY=grid.returnOrigin().y-((this->posY*grid.returnCellWidth())); 

    if(!textureLoaded){
        setTexture();
        textureLoaded = 1;
    }

    double magnX=expressionX(this->posX,this->posY); //temp variable to store value on i component
    double magnY=expressionY(this->posX,this->posY); //temp variable to store value at j component
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
    if(magnitude!=0 && !std::isnan(magnitude)){ //doesnt set texture if magnitude of a vector is 0 or nan
        sprite.setTexture(*(texture));
        sprite.setPosition(pixelX,pixelY);
        sprite.setRotation(angle);
        sprite.setOrigin(0,12);
    }
}

void Vector::displayArrow(sf::RenderWindow& window){
    window.draw(sprite);
}

void Vector::setHighest(std::vector<Vector*>& arrows){
    highestMagn=0;
    for(int i=0;i<arrows.size();i++){
        if(!std::isnan(arrows[i]->magnitude)){
            if(arrows[i]->magnitude>highestMagn)
                highestMagn=arrows[i]->magnitude;
        }  
    }
}

void Vector::setColor(std::vector<Vector*>& arrows){
    sf::Color dark(255, 0, 0);
    sf::Color light(0, 0, 255);
    for(int i=0;i<arrows.size();i++){
        double scalar=(arrows[i]->magnitude/highestMagn);
        arrows[i]->arrowColor=sf::Color((scalar*dark.r)+((1-scalar)*light.r),(scalar*dark.g)+((1-scalar)*light.g), (scalar*dark.b)+((1-scalar)*light.b));
        arrows[i]->sprite.setColor(arrows[i]->arrowColor);
    }
}

void Vector::setLimits(Grid grid){
    lowerX=-(grid.returnCellCol()/2)-1;
    lowerY=-(grid.returnCellRow()/2)-1;
    higherX=(grid.returnCellCol()/2)+1;
    higherY=(grid.returnCellRow()/2)+1;
}

void Vector::setTexture(){
    texture->loadFromFile("./assets/one_Arrow.png");
    texture->setSmooth(true);
}

std::string Vector::roundNumber(double a){
    std::string b= std::to_string(a);
    char c[10];
    int i=0;
    while(b[i-3]!='.'){
        c[i]=b[i];
        i++;
    }
    c[i]='\0';
    return std::string(c);
}

void Vector::hovered(){
    double angle;
    sprite.setColor(sf::Color(0,0,0));
    
    Vector::magnValue->setString(roundNumber(this->magnitude));
    if(this->angle==90)
        angle=270;
    else if(this->angle==0)
        angle=0;
    else    
        angle=-this->angle;
    Vector::angleValue->setString(roundNumber(angle)+" deg");
    Vector::posValue->setString(("("+std::to_string(int(this->posX))+","+std::to_string(int(this->posY))+")"));
}

void Vector::unhovered(){
    sprite.setColor(arrowColor);
}