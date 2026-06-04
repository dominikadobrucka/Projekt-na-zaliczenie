#ifndef BUSH_H
#define BUSH_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
class Bush: public Object
{
public:
    Bush(sf::RenderWindow& window) :
        window(window)
    {
        sf::FloatRect rectangle_bounds = getGlobalBounds();
        tekstura.loadFromFile("./krzak.jpeg");
        setTexture(tekstura);
        setPosition(rand()%window.getSize().x-rectangle_bounds.width, rand()%window.getSize().y-rectangle_bounds.height);
        setScale(0.05, 0.05);
    }
private:
    sf::Texture tekstura;
    sf::RenderWindow& window;
};

#endif // BUSH_H
