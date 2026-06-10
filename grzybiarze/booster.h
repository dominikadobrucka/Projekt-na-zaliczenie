#ifndef BOOSTER_H
#define BOOSTER_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
class Booster : public Object
{
public:
    Booster(sf::RenderWindow& window);
private:
    sf::RenderWindow& window;
    sf::Texture tekstura;
    friend class Cmap;
};

#endif // BOOSTER_H
