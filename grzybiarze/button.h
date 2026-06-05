#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Window/Mouse.hpp>
class Button : public sf::Sprite
{
public:
    Button(sf::RenderWindow& window): window(window){
        button_tex.loadFromFile("./button.png");
        setTexture(button_tex);
        setScale(window.getSize().x/getGlobalBounds().width*0.2,0.2);
        setPosition(window.getSize().x*0.4,window.getSize().y*0.7);
    }

private:
    sf::Texture button_tex;
    sf::RenderWindow& window;
};

#endif // BUTTON_H
