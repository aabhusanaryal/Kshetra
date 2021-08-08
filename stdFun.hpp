#pragma once
#include<iostream>
#include"canvas.hpp"

class StdFn{
    public:
        static std::vector<StdFn> fnList;
        static int fnIndex;
        doublePointerFn fnX,fnY;
        std::string eqn,description;

        StdFn(doublePointerFn fnX,doublePointerFn fnY,std::string eqn,std::string desc){
            this->fnX=fnX;
            this->fnY=fnY;
            this->eqn=eqn;
            this->description=desc;
            fnList.push_back(*(this));
        }


};