#pragma once
#include <vector.hpp>

typedef double (*doublePointerFn)(double, double);

class Canvas{
    public:
        static std::vector<Canvas*> list;
        std::vector<int> state; 
        std::vector<Vector*> arrows;  //collection of vectors (or arrows)
        Grid grid; 
        Canvas(int,int,double (*expressionX)(double,double),double (*expressionY)(double,double), std::vector<int> state);

        //function to reset arrow collection according to new function
        void reinitialiseVectors(double (*expressionX)(double,double),double (*expressionY)(double,double)); 

        //function to reset grid according to new cell size
        void reinitialiseGrid(float =22.f);

        doublePointerFn fnX, fnY;
};