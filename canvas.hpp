#include "vector.hpp"

typedef double (*doublePointerFn)(double, double);

class canvas{
    public:
        static std::vector<canvas*> list;
        int state;
        std::vector<vector*> arrows;
        Grid grid;
        canvas(int,int,double (*expressionX)(double,double),double (*expressionY)(double,double), int state);
        void reinitialiseVectors(double (*expressionX)(double,double),double (*expressionY)(double,double));
        void reinitialiseGrid(float =22.f);
        doublePointerFn fnX, fnY;
};