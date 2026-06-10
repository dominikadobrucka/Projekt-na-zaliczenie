#include "character.h"

Character::Character(const sf::Vector2f& velocity, sf::RenderWindow& window) :
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
    setPosition(window.getSize().x/2, window.getSize().y/2);
}

void Character::animate(const sf::Time &elapsed, char direction) {
    sf::FloatRect rectangle_bounds = getGlobalBounds();
    animation_timer +=elapsed.asSeconds();
    if(direction=='w' && rectangle_bounds.top>0){        //chodzenie strzalkami, nieprzenikanie przez krawędzie
        move(0.0, -(velocity.y*elapsed.asSeconds()));
        if(animation_timer<0.01)
        setTextureRect(sf::IntRect(0, 610, 150, 190));  //kolejne kadry animacji
        else if(animation_timer<0.02)
        setTextureRect(sf::IntRect(150, 610, 150, 190));
        else if(animation_timer<0.03)
            setTextureRect(sf::IntRect(300, 610, 150, 190));
        else if(animation_timer<0.04)
            setTextureRect(sf::IntRect(450, 610, 150, 190));
        else
        {animation_timer=0;}
    }
    if(direction=='s' && rectangle_bounds.top+rectangle_bounds.height < window.getSize().y){
        move(0.0, velocity.y*elapsed.asSeconds());
        if(animation_timer<0.01)
            setTextureRect(sf::IntRect(0, 0, 150, 190));
        else if(animation_timer<0.02)
            setTextureRect(sf::IntRect(150, 0, 150, 190));
        else if(animation_timer<0.03)
            setTextureRect(sf::IntRect(300, 0, 150, 190));
        else if(animation_timer<0.04)
            setTextureRect(sf::IntRect(450, 0, 150, 190));
        else
        {animation_timer=0;}

    }
    if(direction=='a' && rectangle_bounds.left > 0){
        move(-(velocity.x*elapsed.asSeconds()), 0.0);
        if(animation_timer<0.01)
            setTextureRect(sf::IntRect(0, 400, 150, 190));
        else if(animation_timer<0.02)
            setTextureRect(sf::IntRect(150, 400, 150, 190));
        else if(animation_timer<0.03)
            setTextureRect(sf::IntRect(300, 400, 150, 190));
        else if(animation_timer<0.04)
            setTextureRect(sf::IntRect(450, 400, 150, 190));
        else
        {animation_timer=0;}

    }
    if(direction=='d' && rectangle_bounds.left + rectangle_bounds.width < window.getSize().x){
        move(velocity.x*elapsed.asSeconds(), 0.0);
        if(animation_timer<0.01)
            setTextureRect(sf::IntRect(0, 200, 150, 190));
        else if(animation_timer<0.02)
            setTextureRect(sf::IntRect(150, 200, 150, 190));
        else if(animation_timer<0.03)
            setTextureRect(sf::IntRect(300, 200, 150, 190));
        else if(animation_timer<0.04)
            setTextureRect(sf::IntRect(450, 200, 150, 190));
        else
        {animation_timer=0;}
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

void Character::add_booster()
{
    booster_counter += 1;
}

void Character::set_speed(float v)
{
    velocity.x = v*booster_counter;
    velocity.y = v*booster_counter;
}

void Character::save_data() //zapis danych gracza do pliku
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

void Character::reset() //reset postaci
{
    setPosition(window.getSize().x/2, window.getSize().y/2);
    points = 0;
    booster_counter = 1;
}