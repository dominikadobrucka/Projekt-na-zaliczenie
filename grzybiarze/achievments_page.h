#ifndef ACHIEVMENTS_PAGE_H
#define ACHIEVMENTS_PAGE_H

#include <SFML/Graphics.hpp>

class achievments_page {
private:
    sf::RenderWindow& window;
    sf::Event& event;
    sf::Font font;
    sf::Text tytul;
    sf::Text przycisk_powrot;

    sf::Texture ach_bg_tex;
    sf::Sprite ach_bg;

public:
    achievments_page(sf::RenderWindow& window, sf::Event ev);
    void draw_everything();
    int check_click(sf::Vector2i mouse_pos);
};

#endif