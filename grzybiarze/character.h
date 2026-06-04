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
        velocity(velocity), window(window), points(0), high_score(0)
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

private:
    sf::Vector2f velocity;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    int points;     //obecne punkty w czasie rozgrywki
    int high_score;
    std::vector<bool> achievements;
    friend class Cmap;
};

#endif // CHARACTER_H
