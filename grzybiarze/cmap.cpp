#include "cmap.h"

CMap::CMap(sf::RenderWindow& window, sf::Event ev) :
    window(window), event(ev)
{
    std::vector<Object*> everything;

    my_character = new Character(sf::Vector2f(1500, 1500), window);
    everything.emplace_back(my_character);

    for(int i=0; i<12+rand()%10; i++)//tworzymy grzyby, sprawdzamy czy nie nachodza na inne obiekty
    {
        Mushroom* nowy = new Mushroom(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_mushrooms.emplace_back(nowy);
            everything.emplace_back(nowy);
        }
        else{delete nowy;}
    }

    for(int i=0; i<rand()%2; i++)
    {
        Booster* nowy = new Booster(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_boosters.emplace_back(nowy);
            everything.emplace_back(nowy);
        }
        else{delete nowy;}
    }

    for(int i=0; i<15+rand()%10; i++)
    {
        Bush* nowy = new Bush(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_bushes.emplace_back(nowy);
            everything.emplace_back(nowy);
        }
        else{delete nowy;}
    }

    for(int i=0; i<30; i++)
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
    /*
        sf::Font font;
        font.loadFromFile("./PixelGame-R9AZe.otf");
        my_timer = new sf::Text("abc",font,30);
*/
}

void CMap::check_updates(sf::Time elapsed, double game_timer)
{
    while (window.pollEvent(event)) {
        
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

void CMap::check_collisions(GameAudio& audio) 
{
    sf::FloatRect boundingBox = my_character->getGlobalBounds();
    for (auto &s : vec_mushrooms) 
    {
        if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
        {
            my_character->add_points(s->Get_points());
            audio.playCollect();
            vec_mushrooms.erase(std::remove(vec_mushrooms.begin(), vec_mushrooms.end(), s), vec_mushrooms.end());;
        }
    }
    for (auto &s : vec_boosters) 
    {
        if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
        {
            my_character->add_booster();
            vec_boosters.erase(std::remove(vec_boosters.begin(), vec_boosters.end(), s), vec_boosters.end());;
        }
    }
    for (auto &s : vec_bushes) 
    {
        if(boundingBox.intersects(s->getGlobalBounds()))
        {
            my_character->set_speed(900);
        }
        else{my_character->set_speed(1500);}
    }

    for (auto &s : vec_przeszkody) 
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

void CMap::draw_everything() 
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

void CMap::save_data()
{
    my_character->save_data();
}

void CMap::reset()
{
    vec_mushrooms.clear();
    vec_boosters.clear();
    vec_bushes.clear();
    vec_przeszkody.clear();

    my_character->reset();

    std::vector<Object*> everything;

    for(int i=0; i<12+rand()%10; i++)
    {
        Mushroom* nowy = new Mushroom(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_mushrooms.emplace_back(nowy);
            everything.emplace_back(nowy);
        }
        else{delete nowy;}
    }

    for(int i=0; i<rand()%2; i++)
    {
        Booster* nowy = new Booster(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_boosters.emplace_back(nowy);
            everything.emplace_back(nowy);
        }
        else{delete nowy;}
    }

    for(int i=0; i<15+rand()%10; i++)
    {
        Bush* nowy = new Bush(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_bushes.emplace_back(nowy);
            everything.emplace_back(nowy);
        }
        else{delete nowy;}
    }

    for(int i=0; i<30; i++)
    {
        Przeszkoda* nowy = new Przeszkoda(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_przeszkody.emplace_back(nowy);
            everything.emplace_back(nowy);
        }
    }
}

