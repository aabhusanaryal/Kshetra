#pragma once

if(event.type == sf::Event::KeyPressed){
// For Easter Egg
    // For easter egg
    if(state==2 && StdFn::fnIndex>=4 && StdFn::fnIndex<=6){
        int i = StdFn::fnIndex;
        // For Charge 1
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            StdFn::c1Y += 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            StdFn::c1X -= 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            StdFn::c1Y -= 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            StdFn::c1X += 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }

        // For Charge 2
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            StdFn::c2Y += 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            StdFn::c2X -= 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            StdFn::c2Y -= 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            StdFn::c2X += 1;
            Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
        }
    }
}


if(event.type == sf::Event::TextEntered){
// For text input in textfields
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