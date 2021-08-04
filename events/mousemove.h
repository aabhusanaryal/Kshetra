#pragma once

// HL->MOUSEMOVE:
// ======================== HANDLING MOUSE MOVES ========================
if(event.type==sf::Event::MouseMoved){ // If mouse is moved
    mouseX = event.mouseMove.x;
    mouseY = event.mouseMove.y;
//           ================= FOR BUTTONS' HOVER ANIMATION =================
for(int i=0; i<Button::list.size(); i++){
    // On hover
    if(((state == Button::list[i]->state || Button::list[i]->state == magicNumber || (Button::list[0]->state==oneAndTwo && (state == 1 || state == 2))) || (state == Button::list[i]->state || Button::list[i]->state == magicNumber) == magicNumber)&& Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y))
        // If mouse is over btn1
        Button::list[i]->hovered();
    // On not hovering
    if((state == Button::list[i]->state || Button::list[i]->state == magicNumber || (Slider::list[0]->state==oneAndTwo && (state == 1 || state == 2))) && !Button::list[i]->rect.contains(event.mouseMove.x, event.mouseMove.y)) // If mouse is over btn1
        Button::list[i]->unhovered();
}
}
