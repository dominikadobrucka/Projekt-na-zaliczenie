#ifndef ACHIEVMENTS_PAGE_H
#define ACHIEVMENTS_PAGE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class achievments_page
{
public:
    achievments_page(sf::RenderWindow& window, sf::Event ev);
    void draw_everything();
    int check_click(sf::Vector2i mouse_pos);

private:
    sf::RenderWindow& window;
    sf::Event event;
    sf::Font font;
    sf::Text tytul;
    sf::Text przycisk_powrot;
};

#endif // ACHIEVMENTS_PAGE_H