#pragma once

// ======================== HANDLING MOUSE MOVES ========================
if(event.type==sf::Event::MouseMoved){ // If mouse is moved
    mouseX = event.mouseMove.x; // mouseX and mouseY are Window's data members
    mouseY = event.mouseMove.y;
//           ================= FOR BUTTONS' HOVER ANIMATION =================
for(int i=0; i<Button::list.size(); i++){
    // On hover
    if(std::find(Button::list[i]->state.begin(), Button::list[i]->state.end(), state) != Button::list[i]->state.end() && Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y))
        // If mouse is over button
        Button::list[i]->hovered();
    // On not hovering
    if(std::find(Button::list[i]->state.begin(), Button::list[i]->state.end(), state) != Button::list[i]->state.end() && !Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
        Button::list[i]->unhovered();
}

for(int i=0; i<Textfield::list.size(); i++){
    // On hover
    if(std::find(Textfield::list[i]->state.begin(), Textfield::list[i]->state.end(), state) != Textfield::list[i]->state.end() && Textfield::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y))
        // If mouse is over textfield
        Textfield::list[i]->hovered();
    // On not hovering
    if(std::find(Textfield::list[i]->state.begin(), Textfield::list[i]->state.end(), state) != Textfield::list[i]->state.end() && !Textfield::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y)){ // If mouse is over btn1
        if(!Textfield::list[i]->isFocused){ // Dont change to unhovered state if the text field is in focus
            Textfield::list[i]->unhovered();
        }
    }
}
}

//           ================= FOR Vector Arrows' HOVER ANIMATION =================
for(int i=0;i<Canvas::list[0]->arrows.size();i++){
        if((Canvas::list[0]->arrows[i]->sprite.getGlobalBounds().contains(mouseX,mouseY)&& mouseX>525 && mouseX<1174 && mouseY>81 && mouseY<642) && state == 1){
            Canvas::list[0]->arrows[i]->hovered();
        }
        else   
            Canvas::list[0]->arrows[i]->unhovered();
}