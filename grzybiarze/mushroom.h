#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"

class Mushroom : public Object{
public:
    Mushroom(sf::RenderWindow& window);
    int Get_points();
private:
    int points_for;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    friend class Cmap;
};

#endif // MUSHROOM_H
