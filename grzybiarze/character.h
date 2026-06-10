#ifndef CHARACTER_H
#define CHARACTER_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
#include <iostream>
#include <fstream>
class Character : public Object {
public:
    Character(const sf::Vector2f& velocity, sf::RenderWindow& window);
    void animate(const sf::Time &elapsed, char direction);
    void add_points(int points_to_add);
    void add_booster();
    void set_speed(float v);
    void save_data();
    void reset();

private:
    sf::Vector2f velocity;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    int points;     //obecne punkty w czasie rozgrywki
    int high_score;
    int booster_counter;
    std::vector<bool> achievements;
    friend class Cmap;
    double animation_timer;
};

#endif // CHARACTER_H
