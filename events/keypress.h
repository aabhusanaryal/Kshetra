#pragma once

if(event.type == sf::Event::KeyPressed){
    for(int i=0; i<Textfield::list.size(); i++){
        if(((state == Textfield::list[i]->state || Textfield::list[i]->state == magicNumber || (Textfield::list[i]->state==oneAndTwo && (state == 1 || state == 2))) || (state == Textfield::list[i]->state || Textfield::list[i]->state == magicNumber)) && Textfield::list[i]->isFocused)
            if (event.text.unicode < 128)
                std::cout<<static_cast<char>(event.text.unicode);
    }
}