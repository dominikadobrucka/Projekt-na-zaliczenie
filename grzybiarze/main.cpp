#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Window/Mouse.hpp>

//#include <memory>

#include <object.h>
#include <mushroom.h>
#include <przeszkoda.h>
#include <bush.h>
#include <booster.h>
#include <character.h>
#include <cmap.h>
#include <menu.h>
#include <achievments_page.h>
#include "audio.h"

int main() {

    std::srand(std::time({}));
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "My window");
    GameAudio gameAudio;
    gameAudio.playMusic();

    sf::Event event;
    Menu menu(window,event);
    Cmap plansza1(window,event);
    achievments_page osiagniecia(window,event);

    int choice = 1;
    double game_timer = 0;

    sf::Clock clock;

    while (window.isOpen()) {
      
        sf::Time elapsed = clock.restart();

        switch(choice)
        {
        case 1:
        {
            game_timer = 0;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    choice = 2;
                }
            }
            menu.draw_everything();
            break;
        }
        case 2:
        {
            game_timer += elapsed.asSeconds();
            
            
            if (plansza1.check_updates(elapsed, game_timer) == true)
            {
                game_timer = 0; 
                choice = 1;     
                break;          
            }
            
            plansza1.check_collisions(gameAudio);
            plansza1.draw_everything();
            
            break;
        }
        case 3:
        {
            break;
        }
        }
        window.display();
    }
    plansza1.save_data();
    return 0;
}