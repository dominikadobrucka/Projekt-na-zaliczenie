#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
#include <string> 

class Mushroom : public Object {
public:
    Mushroom(sf::RenderWindow& window);
    int Get_points();
    std::string Get_type(); 

private:
    int points_for;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    std::string mushroom_type; 
    friend class Cmap;
};

#endif // MUSHROOM_H
