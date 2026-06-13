#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Font.hpp"
#include "button.h"

class Menu
{
public:
    Menu(sf::RenderWindow& window, sf::Event ev);
    void draw_everything();
    void check_updates();
    int check_click(sf::Vector2i mouse_pos);

private:
    sf::RenderWindow& window;
    sf::Event event;
    Button* button;
    Button* button_osiagniecia;
    sf::Sprite bg;
    sf::Texture bg_tex;

    
    sf::Font font_menu;
    sf::Text przycisk_osiagniecia;
    sf::Texture achi_btn_tex;
    sf::Sprite achi_btn_sprite;
};

#endif // MENU_H