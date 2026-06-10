#include "przeszkoda.h"

Przeszkoda::Przeszkoda(sf::RenderWindow& window) :
    window(window)
{
    sf::FloatRect rb = getGlobalBounds();
    tekstura.loadFromFile("./drzewo.png");
    setTexture(tekstura);
    setPosition(rand()%(int)(window.getSize().x-rb.width), rand()%(int)(window.getSize().y-rb.height));
    setScale(0.3, 0.3);

}

sf::FloatRect Przeszkoda::getGlobalBounds(){  //nadpisuje getGlobalBounds zeby zwracala obszar korzeni
    sf::FloatRect rb = Object::getGlobalBounds();
    return sf::FloatRect(sf::Vector2f(rb.left+rb.width*0.4,rb.top+0.8*rb.height),sf::Vector2f(0.2*rb.width,0.2*rb.height));
};