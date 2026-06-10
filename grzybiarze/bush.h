#ifndef BUSH_H
#define BUSH_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
class Bush: public Object
{
public:
    Bush(sf::RenderWindow& window);
private:
    sf::Texture tekstura;
    sf::RenderWindow& window;
};

#endif // BUSH_H
