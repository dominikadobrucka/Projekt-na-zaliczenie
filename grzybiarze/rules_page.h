#ifndef RULES_PAGE_H
#define RULES_PAGE_H

#include <SFML/Graphics.hpp>

class RulesPage {
private:
    sf::RenderWindow& window;
    sf::Event& event;
    sf::Font font;
    sf::Text przycisk_powrot;

public:
    RulesPage(sf::RenderWindow& window, sf::Event ev);
    void draw_everything();
    int check_click(sf::Vector2i mouse_pos);
};

#endif