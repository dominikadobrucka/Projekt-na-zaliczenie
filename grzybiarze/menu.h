#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "button.h"
class Menu
{
public:
    Menu(sf::RenderWindow& window, sf::Event ev);
    void draw_everything();
    void check_updates();
    //bool is_button_clicked(sf::Vector2i myszka);

private:
    sf::RenderWindow& window;
    sf::Event event;
    Button* button;
    sf::Sprite bg;
    sf::Text tekst1;
    sf::Texture bg_tex;
    //sf::Texture button_tex;
};

#endif // MENU_H
