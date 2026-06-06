#ifndef CMAP_H
#define CMAP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "booster.h"
#include "bush.h"
#include "character.h"
#include "mushroom.h"
#include "przeszkoda.h"
#include <algorithm>
class CMap
{
public:
    CMap(sf::RenderWindow& window, sf::Event ev,std::string tex) :
        window(window), event(ev)
    {
        std::vector<Object*> everything;

        my_character = new Character(sf::Vector2f(3000, 3000), window);
        everything.emplace_back(my_character);

        for(int i=0; i<4; i++)//tworzymy grzyby, sprawdzamy czy nie nachodza na inne obiekty
        {
            Mushroom* nowy = new Mushroom(window);
            if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
            {
                vec_mushrooms.emplace_back(nowy);
                everything.emplace_back(nowy);
            }
        }

        for(int i=0; i<2; i++)
        {
            Booster* nowy = new Booster(window);
            if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
            {
                vec_boosters.emplace_back(nowy);
                everything.emplace_back(nowy);
            }
        }

        for(int i=0; i<5; i++)
        {
            Bush* nowy = new Bush(window);
            if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
            {
                vec_bushes.emplace_back(nowy);
                everything.emplace_back(nowy);
            }
        }

        for(int i=0; i<10; i++)
        {
            Przeszkoda* nowy = new Przeszkoda(window);
            if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
            {
                vec_przeszkody.emplace_back(nowy);
                everything.emplace_back(nowy);
            }
        }

        bg_tex.loadFromFile("./grass.png");
        bg_tex.setRepeated(true);
        background.setTexture(bg_tex);
        background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    }

    void check_updates(sf::Time elapsed);
    void check_collisions();
    void draw_everything();
    void save_data()
    {
        my_character->save_data();
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
