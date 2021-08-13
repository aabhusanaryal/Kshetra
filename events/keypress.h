#pragma once

// For entering text in a Textfield
if(event.type == sf::Event::TextEntered){
    for(int i=0; i<Textfield::list.size(); i++){
        if(std::find(Textfield::list[i]->state.begin(), Textfield::list[i]->state.end(), state) != Textfield::list[i]->state.end() && Textfield::list[i]->isFocused)
                if(event.text.unicode == 8){ // For backspace
                    if(Textfield::list[i]->text.length()>0){
                        Textfield::list[i]->text.pop_back();
                        Textfield::list[i]->setContent(1);
                    }
                } 
                else if(!(std::find(legalChars.begin(), legalChars.end(), event.text.unicode) != legalChars.end()))
                    continue; // only allowing legalChars (defined in window.hpp)
                else if(event.text.unicode != 8){ // unicode 8 is backspace
                    Textfield::list[i]->text += static_cast<char>(event.text.unicode);
                    Textfield::list[i]->setContent(0);
                }
                               
    }
}