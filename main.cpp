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
Text* vector::magnValue;
Text* vector::angleValue;
Text* vector::posValue;

// currentEqn and currentDescription are the details of the "common/standard function"
// that's currently being displayed 
int StdFn::fnIndex=0;
Text* StdFn::currentEqn = new Text("NA",40,150,350,"Jaldi-Bold",{2});
Text* StdFn::currentDescription = new Text("NA",22,150,410,"Roboto-Medium",{2});


//=======================================

int windowWidth = 1250;
int windowHeight = 850;

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
    int i = StdFn::fnIndex;
    StdFn::currentEqn->setString(StdFn::fnList[StdFn::fnIndex].eqn);
    StdFn::currentDescription->setString(StdFn::fnList[StdFn::fnIndex].description);
    canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
};

void action_NextFn(){ // Switches to next function in Common Functions state
    if(StdFn::fnIndex ==StdFn::fnList.size()-1){
        StdFn::fnIndex = 0;
    }
    else{
        StdFn::fnIndex += 1;
    }
    int i = StdFn::fnIndex;
    StdFn::currentEqn->setString(StdFn::fnList[StdFn::fnIndex].eqn);
    StdFn::currentDescription->setString(StdFn::fnList[StdFn::fnIndex].description);
    canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
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
        canvas::list[0]->reinitialiseVectors(fnParserX, fnParserY);
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
    canvas::list[0]->reinitialiseVectors(StdFn::fnList[i].fnX, StdFn::fnList[i].fnY);
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
    icon.loadFromFile("./assets/icon.ico");
    window.setIcon(icon.getSize().x,icon.getSize().y, icon.getPixelsPtr());
//Initialising Common Functions
    StdFn std1(std1X, std1Y,"F = (-y, x)","Models circular motion such\nas that of a air molecules\nin a cyclone.");
    StdFn std2(std2X, std2Y,"F = (1/r*cos(phi), 1/r*sin(phi))","Models a positive charge\nat the origin");
    StdFn std3(std3X, std3Y,"F = (-x, -y)","Models a sink.");
    StdFn std4(std4X, std4Y,"F = (x, x)","Models a idk wtf\nthis is.");

    StdFn::currentEqn->setString(StdFn::fnList[StdFn::fnIndex].eqn);
    StdFn::currentDescription->setString(StdFn::fnList[StdFn::fnIndex].description);

// Initialising Button and Slider components
    Button btn_Common_Functions("main_Common_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+50, {0});
    Button btn_Custom_Functions("main_Custom_Functions", 311, 80, (windowWidth-311)/2, (windowHeight-70)/2+170, {0});
    Button btn_Exit("main_Exit", 62, 62, (windowWidth-62)-20, 20, {0, 1, 2});
    Button btn_Back("one_Back", 33, 37, 22, 777, {1, 2});
    

    // State 1 components:
    Button btn_Plot("one_Plot", 183, 47, 171, 495, {1});
    Slider slider1(698, 803, {1,2});
    Textfield fx("Fx",201, 54, 165, 345, {1});
    Textfield fy("Fy",201, 54, 165, 418, {1});
    canvas canvas1(window.width-50, window.height+40, std1X, std1Y, {1, 2});

    Text* magnitude=new Text("Magnitude:",18,131,662,{1});
    Text* angle=new Text("Angle:",18,131,689,{1});
    Text* position=new Text("Position:",18,131,716,{1});
    Text* function=new Text("Enter Function",36,131,290,"Jaldi-Bold",{1});
    Text* details=new Text("Details:",36,131,620,"Jaldi-Bold",{1});
    
    vector::magnValue=new Text("NA",18,225,662,{1});
    vector::angleValue=new Text("NA",18,185,689,{1});
    vector::posValue=new Text("NA",18,205,716,{1});

    // State 2 components
    Button btnPrevious("two_Arrow_Left", 36, 80, 44, 385, {2});
    Button btnNext("two_Arrow_Right", 36, 80, window.width-80, 385, {2});
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