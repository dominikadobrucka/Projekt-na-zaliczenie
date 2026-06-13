#include "menu.h"

Menu::Menu(sf::RenderWindow& window, sf::Event ev): window(window), event(ev){

    bg_tex.loadFromFile("./menu_bg.png");
    bg.setTexture(bg_tex);
    bg.setScale(window.getSize().x/bg.getGlobalBounds().width, window.getSize().y/bg.getGlobalBounds().height);

    button = new Button(window);

    button_osiagniecia = new Button(window);
    button_osiagniecia->zmienGrafike("./achprzycisk.png"); 

    button_zasady = new Button(window);
    button_zasady->zmienGrafike("./zasadyprzycisk.png");

    float startScaleX = button->getScale().x;
    float startScaleY = button->getScale().y;

    
    button_osiagniecia->setScale(startScaleX * 1.48f, startScaleY * 1.55f);
    button_zasady->setScale(startScaleX * 1.48f, startScaleY * 1.55f);

    
    button_osiagniecia->setPosition(button->getPosition().x - 0.f, window.getSize().y * 0.81f);
    button_zasady->setPosition(button->getPosition().x + 480.f, window.getSize().y * 0.75f);
}

void Menu::draw_everything()
{
    window.clear();
    window.draw(bg);
    
    
    window.draw(*button);
    window.draw(*button_osiagniecia);

    
    window.draw(*button_zasady);

    
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
    sf::Vector2f mouse_f;
    mouse_f.x = static_cast<float>(mouse_pos.x) * (window.getDefaultView().getSize().x / window.getSize().x);
    mouse_f.y = static_cast<float>(mouse_pos.y) * (window.getDefaultView().getSize().y / window.getSize().y);

    if(button->getGlobalBounds().contains(mouse_f)) {
        return 2;
    }
    
    if(button_osiagniecia->getGlobalBounds().contains(mouse_f)) {
        return 3;
    }

    if(button_zasady->getGlobalBounds().contains(mouse_f)) {
        return 4;
    }

    return 0;
}