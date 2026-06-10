#include "booster.h"

Booster::Booster(sf::RenderWindow& window) :
    window(window)
{
    //sf::FloatRect rectangle_bounds = getGlobalBounds();
    tekstura.loadFromFile("./booster.png");
    setTexture(tekstura);
    setPosition((rand()%window.getSize().x)-100, (rand()%window.getSize().y)-100);
    setScale(0.02, 0.02);
}
