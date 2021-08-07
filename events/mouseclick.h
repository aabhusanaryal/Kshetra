// HL->MOUSECLICKS:
// ======================== HANDLING MOUSE CLICKS ========================
if(event.type==sf::Event::MouseButtonPressed){ // <-----------
    if(event.mouseButton.button == sf::Mouse::Left){
        // std::cout<<"mouse button pressed"<<event.mouseButton.x;
//           ================= FOR SLIDERS =================
        for(int i=0; i<Slider::list.size(); i++){
            if((state == Slider::list[i]->state || Slider::list[i]->state == magicNumber || (Slider::list[0]->state==oneAndTwo && (state == 1 || state == 2))) && Slider::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
                // HL-> Add method to be called when a slider is pressed here
                Slider::list[i]->clicked();
            }
        }
    }            
        
//           ================= FOR BUTTONS' CLICK HANDLING =================
    for(int i=0; i<Button::list.size(); i++){
        if((state == Button::list[i]->state || Button::list[i]->state == magicNumber || (Button::list[0]->state==oneAndTwo && (state == 1 || state == 2))) && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            Button::list[i]->clicked = true;
        }
    }

//           ================= FOR TEXTFIELD' CLICK HANDLING =================
    for(int i=0; i<Textfield::list.size(); i++){ // If clicked on textfield
        if((state == Textfield::list[i]->state || Textfield::list[i]->state == magicNumber || (Textfield::list[0]->state==oneAndTwo && (state == 1 || state == 2))) && Textfield::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            Textfield::list[i]->focused();
        }
    }

    for(int i=0; i<Textfield::list.size(); i++){ // If clicked outside textfield
        if((state == Textfield::list[i]->state || Textfield::list[i]->state == magicNumber || (Textfield::list[0]->state==oneAndTwo && (state == 1 || state == 2))) && !Textfield::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            if(Textfield::list[i]->isFocused) // If the text field is focused, change to unfocused
                Textfield::list[i]->unfocused();
        }
    }

}
//           ================= FOR BUTTON RELEASE =================           
if(event.type==sf::Event::MouseButtonReleased){ // <-----------
// FOR BUTTONS
    std::cout<<"("<<mouseX<<","<<mouseY<<")\n";
    for(int i=0; i<Button::list.size(); i++){
    // Checking if the button is being clicked and is in correct state
        if((state == Button::list[i]->state || Button::list[i]->state == magicNumber || ((Button::list[0]->state==oneAndTwo && (state == 1 || state == 2)))) && Button::list[i]->clicked && Button::list[i]->rect.contains(event.mouseButton.x, event.mouseButton.y)){
            // HL-> Add method to be called when a button is pressed here
            (*(Button::list[i]->action))();
            if(!Button::list[i]->rect.contains(mouseX, mouseY))
                Button::list[i]->unhovered(); // Unhovering the button
        }
    }
// FOR SLIDERS
    for(int i=0; i<Slider::list.size(); i++){
            Slider::list[i]->unclicked();
    }
}

for(int i=0; i<Slider::list.size(); i++){
    if((state == Slider::list[i]->state || Slider::list[i]->state == magicNumber || ((Slider::list[0]->state==oneAndTwo && (state == 1 || state == 2)))) && Slider::list[i]->sliding){
        Slider::list[i]->slide(mouseX);
    }
}