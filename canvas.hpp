#include "vector.hpp"

class canvas{
    public:
        static std::vector<canvas*> list;
        int state;
        std::vector<vector> arrows;
        Grid grid;
        canvas(int,int,double (*expressionX)(double,double),double (*expressionY)(double,double), int state);
};