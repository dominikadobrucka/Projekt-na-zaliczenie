#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"

class Przeszkoda : public Object
{
    public:
    Przeszkoda(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

private:
sf::Texture tekstura;
sf::RenderWindow& window;
friend class CMap;
};

#endif // PRZESZKODA_H
