#include "vector.hpp"

class canvas{
    public:
        std::vector<vector> arrows;
        Grid grid;
        canvas(int,int,double (*expressionX)(double,double),double (*expressionY)(double,double));
};