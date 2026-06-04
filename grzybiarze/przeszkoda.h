#ifndef PRZESZKODA_H
#define PRZESZKODA_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
#include <iostream>
class Przeszkoda : public Object
{
    public:
    Przeszkoda(sf::RenderWindow& window) :
            window(window)
{
    sf::FloatRect rb = getGlobalBounds();
    tekstura.loadFromFile("./drzewo.png");
    setTexture(tekstura);
    setPosition(rand()%window.getSize().x-rb.width, rand()%window.getSize().y-rb.height);
    setScale(0.3, 0.3);

}

sf::FloatRect get_korzenie() //zwraca pozycje korzeni drzewa
{
     sf::FloatRect rb = getGlobalBounds();
    return sf::FloatRect(sf::Vector2f(rb.left+rb.width*0.4,rb.top+0.8*rb.height),sf::Vector2f(0.2*rb.width,0.2*rb.height));
}

private:
sf::Texture tekstura;
sf::RenderWindow& window;
sf::FloatRect korzenie(sf::Vector2f a,sf::Vector2f b);
friend class CMap;
};

#endif // PRZESZKODA_H
