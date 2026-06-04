#ifndef CMAP_H
#define CMAP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "booster.h"
#include "bush.h"
#include "character.h"
#include "mushroom.h"
#include "przeszkoda.h"
class CMap
{
public:
    CMap(sf::RenderWindow& window, sf::Event ev,std::string tex) :
        window(window), event(ev)
    {
        for(int i=0; i<4; i++)
            vec_mushrooms.emplace_back(new Mushroom(window)); //dodajemy 4 grzyby do narysowania
        for(int i=0; i<2; i++)
            vec_boosters.emplace_back(new Booster(window)); //dodajemy 2 boostery
        for(int i=0; i<3; i++)
            vec_bushes.emplace_back(new Bush(window)); //dodajemy 3 krzaki
        for(int i=0; i<3; i++)
            vec_przeszkody.emplace_back(new Przeszkoda(window));

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
                my_character->animate(elapsed,'w');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                my_character->animate(elapsed,'s');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                my_character->animate(elapsed,'a');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                my_character->animate(elapsed,'d');
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
        for (auto &s : vec_boosters) //sprawdzamy czy podniesiono booster
        {
            if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
            {
                my_character->add_booster();
                vec_boosters.erase(std::remove(vec_boosters.begin(), vec_boosters.end(), s), vec_boosters.end());;
            }
        }
        for (auto &s : vec_bushes) //sprawdzamy czy podniesiono booster
        {
            if(boundingBox.intersects(s->getGlobalBounds()))
            {
                my_character->set_speed(1000);
            }
            else{my_character->set_speed(2000);}
        }

        for (auto &s : vec_przeszkody) //sprawdzamy czy przechodzimy przez drzewa
        {
            sf::Vector2f p1= sf::Vector2f(boundingBox.left , boundingBox.top);
            sf::Vector2f p2 = sf::Vector2f(boundingBox.left+boundingBox.width,boundingBox.top);
            sf::Vector2f p3 = sf::Vector2f(boundingBox.left,boundingBox.top+boundingBox.height);
            sf::Vector2f p4 = sf::Vector2f(boundingBox.left+boundingBox.width,boundingBox.top+boundingBox.height);

            sf::FloatRect a = s->get_korzenie();

            if(boundingBox.intersects(a))
            {
                //dol
                if(boundingBox.top<a.top
                    && boundingBox.top +boundingBox.height <a.top+a.height
                    && boundingBox.left< a.left+a.width
                    && boundingBox.left+boundingBox.width >a.left)
                {
                    my_character->setPosition(boundingBox.left,a.top-boundingBox.height);
                }
                //gora
                else if(boundingBox.top>a.top
                    && boundingBox .top+boundingBox.height>a.top+a.height
                    && boundingBox.left<a.left+a.width
                    && boundingBox.left + boundingBox.width>a.left)
                {
                    my_character->setPosition(boundingBox.left,a.top+a.height);
                }
                //prawa
                if(boundingBox.left<a.left
                    && boundingBox.left +boundingBox.width<a.left+a.width
                    && boundingBox.top<a.top+a.height
                    && boundingBox.top+boundingBox.height>a.top)
                {
                    my_character->setPosition(a.left-boundingBox.width,boundingBox.top);
                }
                //lewa
                else if(boundingBox.left>a.left
                    && boundingBox.left+boundingBox.width>a.left+a.width
                    && boundingBox.top<a.top+a.height
                    && boundingBox.top+boundingBox.height>a.top)
                {
                    my_character->setPosition(a.left+a.width,boundingBox.top);
                }

            }

        }
    }

    void draw_everything() //rysowanie wszystkich elementow
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
        for (auto &s : vec_bushes)
        {
            window.draw(*s);
        }
        window.draw(*player());
        for (auto &s : vec_przeszkody)
        {
            window.draw(*s);
        }
    }

private:
    sf::RenderWindow& window;
    sf::Sprite background;
    sf::Texture bg_tex;
    Character* my_character;
    std::vector<Mushroom*> vec_mushrooms;
    std::vector<Booster*> vec_boosters;
    std::vector<Przeszkoda*> vec_przeszkody;
    std::vector<Bush*> vec_bushes;
    sf::Event event;
};

#endif // CMAP_H
