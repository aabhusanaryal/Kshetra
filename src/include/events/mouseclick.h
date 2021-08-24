#pragma once

// ======================== HANDLING MOUSE CLICKS ========================
if(event.type==sf::Event::MouseButtonPressed){ // <-----------
    if(event.mouseButton.button == sf::Mouse::Left){
//           ================= FOR SLIDERS =================
        for(int i=0; i<Slider::list.size(); i++){
            if((std::find(Slider::list[i]->state.begin(), Slider::list[i]->state.end(), state) != Slider::list[i]->state.end()) && Slider::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                Slider::list[i]->clicked();
            }
        }
    }            
        
//           ================= FOR BUTTONS' CLICK HANDLING =================
    for(int i=0; i<Button::list.size(); i++){
        if(std::find(Button::list[i]->state.begin(), Button::list[i]->state.end(), state) != Button::list[i]->state.end() && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            Button::list[i]->clicked = true;
        }
    }

//           ================= FOR TEXTFIELD' CLICK HANDLING =================
    for(int i=0; i<Textfield::list.size(); i++){ // If clicked on textfield
        if(std::find(Textfield::list[i]->state.begin(), Textfield::list[i]->state.end(), state) != Textfield::list[i]->state.end() && Textfield::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            Textfield::list[i]->focused();
        }
    }

    for(int i=0; i<Textfield::list.size(); i++){ // If clicked outside textfield
        if(std::find(Textfield::list[i]->state.begin(), Textfield::list[i]->state.end(), state) != Textfield::list[i]->state.end() && !Textfield::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            if(Textfield::list[i]->isFocused) // If the text field is focused, change to unfocused
                Textfield::list[i]->unfocused();
        }
    }

}
//           ================= FOR BUTTON RELEASE =================           
if(event.type==sf::Event::MouseButtonReleased){ // <-----------
// FOR BUTTONS
    for(int i=0; i<Button::list.size(); i++){
    // Checking if the button is being clicked and is in correct state
        if(std::find(Button::list[i]->state.begin(), Button::list[i]->state.end(), state) != Button::list[i]->state.end() && Button::list[i]->clicked && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            (*(Button::list[i]->action))();
            Button::list[i]->clicked = false;
            Button::list[i]->unhovered(); // Unhovering the button
        }
    }
// FOR SLIDERS
    for(int i=0; i<Slider::list.size(); i++){
            Slider::list[i]->unclicked();
    }
}

for(int i=0; i<Slider::list.size(); i++){
    if((std::find(Slider::list[i]->state.begin(), Slider::list[i]->state.end(), state) != Slider::list[i]->state.end()) && Slider::list[i]->sliding){
        Slider::list[i]->slide(mouseX);
    }
}