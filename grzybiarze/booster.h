#ifndef BOOSTER_H
#define BOOSTER_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
class Booster : public Object
{
public:
    Booster(sf::RenderWindow& window) :
        window(window)
    {
        //sf::FloatRect rectangle_bounds = getGlobalBounds();
        tekstura.loadFromFile("./booster.png");
        setTexture(tekstura);
        setPosition((rand()%window.getSize().x)-100, (rand()%window.getSize().y)-100);
        setScale(0.02, 0.02);
    }
    ~Booster(){};
private:
    sf::RenderWindow& window;
    sf::Texture tekstura;
    friend class Cmap;
};

#endif // BOOSTER_H
