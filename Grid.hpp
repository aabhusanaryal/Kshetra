#include "SFML/Graphics.hpp"

class Grid
{
private:
    sf::RectangleShape bg;
    int paddingRight = 10;
    int paddingVertical = 30;
    int windowWidth = 1080;
    int width = windowWidth/2 + 80;
    int windowHeight = 720;
    int height = windowHeight - paddingVertical;

public:
    Grid();
    void display(sf::RenderWindow& window);
    void make_bg(sf::RenderWindow& window);
    void make_cells(sf::RenderWindow& window);
    float top();
    float right();
    float bottom();
    float left();
};