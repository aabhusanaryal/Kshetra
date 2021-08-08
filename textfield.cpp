#include "./textfield.h"

std::vector<Textfield*> Textfield::list;

Textfield::Textfield(std::string label, int width,int height,int posX, int posY, std::vector<int> state){
    int labelSize = 22; //in pixels not points
    int contentSize = 20; //in pixels not points
    int paddingBottom = 15;
    int paddingRight = 28;
    contentPosX = posX+width-paddingRight;
    contentPosY = (posY+height-contentSize-paddingBottom);
    this->name = new Text(label, labelSize, posX-35, (posY+height/2-labelSize/2-5), "Jaldi-Bold",state);
    this->content = new Text(text, contentSize, contentPosX, contentPosY, state);
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    this->state = state;
    list.push_back(this);


    rectangle = sf::RectangleShape (sf::Vector2f(width, height));
    rectangle.setPosition(posX, posY);
// =========================================================================
// HL->WARNING:
// Rect is NOT the rectange that's being rendered, but rather a rectangular
// space in screen. We need this to check if the button is being hovered on.
// This basically "invisibly wraps" our rectangle
// =========================================================================
    rect = sf::IntRect(posX, posY, width, height);
    // Loading different images in texture
    textureHover.loadFromFile(std::string("./assets/textbox_Hovered.png"));
    textureUnhovered.loadFromFile(std::string("./assets/textbox.png"));
    textureFocused.loadFromFile(std::string("./assets/textbox_Focused.png"));
    textureError.loadFromFile(std::string("./assets/textbox_Error.png"));
    // Setting the initial textureRendered to be the unhovered one
    rectangle.setTexture(&textureUnhovered);
}

void Textfield::hovered(){ // Sets the right texture when the textbox is hovered
    if(!isHovered && !isFocused && !isError){ // Setting texture to textureHover iff it's not already textureHover
        rectangle.setTexture(&textureHover);
        isHovered = 1;
    }
}

void Textfield::unhovered(){ // Sets the right texture when the textbox is not hovered
    if(isHovered && !isFocused && !isError){ // Setting texture to textureUnover iff it's not already textureUnhover
        rectangle.setTexture(&textureUnhovered);
        isHovered = 0;
    }
}

void Textfield::focused(){ // Sets the right texture when the textbox is focused (clicked)
    if(!isFocused){ // Setting texture to textureHover iff it's not already textureHover
        rectangle.setTexture(&textureFocused);
        isFocused = 1;
        isHovered = 0;
        isError = 0;
    }
}

void Textfield::unfocused(){ // Sets the right texture when the textbox is not hovered
    if(isFocused && !isError){ // Setting texture to textureUnover iff it's not already textureUnhover and making sure that there's no error
        rectangle.setTexture(&textureUnhovered);
        isFocused = 0;
    }
}

void Textfield::error(){ // Sets the right texture when the textbox has some error
    if(!isError){ 
        rectangle.setTexture(&textureError);
        isFocused = 0;
        isHovered = 0;
        isError = 1;
    }
}

void Textfield::setContent(bool isBackspace){
    float width = this->content->text.getLocalBounds().width; // Width of text
    // Setting the origin of text to top right to make the text right aligned
    if(!isBackspace)
        this->content->text.setOrigin(width, 0);
    if(isBackspace)
        this->content->text.setOrigin(width-17, 0);
 
    if(this->text.length() < 15) // Over 15 characters will overflow
        this->content->text.setString(text);
    else
        this->content->text.setString(text.substr(this->text.length()-15,15)); // Only displaying the last 15 characters if total char count > 15
}