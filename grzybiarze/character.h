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
        velocity(velocity), window(window), points(0), high_score(0),booster_counter(1),animation_timer(0)
    {
        std::fstream input_file("./character_data.txt", std::ios::in);
        if (input_file.is_open()) {
            input_file >> high_score;
            while (!input_file.eof()) {
                std::string line;
                input_file >> line;

                if(line[0]=='1')
                {
                    achievements.emplace_back(true);
                }
                else if(line[0]=='0'){achievements.emplace_back(false);}
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

    void save_data()
    {
        std::ofstream input_file("./character_data.txt", std::ios::out);
        if (input_file.is_open()) {
            input_file << high_score;
            for(auto s: achievements)
            {
                if(s==true)
                {
                    input_file<<std::endl<<'1';
                }
                else if(s==false){input_file<<std::endl<<'0';}
            }
        }
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
    double animation_timer;
};

#endif // CHARACTER_H
