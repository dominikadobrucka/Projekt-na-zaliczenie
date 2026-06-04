#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
//#include <memory>

#include <object.h>
#include <mushroom.h>
#include <przeszkoda.h>
#include <bush.h>
#include <booster.h>
#include <character.h>
#include <cmap.h>



int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");


    std::string tex1="./gzib.png";
    std::string tex2="./postacprzyklad.png";

    sf::Texture grass;
    grass.loadFromFile("./grass.png");
    grass.setRepeated(true);


    sf::Sprite bg;
    bg.setTexture(grass);
    bg.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    sf::Event event;
    CMap plansza1(window,event,tex1);

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop

        sf::Time elapsed = clock.restart();

        //window.draw(bg);

        plansza1.check_updates(elapsed);
        plansza1.pick_mushrooms();
        plansza1.draw_everything();


        window.display();
    }

    return 0;
}
