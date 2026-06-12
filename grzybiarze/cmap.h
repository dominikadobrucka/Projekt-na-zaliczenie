#ifndef CMAP_H
#define CMAP_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "booster.h"
#include "bush.h"
#include "character.h"
#include "mushroom.h"
#include "przeszkoda.h"
#include <algorithm>
#include "audio.h"

class CMap
{
public:
    CMap(sf::RenderWindow& window, sf::Event ev);
    void check_updates(sf::Time elapsed,double game_timer);
    void check_collisions(GameAudio& audio);
    void draw_everything();
    void save_data();
    void reset();

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
    sf::Text* my_timer;
};

#endif 
