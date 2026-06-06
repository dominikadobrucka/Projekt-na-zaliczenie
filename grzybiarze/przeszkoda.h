#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"

class Przeszkoda : public Object
{
    public:
    Przeszkoda(sf::RenderWindow& window) :
            window(window)
{
    sf::FloatRect rb = getGlobalBounds();
    tekstura.loadFromFile("./drzewo.png");
    setTexture(tekstura);
    setPosition(rand()%(int)(window.getSize().x-rb.width), rand()%(int)(window.getSize().y-rb.height));
    setScale(0.3, 0.3);

}

sf::FloatRect getGlobalBounds(){  //nadpisuje getGlobalBounds zeby zwracala obszar korzeni
    sf::FloatRect rb = Object::getGlobalBounds();
    return sf::FloatRect(sf::Vector2f(rb.left+rb.width*0.4,rb.top+0.8*rb.height),sf::Vector2f(0.2*rb.width,0.2*rb.height));
};

private:
sf::Texture tekstura;
sf::RenderWindow& window;
friend class CMap;
};

#endif // PRZESZKODA_H
