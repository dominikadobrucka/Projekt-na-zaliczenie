#ifndef CMAP_H
#define CMAP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "character.h"
#include "mushroom.h"
#include "bush.h"
#include "booster.h"
#include "przeszkoda.h"
#include "audio.h"

class Cmap {
public:
    Cmap(sf::RenderWindow& window, sf::Event& event);
    void draw_everything();
    bool check_updates(sf::Time elapsed, double game_timer, GameAudio& audio);
    void check_collisions(GameAudio& audio);
    void reset();
    void save_data();
    int podajPunkty() {
        return punkty_gracza;
    }
   
    bool achi_perfekcjonista = false;
    bool achi_halucynek = false;
    bool achi_sprinter = false;
    int wejscia_w_krzaki = 0;
    int zjedzone_dobre = 0;
    int zjedzone_zle = 0;
    bool bylem_w_krzaku = false;

private:
    sf::RenderWindow& window;
    sf::Event& event;
    Character* my_character;
    std::vector<Mushroom*> vec_mushrooms;
    std::vector<Bush*> vec_bushes;
    std::vector<Booster*> vec_boosters;
    std::vector<Przeszkoda*> vec_przeszkody;

    sf::Texture t_tlo;
    sf::Sprite s_tlo;
    sf::Texture bg_tex;
    sf::Sprite background;

    sf::Font timer_font;     
    sf::Text timer_text;     
    double total_game_time = 120.0; 

    double slow_timer = 0.0;

    sf::Text game_over_text; 
    bool game_over = false;  
    int jadalne_na_mapie = 0;
    sf::Texture timer_tex;
    sf::Sprite timer_sprite;
    sf::Texture points_tex;
    sf::Sprite points_sprite;
    int punkty_gracza = 0;

    sf::RectangleShape haze_overlay;
};

#endif // CMAP_H