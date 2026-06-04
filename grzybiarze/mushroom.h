#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
class Mushroom : public Object{
public:
    Mushroom(sf::RenderWindow& window) :
        points_for(10),window(window)
    {
        sf::FloatRect rectangle_bounds = getGlobalBounds();
        tekstura.loadFromFile("./gzib.png");
        setTexture(tekstura);
        setPosition(rand()%window.getSize().x-rectangle_bounds.width, rand()%window.getSize().y-rectangle_bounds.height);
        setScale(0.05, 0.05);
    }
    ~Mushroom(){};
    int Get_points();
private:
    int points_for;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    friend class Cmap;
};

#endif // MUSHROOM_H
