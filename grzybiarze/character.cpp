#include "character.h"

void Character::animate(const sf::Time &elapsed, char direction) {
    sf::FloatRect rectangle_bounds = getGlobalBounds();

    if(direction=='w' && rectangle_bounds.top>0){        //chodzenie strzalkami, nieprzenikanie przez krawędzie
        move(0.0, -(velocity.y*elapsed.asSeconds()));
        setTextureRect(sf::IntRect(0, 610, 150, 190));  // zmiana pozycji postaci
    }
    if(direction=='s' && rectangle_bounds.top+rectangle_bounds.height < window.getSize().y){
        move(0.0, velocity.y*elapsed.asSeconds());
        setTextureRect(sf::IntRect(0, 0, 150, 190));
    }
    if(direction=='a' && rectangle_bounds.left > 0){
        move(-(velocity.x*elapsed.asSeconds()), 0.0);
        setTextureRect(sf::IntRect(150, 400, 150, 190));
    }
    if(direction=='d' && rectangle_bounds.left + rectangle_bounds.width < window.getSize().x){
        move(velocity.x*elapsed.asSeconds(), 0.0);
        setTextureRect(sf::IntRect(0, 200, 150, 190));
    }
}

void Character::add_points(int points_to_add)  //dodawanie punktow, edycja najwyzszego wyniku
{
    points += points_to_add;
    if(points>high_score)
    {
        high_score=points;
    }
    std::cout<<points<<"/"<<high_score<<std::endl;
}