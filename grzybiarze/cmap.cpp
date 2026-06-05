#include "cmap.h"

void CMap::check_updates(sf::Time elapsed)
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

void CMap::check_collisions()
{
    sf::FloatRect boundingBox = my_character->getGlobalBounds();
    for (auto &s : vec_mushrooms) //sprawdzamy czy postac dotyka grzybka, jesli tak to go usuwamy z wektora
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

        sf::FloatRect a = s->getGlobalBounds();

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

void CMap::draw_everything() //rysowanie wszystkich elementow
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
    window.draw(*my_character);
    for (auto &s : vec_przeszkody)
    {
        window.draw(*s);
    }
}

