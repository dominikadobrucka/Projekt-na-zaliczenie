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

int main() {
    // create the window
    std::srand(std::time({}));
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "My window");


    sf::Event event;
    Menu menu(window,event);
    CMap plansza1(window,event);
    achievments_page osiagniecia(window,event);

    int choice = 1;
    double game_timer = 0;

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop

        sf::Time elapsed = clock.restart();


        switch(choice)
        {
        case 1:
        {
            game_timer=0;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    choice = 2;
                }
            }
            //menu.check_updates();
            menu.draw_everything();
            break;
        }
        case 2:
        {
            if(game_timer<=45)
            {
            game_timer += elapsed.asSeconds();
            plansza1.check_updates(elapsed,game_timer);
            plansza1.check_collisions();
            plansza1.draw_everything();
            break;
            }
            else{choice=1;}
            plansza1.reset();
        }
        case 3:
        {

        }
        }
        window.display();
    }
    plansza1.save_data();
    return 0;
}
