#include "achievments_page.h"

achievments_page::achievments_page(sf::RenderWindow& window, sf::Event ev)
    : window(window), event(ev)
{
    font.loadFromFile("pixel.ttf");

    tytul.setFont(font);
    tytul.setString("TWOJE OSIAGNIECIA");
    tytul.setCharacterSize(80);
    tytul.setFillColor(sf::Color::White);
    tytul.setPosition(window.getSize().x / 2.f - 300.f, 50.f);

    przycisk_powrot.setFont(font);
    przycisk_powrot.setString("<- POWROT");
    przycisk_powrot.setCharacterSize(50);
    przycisk_powrot.setFillColor(sf::Color::Red);
    przycisk_powrot.setPosition(50.f, window.getSize().y - 100.f);
}

void achievments_page::draw_everything()
{
    window.clear(sf::Color::Black);
    window.draw(tytul);
    window.draw(przycisk_powrot);
}

int achievments_page::check_click(sf::Vector2i mouse_pos)
{
    sf::Vector2f mouse_f(mouse_pos.x, mouse_pos.y);
    if(przycisk_powrot.getGlobalBounds().contains(mouse_f)) {
        return 1;
    }
    return 0;
}