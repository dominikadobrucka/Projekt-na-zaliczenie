#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Window/Mouse.hpp>
class Button : public sf::Sprite
{
public:
    Button(sf::RenderWindow& window);

private:
    sf::Texture button_tex;
    sf::RenderWindow& window;
};

#endif // BUTTON_H
