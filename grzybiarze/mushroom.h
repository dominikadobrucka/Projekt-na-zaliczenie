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
        tekstura.loadFromFile("./kania.png");
        setTexture(tekstura);
        setPosition(rand()%window.getSize().x-50, rand()%window.getSize().y-50);
        setScale(0.03, 0.03);
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
