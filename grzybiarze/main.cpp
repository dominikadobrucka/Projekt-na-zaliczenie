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



int main() {
    // create the window
    std::srand(std::time({}));
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");


    std::string tex1="./gzib.png";
    std::string tex2="./postacprzyklad.png";

    sf::Texture grass;
    grass.loadFromFile("./grass.png");
    grass.setRepeated(true);


    sf::Event event;
    Menu menu(window,event);
    CMap plansza1(window,event,tex1);
    int choice = 1;

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop

        sf::Time elapsed = clock.restart();

       // while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
       // {
       //     menu.draw_everything();
       // }

        switch(choice)
        {
        case 1:
        {
            while (window.pollEvent(event)) {

                if(event.type == sf::Event::MouseButtonPressed)
                {
                    choice = 2;
                }
            }
            menu.check_updates();
            menu.draw_everything();
            break;
        }
        case 2:
        {
            plansza1.check_updates(elapsed);
            plansza1.check_collisions();
            plansza1.draw_everything();
            break;
        }
        }
        window.display();
    }
    plansza1.save_data();
    return 0;
}
