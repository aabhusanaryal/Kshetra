#pragma once
// #include <SFML/System/String.hpp>

if(event.type == sf::Event::TextEntered){
    for(int i=0; i<Textfield::list.size(); i++){
        if(((state == Textfield::list[i]->state || Textfield::list[i]->state == magicNumber || (Textfield::list[i]->state==oneAndTwo && (state == 1 || state == 2))) || (state == Textfield::list[i]->state || Textfield::list[i]->state == magicNumber)) && Textfield::list[i]->isFocused)
            // if (event.text.unicode < 127 && event.text.unicode > 32){
                // str1 += sf::String((unsigned int)(event.text.unicode));
                if(event.text.unicode != 8){ // unicode 8 is backspace
                    Textfield::list[i]->text += static_cast<char>(event.text.unicode);
                    Textfield::list[i]->setContent(0);
                }
                else if(event.text.unicode == 8){
                    if(Textfield::list[i]->text.length()>0){
                        Textfield::list[i]->text.pop_back();
                        Textfield::list[i]->setContent(1);
                    }
                }
                
            // }
                
    }
}