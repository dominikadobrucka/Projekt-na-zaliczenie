#include "rules_page.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

RulesPage::RulesPage(sf::RenderWindow& window, sf::Event ev)
    : window(window), event(ev)
{
    font.loadFromFile("pixel.ttf");

    przycisk_powrot.setFont(font);
    przycisk_powrot.setString("<- POWROT");
    przycisk_powrot.setCharacterSize(40);
    przycisk_powrot.setFillColor(sf::Color::Red);
    przycisk_powrot.setPosition(50.f, window.getSize().y - 80.f);
}

void RulesPage::draw_everything()
{
    window.clear(sf::Color::Black);

    static sf::Texture rules_bg_tex;
    static sf::Sprite rules_bg;
    static bool texture_loaded = false;

    if (!texture_loaded)
    {
        if (rules_bg_tex.loadFromFile("./zasady.png")) 
        {
            rules_bg.setTexture(rules_bg_tex);
            float scaleX = static_cast<float>(window.getSize().x) / rules_bg_tex.getSize().x;
            float scaleY = static_cast<float>(window.getSize().y) / rules_bg_tex.getSize().y;
            rules_bg.setScale(scaleX, scaleY);
            texture_loaded = true;
        }
    }

    if (texture_loaded)
    {
        window.draw(rules_bg);
    }

    window.draw(przycisk_powrot);
}

int RulesPage::check_click(sf::Vector2i mouse_pos)
{
    sf::Vector2f mouse_f;
    mouse_f.x = static_cast<float>(mouse_pos.x) * (window.getDefaultView().getSize().x / window.getSize().x);
    mouse_f.y = static_cast<float>(mouse_pos.y) * (window.getDefaultView().getSize().y / window.getSize().y);
    
    if(przycisk_powrot.getGlobalBounds().contains(mouse_f)) {
        return 1;
    }
    return 0;
}