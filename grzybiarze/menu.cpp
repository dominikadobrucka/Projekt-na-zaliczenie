#include "menu.h"

Menu::Menu(sf::RenderWindow& window, sf::Event ev): window(window), event(ev){

    bg_tex.loadFromFile("./menu_bg.png");
    bg.setTexture(bg_tex);
    bg.setScale(window.getSize().x/bg.getGlobalBounds().width, window.getSize().y/bg.getGlobalBounds().height);

    button = new Button(window);

    button_osiagniecia = new Button(window);
    button_osiagniecia->zmienGrafike("./achprzycisk.png"); 

    float startScaleX = button->getScale().x;
    float startScaleY = button->getScale().y;

    button_osiagniecia->setScale(startScaleX * 1.48f, startScaleY * 1.55f);
    button_osiagniecia->setPosition(button->getPosition().x - 30.f, window.getSize().y * 0.81f);
}

void Menu::draw_everything()
{
    window.clear(sf::Color::Black);
    window.draw(bg);
    window.draw(*button);             
    window.draw(*button_osiagniecia); 
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

    
    if(button->getGlobalBounds().contains(mouse_f)) {
        return 2;
    }
    
    
    sf::FloatRect achi_hitbox = button_osiagniecia->getGlobalBounds();
    
    
    achi_hitbox.left -= 50.f;
    achi_hitbox.width += 100.f;

    if(achi_hitbox.contains(mouse_f)) {
        return 3;
    }

    return 0; 
}