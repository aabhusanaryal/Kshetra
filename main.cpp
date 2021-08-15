#include "SFML/Graphics.hpp"
#include<button.hpp>
#include<slider.hpp>
#include<textfield.hpp>
#include<window.hpp>
#include<text.hpp>
#include<vector.hpp>
#include<canvas.hpp>
#include<parser.hpp>
#include<commonfunctions.hpp>
#include <commonfunctionslist.hpp>
#include <math.h>

// ============ States ============
// 0. Main Menu                   ||
// 1. Custom Functions           ||
// 2. Demo Functions        ||
// =========================== ||

Parser *parseri, *parserj;

// Declaring static member of various classes
std::vector<Text*> Text::list; 
std::vector<StdFn> StdFn::fnList;
Text* Vector::magnValue;
Text* Vector::angleValue;
Text* Vector::posValue;

// currentEqn and currentDescription are the details of the "common/standard function"
// that's currently being displayed 
int StdFn::fnIndex=0;
Text* StdFn::currentEqn = new Text("NA",38,150,295,"Jaldi-bold",{2});
Text* StdFn::currentDescription = new Text("NA",22,150,355,"Roboto-Medium",{2});


//=======================================

int windowWidth = 1280;
int windowHeight = 720;

Window window(sf::VideoMode(windowWidth, windowHeight), "Kshetra", sf::Style::None);

//=======================================
// Functions passed into the canvas as parameter
double fnParserX(double x,double y){
    return parseri->evaluateRPN(x,y);
}
double fnParserY(double x,double y){
    return parserj->evaluateRPN(x,y);
}
//=======================================
// Functions (actions) to be called on button click:
void action_ExitProgram(){ // Exits program
    window.close();
};
void action_PreviousFn(){ // Switches to previous function in Common Functions state
    if(StdFn::fnIndex == 0){
        StdFn::fnIndex =StdFn::fnList.size()-1;
    }
    else{
        StdFn::fnIndex -= 1;
    }
    float chargeSeparation = 5;
    StdFn::c1X = -5;
    StdFn::c1Y = 0;
    StdFn::c2X = 5;
    StdFn::c2Y = 0;
    int i = StdFn::fnIndex;
    StdFn::currentEqn->setString(StdFn::fnList[StdFn::fnIndex].eqn);
    StdFn::currentDescription->setString(StdFn::fnList[StdFn::fnIndex].description);
    Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
};

void action_NextFn(){ // Switches to next function in Common Functions state
    if(StdFn::fnIndex ==StdFn::fnList.size()-1){
        StdFn::fnIndex = 0;
    }
    else{
        StdFn::fnIndex += 1;
    }
    float chargeSeparation = 5;
    StdFn::c1X = -5;
    StdFn::c1Y = 0;
    StdFn::c2X = 5;
    StdFn::c2Y = 0;
    int i = StdFn::fnIndex;
    StdFn::currentEqn->setString(StdFn::fnList[StdFn::fnIndex].eqn);
    StdFn::currentDescription->setString(StdFn::fnList[StdFn::fnIndex].description);
    Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
};

void action_PlotFunction(){ // Plots the given function
// Parser stuff
    delete parseri;
    delete parserj;

    parseri = new Parser();
    parserj = new Parser();

    std::string strExpressioni, strExpressionj;

    strExpressioni = (Textfield::list[0]->text != ""? Textfield::list[0]->text : "0");
    strExpressionj = (Textfield::list[1]->text != ""? Textfield::list[1]->text : "0");
   
    parseri->parse(strExpressioni);
    parserj->parse(strExpressionj);
    
    if(!parseri->syntaxError && !parserj->syntaxError)
        Canvas::list[0]->reinitialiseVectors(fnParserX, fnParserY);
    else{
        if(parseri->syntaxError)
            Textfield::list[0]->error();
        if(parserj->syntaxError)
            Textfield::list[1]->error();
    }
}

void action_CommonFunctions(){ // Changes to the Common Functions state
    int i = StdFn::fnIndex;
    StdFn::currentEqn->setString(StdFn::fnList[StdFn::fnIndex].eqn);
    StdFn::currentDescription->setString(StdFn::fnList[StdFn::fnIndex].description);
    Canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
    window.state = 2;
};

void action_MainMenu(){ // Changes to the MainMenu state
    window.state = 0;
};

void action_CustomFunctions(){ // Changes to the Custom Functions state
    action_PlotFunction();
    window.state = 1;
};

int main(){
// Setting app icon
    sf::Image icon;
    icon.loadFromFile("./assets/icon.png");
    window.setIcon(icon.getSize().x,icon.getSize().y, icon.getPixelsPtr());
//Initialising Common Functions
    StdFn std1(std1X, std1Y,"Fx = -y\nFy = x","Curl");
    StdFn std2(std2X, std2Y,"Fx = 1/r*cos(p)\nFy = 1/r*sin(p))\n p = arctan(y/x)","Positive charge at O");
    StdFn std3(std3X, std3Y,"Fx = -x\nFy = -y","Sink");
    StdFn std4(std4X, std4Y,"Fx = x\nFy = y","Source");
    StdFn std5(std5X, std5Y,"Fx = (x-5)^2/((x-5)^2 +y^2)\nFy = y^2/((x-5)^2 +y^2)\n\nTwo positive charges","Interaction of Charges");
    StdFn std7(std7X, std7Y,"Fx = -(x-5)^2/((x-5)^2 -y^2)\nFy = -y^2/((x-5)^2 -y^2)\n\nTwo negative charges","Interaction of Charges");
    StdFn std6(std6X, std6Y,"Fx = (x-5)^2/((x-5)^2 +y^2)\nFy =-y^2/((x-5)^2-y^2)\n\nPositive and Negative Charges","Interaction of Charges");

    StdFn::currentEqn->setString(StdFn::fnList[StdFn::fnIndex].eqn);
    StdFn::currentDescription->setString(StdFn::fnList[StdFn::fnIndex].description);
// Initializing components:
    // State 0 [Main Menu] components
    Button btn_Custom_Functions("Custom Functions", Button::showLabel, 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+50, {0});
    Button btn_Common_Functions("Common Functions", Button::showLabel, 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+150, {0});
    Button btn_Exit("main_Exit", Button::hideLabel, 62, 62, (windowWidth-62)-20, 20, {0, 1, 2});
    Button btn_Back("one_Back", Button::hideLabel, 33, 37, 22, 665, {1, 2});
    // State 1 [Custom Functions] components:
    Textfield fx("Fx",201, 54, 165, 345-52, {1});
    Textfield fy("Fy",201, 54, 165, 418-52, {1});
    Button btn_Plot("Plot", Button::showLabel, 183, 47, 171, 495-52, {1});
    Slider slider1(727, 685, {1,2});
    Canvas canvas(510, window.height/2-350+8, std1X, std1Y, {1, 2});

    Text* magnitude=new Text("Magnitude:",18,131,571,{1});
    Text* angle=new Text("Angle:",18,131,598,{1});
    Text* position=new Text("Position:",18,131,625,{1});
    Text* function=new Text("Enter Function",36,131,238,"Jaldi-Bold",{1});
    Text* details=new Text("Details:",36,131,529,"Jaldi-Bold",{1});
    
    Vector::magnValue=new Text("NA",18,225,571,{1});
    Vector::angleValue=new Text("NA",18,185,598,{1});
    Vector::posValue=new Text("NA",18,205,625,{1});
    // State 2 [Common Functions] components
    Button btnPrevious("two_Arrow_Left", Button::hideLabel, 36, 80, 44, window.height/2-40, {2});
    Button btnNext("two_Arrow_Right", Button::hideLabel, 36, 80, window.width-80, window.height/2-40, {2});
    // Assigning functions to be called on button click
    btn_Exit.setAction(action_ExitProgram);
    btn_Common_Functions.setAction(action_CommonFunctions);
    btn_Custom_Functions.setAction(action_CustomFunctions);
    btn_Back.setAction(action_MainMenu);
    btn_Plot.setAction(action_PlotFunction);
    btnPrevious.setAction(action_PreviousFn);
    btnNext.setAction(action_NextFn);

    window.mainLoop();
}