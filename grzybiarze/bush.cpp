#include "bush.h"

Bush::Bush(sf::RenderWindow& window) :
    window(window)
{
    sf::FloatRect rectangle_bounds = getGlobalBounds();
    tekstura.loadFromFile("./maliny.png");
    setTexture(tekstura);
    setPosition(rand()%window.getSize().x-rectangle_bounds.width, rand()%window.getSize().y-rectangle_bounds.height);
    setScale(0.05, 0.05);
}
