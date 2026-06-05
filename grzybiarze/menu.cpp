#include "menu.h"

Menu::Menu(sf::RenderWindow& window, sf::Event ev): window(window), event(ev){
    bg_tex.loadFromFile("./menu_bg.png");
    bg.setTexture(bg_tex);
    bg.setScale(window.getSize().x/bg.getGlobalBounds().width,window.getSize().y/bg.getGlobalBounds().height);
    button = new Button(window);
}
void Menu::draw_everything()
{
    window.clear(sf::Color::Black);
    window.draw(bg);
    window.draw(*button);
}

void Menu::check_updates()
{
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

/*
bool Menu::is_button_clicked(sf::Vector2i myszka)
{
    sf::FloatRect box = button->getGlobalBounds();
    if(box.contains((float)(sf::Mouse::getPosition().x),(float)(sf::Mouse::getPosition().y)))
    {
        return true;
    }
    else {return false;}
}
*/