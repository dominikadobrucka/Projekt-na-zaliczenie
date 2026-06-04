#ifndef CHARACTER_H
#define CHARACTER_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "object.h"
#include <iostream>
#include <fstream>
class Character : public Object {
public:
    Character(const sf::Vector2f& velocity, sf::RenderWindow& window) :
        velocity(velocity), window(window), points(0), high_score(0),booster_counter(1),
        is_in_collision_right(false), is_in_collision_left(false), is_in_collision_top(false), is_in_collision_bottom(false)
    {
        std::fstream input_file("./character_data.txt", std::ios::in);
        if (input_file.is_open()) {
            input_file >> high_score;
            while (!input_file.eof()) {
                std::string line;
                input_file >> line;

                if(line[0]=='1')
                {
                    achievements.emplace_back(1);
                }
                else {achievements.emplace_back(0);}
                input_file >>line;
            }
        }
        tekstura.loadFromFile("./postacprzyklad.png");
        setTexture(tekstura);
        setScale(0.3, 0.3);
        setTextureRect(sf::IntRect(0, 0, 150, 190));
        setPosition(300, 300);
    }

    void animate(const sf::Time &elapsed, char direction);
    void add_points(int points_to_add);

    void add_booster()
    {
        booster_counter += 1;
    }

    void set_speed(float v)
    {
        velocity.x = v*booster_counter;
        velocity.y = v*booster_counter;
    }

    void collision_right(bool state)
    {
     is_in_collision_right = state;
    }
    void collision_left(bool state)
    {
        is_in_collision_left = state;
    }
    void collision_top(bool state)
    {
        is_in_collision_top = state;
    }
    void collision_bottom(bool state)
    {
        is_in_collision_bottom = state;
    }



private:
    sf::Vector2f velocity;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    int points;     //obecne punkty w czasie rozgrywki
    int high_score;
    int booster_counter;
    std::vector<bool> achievements;
    friend class Cmap;
    bool is_in_collision_right;
    bool is_in_collision_left;
    bool is_in_collision_top;
    bool is_in_collision_bottom;
};

#endif // CHARACTER_H
