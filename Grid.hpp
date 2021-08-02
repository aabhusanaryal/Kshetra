#include "SFML/Graphics.hpp"

class Grid
{
private:
    sf::RectangleShape bg;
    int paddingRight = 20;
    int windowWidth;
    int windowHeight;
    int width = 700;
    int height = 700;
    int cellWidth,cellHeight,cellCol,cellRow;
    std::vector<sf::RectangleShape> cells;
    float topPaddingcell,leftPaddingcell;

public:
    Grid(int=0,int=0);
    void display(sf::RenderWindow& window);
    void make_bg(sf::RenderWindow& window);
    void make_cells();
    float top();
    float right();
    float bottom();
    float left();
    sf::Vector2f returnOrigin();
    int returnCellWidth();
    int returnCellCol();
    int returnCellRow();
};