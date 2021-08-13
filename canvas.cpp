// ===========================================================================
// Usage: Canvas canvasName(posXofGrid, posYofGrid, functionForiComponent, functionForjComponent,state);
// ===========================================================================

// ===================== How this component works =======================
// The Canvas class merges both, the vector and the grid into one unit called a Canvas. The Canvas class has an std::vector of arrows
// and a grid at its core. Instantiating a canvas with the above parameters creates an std::vector of arrows, and initialises
// a grid automatically, with the given values. It also calls setHighest and setColor on the std::vector of arrows. The components
// can be drawn by calling the respective display methods of the arrow and grid which belong to the Canvas.

// Additionally, reinitialiseVectors function can be called to change the function for the vector field.

// Also, reinitialiseGrid redraws the grid when zoomed in, and also reinitialises the arrows for the new limits of the grid. 
// ===========================================================================

#include<window.hpp>
#include<canvas.hpp>

std::vector<Canvas*> Canvas::list;

Canvas::Canvas(int windowWidth,int windowHeight,doublePointerFn expressionX, doublePointerFn expressionY, std::vector<int> state){
    this->fnX = expressionX;
    this->fnY = expressionY; //setting functions for vector field
    list.push_back(this);
    this->state = state;
    grid=Grid(windowWidth,windowHeight, 22); //creating a grid
    grid.makeCells();
    Vector::setLimits(grid);
    for(int i=Vector::lowerX;i<Vector::higherX;i++){
        for(int j=Vector::lowerY;j<Vector::higherY;j++){
            arrows.push_back(new Vector(i,j,fnX,fnY,grid)); //creating collection of arrows, according to limits
        }
    }
    Vector::setHighest(arrows);
    Vector::setColor(arrows); 
}

void Canvas::reinitialiseVectors(doublePointerFn expressionX, doublePointerFn expressionY){
    fnX = expressionX;
    fnY = expressionY;
    arrows.clear();
    for(int i=Vector::lowerX;i<Vector::higherX;i++){
        for(int j=Vector::lowerY;j<Vector::higherY;j++){
            arrows.push_back(new Vector(i,j,expressionX,expressionY,grid));
        }
    }
    Vector::setColor(arrows);
}

void Canvas::reinitialiseGrid(float scalar){
    // HL-> Need to un-hardcode windowWidth and windowHeight
    grid=Grid(510, 18, scalar);
    grid.makeCells();
    Vector::setLimits(grid);
    reinitialiseVectors(fnX, fnY);
}