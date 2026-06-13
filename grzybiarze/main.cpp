#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Window/Mouse.hpp>

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
#include "rules_page.h"

int main() {

    std::srand(std::time({}));
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "My window");
    GameAudio gameAudio;
    gameAudio.playMusic();

    sf::Event event;
    Menu menu(window,event);
    Cmap plansza1(window,event);
    achievments_page osiagniecia(window,event);
    RulesPage zasady_ekran(window, event);

    int choice = 1;
    double game_timer = 0;

    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("pixel.ttf");

    sf::Texture texAchi[5];
    texAchi[0].loadFromFile("achievement.png");     
    texAchi[1].loadFromFile("achievement (1).png"); 
    texAchi[2].loadFromFile("achievement (2).png"); 
    texAchi[3].loadFromFile("achievement (3).png"); 
    texAchi[4].loadFromFile("achievement (4).png"); 

    bool odblokowane[5] = {false, false, false, false, false};
    sf::Sprite popupSprite;
    popupSprite.setPosition(window.getSize().x / 2.f - 150.f, 20.f); 

    bool pokazPopup = false;
    sf::Clock popupZegar;

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

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int akcja = menu.check_click(mousePos);
                    if (akcja != 0) {
                        choice = akcja; 
                    }
                }
            }
            menu.draw_everything();
            break;
        }
        case 2:
        {
            game_timer += elapsed.asSeconds();
            
            if (plansza1.check_updates(elapsed, game_timer, gameAudio) == true)
            {
                game_timer = 0; 
                choice = 1;     
                break;          
            }
            
            plansza1.check_collisions(gameAudio);
            plansza1.draw_everything();

            if (plansza1.achi_perfekcjonista && !odblokowane[0]) {
                odblokowane[0] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[0]);
                osiagniecia.is_ach1_unlocked = true;
            }
            else if (plansza1.zjedzone_zle >= 3 && plansza1.zjedzone_zle > plansza1.zjedzone_dobre && !odblokowane[1]) {
                odblokowane[1] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[1]);
                osiagniecia.is_ach2_unlocked = true;
            }
            else if (plansza1.wejscia_w_krzaki >= 5 && !odblokowane[2]) {
                odblokowane[2] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[2]);
                osiagniecia.is_ach3_unlocked = true;
            }
            else if (plansza1.achi_sprinter && !odblokowane[3]) {
                odblokowane[3] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[3]);
                osiagniecia.is_ach4_unlocked = true;
            }
            else if (plansza1.achi_halucynek && !odblokowane[4]) {
                odblokowane[4] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[4]);
                osiagniecia.is_ach5_unlocked = true;
            }

            if (pokazPopup && popupZegar.getElapsedTime().asSeconds() > 3.0f) {
                pokazPopup = false;
            }

            if (pokazPopup) {
                window.draw(popupSprite);
            }
            
            break;
        }
        case 3:
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int akcja = osiagniecia.check_click(mousePos);
                    if (akcja == 1) {
                        choice = 1; 
                    }
                }
            }
            
            osiagniecia.draw_everything();
            break;
        }
        case 4:
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int akcja = zasady_ekran.check_click(mousePos);
                    if (akcja == 1) {
                        choice = 1;
                    }
                }
            }

            zasady_ekran.draw_everything();
            break;
        }
        }
        window.display();
    }
    plansza1.save_data();
    return 0;
}