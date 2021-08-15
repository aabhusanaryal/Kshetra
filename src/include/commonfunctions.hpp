#pragma once
#include<iostream>
#include<canvas.hpp>

class StdFn{
    public:
        static std::vector<StdFn> fnList;
        static int fnIndex;
        static int c1X;
        static int c1Y;
        static int c2X;
        static int c2Y;
        static Text *currentEqn;
        static Text *currentDescription;
        doublePointerFn fnX,fnY;
        std::string eqn,description;

        StdFn(doublePointerFn fnX,doublePointerFn fnY,std::string desc, std::string eqn){
            this->fnX=fnX;
            this->fnY=fnY;
            this->eqn=eqn;
            this->description=desc;
            fnList.push_back(*(this));
        }
};