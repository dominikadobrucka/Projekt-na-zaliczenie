#ifndef CMAP_H
#define CMAP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "booster.h"
#include "character.h"
#include "mushroom.h"
class CMap
{
public:
    CMap(sf::RenderWindow& window, sf::Event ev,std::string tex) :
        window(window), event(ev)
    {
        for(int i=0; i<4; i++)
            vec_mushrooms.emplace_back(new Mushroom(window)); //dodajemy 4 grzyby do narysowania
        for(int i=0; i<2; i++)
            vec_boosters.emplace_back(new Booster(window)); //dodajemy 4 grzyby do narysowania

        my_character = new Character(sf::Vector2f(3000, 3000), window);

        bg_tex.loadFromFile("./grass.png");
        bg_tex.setRepeated(true);
        background.setTexture(bg_tex);
        background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    }

    Character* player()
    {
        return my_character;
    }

    void check_updates(sf::Time elapsed)
    {
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //chodzenie WSAD lub strzałki
                player()->animate(elapsed,'w');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                player()->animate(elapsed,'s');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                player()->animate(elapsed,'a');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player()->animate(elapsed,'d');
            }
        }
    }

    void pick_mushrooms() //sprawdzamy czy postac dotyka grzybka, jesli tak to go usuwamy z wektora
    {
        sf::FloatRect boundingBox = my_character->getGlobalBounds();
        for (auto &s : vec_mushrooms)
        {
            if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
            {
                my_character->add_points(s->Get_points());
                vec_mushrooms.erase(std::remove(vec_mushrooms.begin(), vec_mushrooms.end(), s), vec_mushrooms.end());;
            }
        }
        for (auto &s : vec_boosters)
        {
            if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
            {
                vec_boosters.erase(std::remove(vec_boosters.begin(), vec_boosters.end(), s), vec_boosters.end());;
            }
        }
    }

    void draw_everything()
    {
        window.clear(sf::Color::Black);
        window.draw(background);
        for (auto &s : vec_mushrooms)
        {
            window.draw(*s);
        }
        for (auto &s : vec_boosters)
        {
            window.draw(*s);
        }
        window.draw(*player());
    }

private:
    sf::RenderWindow& window;
    sf::Sprite background;
    sf::Texture bg_tex;
    Character* my_character;
    std::vector<Mushroom*> vec_mushrooms;
    std::vector<Booster*> vec_boosters;
    sf::Event event;
};

#endif // CMAP_H
