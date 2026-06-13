#include "achievments_page.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

achievments_page::achievments_page(sf::RenderWindow& window, sf::Event ev)
    : window(window), event(ev)
{
    font.loadFromFile("pixel.ttf");

    tytul.setFont(font);
    tytul.setString("TWOJE OSIAGNIECIA");
    tytul.setCharacterSize(50);
    tytul.setFillColor(sf::Color::White);
    tytul.setPosition(window.getSize().x / 2.f - 260.f, 50.f);

    przycisk_powrot.setFont(font);
    przycisk_powrot.setString("<- POWROT");
    przycisk_powrot.setCharacterSize(40);
    przycisk_powrot.setFillColor(sf::Color::Red);
    przycisk_powrot.setPosition(50.f, window.getSize().y - 80.f);
}

void achievments_page::draw_everything()
{
    window.clear(sf::Color::Black);

    static sf::Texture local_bg_tex;
    static sf::Sprite local_bg;
    static bool texture_loaded = false;

    if (!texture_loaded)
    {
        if (local_bg_tex.loadFromFile("./tloach.png")) 
        {
            local_bg.setTexture(local_bg_tex);
            float scaleX = static_cast<float>(window.getSize().x) / local_bg_tex.getSize().x;
            float scaleY = static_cast<float>(window.getSize().y) / local_bg_tex.getSize().y;
            local_bg.setScale(scaleX, scaleY);
            texture_loaded = true;
        }
    }

    if (texture_loaded)
    {
        window.draw(local_bg);
    }

    window.draw(tytul);
    window.draw(przycisk_powrot);
}

int achievments_page::check_click(sf::Vector2i mouse_pos)
{
    sf::Vector2f mouse_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    
    if(przycisk_powrot.getGlobalBounds().contains(mouse_f)) {
        return 1;
    }
    return 0;
}