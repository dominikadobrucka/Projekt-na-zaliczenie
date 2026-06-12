#include "cmap.h"

Cmap::Cmap(sf::RenderWindow& window, sf::Event& event) :
    window(window), event(event)
{
    jadalne_na_mapie = 0;
    std::vector<Object*> everything;

    my_character = new Character(sf::Vector2f(1500, 1500), window);
    everything.emplace_back(my_character);

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

    bg_tex.loadFromFile("./grass.png");
    bg_tex.setRepeated(true);
    background.setTexture(bg_tex);
    background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    /*
        sf::Font font;
        font.loadFromFile("./PixelGame-R9AZe.otf");
        my_timer = new sf::Text("abc",font,30);
*/

    
    if (!timer_font.loadFromFile("grzybiarze/pixel.ttf")) {
        if (!timer_font.loadFromFile("./pixel.ttf")) {
            std::cout << "Nie udalo sie znalezc czcionki pixel.ttf w zadnej lokalizacji!" << std::endl;
        }
    }

    timer_text.setFont(timer_font);
    timer_text.setCharacterSize(24);            
    timer_text.setFillColor(sf::Color::White);  
    timer_text.setPosition(25, 25);


    game_over_text.setFont(timer_font); 
    game_over_text.setCharacterSize(35); 
    game_over_text.setFillColor(sf::Color::Red); 
    game_over_text.setString("KONIEC GRY!\nWcisnij ENTER aby wrocic");
    game_over_text.setPosition(250.f, 400.f);
}

bool Cmap::check_updates(sf::Time elapsed, double game_timer)
{
    
    if (game_over)
    {
        sf::Event event_game_over;
        while (window.pollEvent(event_game_over)) 
        {
            if (event_game_over.type == sf::Event::Closed)
                window.close();
            
            if (event_game_over.type == sf::Event::KeyReleased)
            {
                if (event_game_over.key.code == sf::Keyboard::Enter)
                {
                    game_over = false;
                    this->reset(); 
                    return true; // <<=== NOWOŚĆ: Informujemy main.cpp, że gracz wcisnął ENTER i resetuje grę!
                }
            }
        }
        return false;
    }

    
    double time_left = total_game_time - game_timer;

    if (time_left <= 0.0) 
    {
        time_left = 0.0;
        game_over = true; 
        game_over_text.setFillColor(sf::Color::Red); 
        game_over_text.setString("KONIEC GRY!\nCzas mina.\nWcisnij ENTER aby wrocic");
    }

    
    
    if (!game_over)
    {
        int dobre_grzyby = 0;
        for (auto &g : vec_mushrooms)
        {
        
            if (g->Get_points() > 0)
            {
                dobre_grzyby++;
            }
        }

        
        if (dobre_grzyby == 0 && !vec_mushrooms.empty())
        {
            game_over = true;
            game_over_text.setFillColor(sf::Color::Green); 
            game_over_text.setCharacterSize(28);
            game_over_text.setString("WYGRANA!\nWszystkie jadalne grzyby zebrane!\nWcisnij ENTER aby wrocic");
            game_over_text.setPosition(200.f, 400.f);
            return false;
        }
    }

    
    int minutes = static_cast<int>(time_left) / 60;
    int seconds = static_cast<int>(time_left) % 60;

    std::string sec_str = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);
    std::string min_str = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);

    timer_text.setString("Czas: " + min_str + ":" + sec_str);
    
    
    if (slow_timer > 0.0) 
    {
        slow_timer -= elapsed.asSeconds();
        if (slow_timer <= 0.0) 
        {
            slow_timer = 0.0;
            my_character->set_speed(1500);
        }
    }

    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            my_character->animate(elapsed,'w');
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            my_character->animate(elapsed,'s');
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            my_character->animate(elapsed,'a');
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            my_character->animate(elapsed,'d');
        }
    }
    return false;
}
void Cmap::check_collisions(GameAudio& audio) 
{
    sf::FloatRect boundingBox = my_character->getGlobalBounds();
    
    
    for (auto &s : vec_mushrooms) 
    {
        if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
        {
            my_character->add_points(s->Get_points());
            audio.playCollect();
            if (s->Get_points() > 0)
            {
                jadalne_na_mapie--;
            }

            if (s->Get_type() == "halucynka")
            {
                my_character->set_speed(500);
                slow_timer = 5.0; 
            }

            vec_mushrooms.erase(std::remove(vec_mushrooms.begin(), vec_mushrooms.end(), s), vec_mushrooms.end());
            break;
        }
    }

    
    for (auto &s : vec_boosters) 
    {
        if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
        {
            my_character->add_booster();
            vec_boosters.erase(std::remove(vec_boosters.begin(), vec_boosters.end(), s), vec_boosters.end());
        }
    }

    
    
    bool w_krzaku = false;
    for (auto &s : vec_bushes) 
    {
        if(boundingBox.intersects(s->getGlobalBounds()))
        {
            w_krzaku = true;
        }
    }

    if (w_krzaku && slow_timer <= 0.0) 
    {
        my_character->set_speed(900);
    } 
    else if (!w_krzaku && slow_timer <= 0.0) 
    {
        my_character->set_speed(1500); // Normalna prędkość wraca tylko gdy nie ma halucynacji i krzaka
    }

   
    for (auto &s : vec_przeszkody) 
    {
        sf::FloatRect a = s->getGlobalBounds();

        if(boundingBox.intersects(a))
        {
            
            if(boundingBox.top<a.top
                && boundingBox.top +boundingBox.height <a.top+a.height
                && boundingBox.left< a.left+a.width
                && boundingBox.left+boundingBox.width >a.left)
            {
                my_character->setPosition(boundingBox.left,a.top-boundingBox.height);
            }
            
            else if(boundingBox.top>a.top
                     && boundingBox .top+boundingBox.height>a.top+a.height
                     && boundingBox.left<a.left+a.width
                     && boundingBox.left + boundingBox.width>a.left)
            {
                my_character->setPosition(boundingBox.left,a.top+a.height);
            }
            
            if(boundingBox.left<a.left
                && boundingBox.left +boundingBox.width<a.left+a.width
                && boundingBox.top<a.top+a.height
                && boundingBox.top+boundingBox.height>a.top)
            {
                my_character->setPosition(a.left-boundingBox.width,boundingBox.top);
            }
            
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

void Cmap::draw_everything() 
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
    window.draw(timer_text); 

    if (game_over)
    {
        window.draw(game_over_text); 
    }
}

void Cmap::save_data()
{
    my_character->save_data();
}

void Cmap::reset()
{
    vec_mushrooms.clear();
    vec_boosters.clear();
    vec_bushes.clear();
    vec_przeszkody.clear();
    jadalne_na_mapie = 0;

    my_character->reset();

    std::vector<Object*> everything;

    for(int i=0; i<12+rand()%10; i++)
    {
        Mushroom* nowy = new Mushroom(window);
        if(none_of(everything.begin(),everything.end(),[nowy](Object* a){return nowy->getGlobalBounds().intersects(a->getGlobalBounds());}))
        {
            vec_mushrooms.emplace_back(nowy);
            everything.emplace_back(nowy);
            if (nowy->Get_points() > 0) 
            {
                jadalne_na_mapie++;
            }
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

