#include "menu.h"

Menu::Menu(sf::RenderWindow& window, sf::Event ev): window(window), event(ev){

    bg_tex.loadFromFile("./menu_bg.png");
    bg.setTexture(bg_tex);
    bg.setScale(window.getSize().x/bg.getGlobalBounds().width, window.getSize().y/bg.getGlobalBounds().height);


    button = new Button(window);


    font_menu.loadFromFile("pixel.ttf");
    przycisk_osiagniecia.setFont(font_menu);
    przycisk_osiagniecia.setString("OSIAGNIECIA");
    przycisk_osiagniecia.setCharacterSize(60);
    przycisk_osiagniecia.setFillColor(sf::Color::Yellow);


    przycisk_osiagniecia.setPosition(400.f, 800.f);
}

void Menu::draw_everything()
{
    window.clear(sf::Color::Black);
    window.draw(bg);
    window.draw(*button);
    window.draw(przycisk_osiagniecia);
}

void Menu::check_updates()
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

int Menu::check_click(sf::Vector2i mouse_pos)
{
    sf::Vector2f mouse_f(mouse_pos.x, mouse_pos.y);

    // Kliknięcie w stary przycisk (GRAJ -> zwraca 2)
    if(button->getGlobalBounds().contains(mouse_f)) {
        return 2;
    }
    // Kliknięcie w nowy napis (OSIĄGNIĘCIA -> zwraca 3)
    if(przycisk_osiagniecia.getGlobalBounds().contains(mouse_f)) {
        return 3;
    }

    return 0; // Nic nie kliknięto
}