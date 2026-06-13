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
    sf::Font font;
    font.loadFromFile("pixel.ttf");

    // --- SYSTEM OSIĄGNIĘĆ (OBRAZKOWY) ---
    sf::Texture texAchi[5];
    texAchi[0].loadFromFile("achievement.png");     // Perfekcjonista
    texAchi[1].loadFromFile("achievement (1).png"); // Ryzykant
    texAchi[2].loadFromFile("achievement (2).png"); // W malinach
    texAchi[3].loadFromFile("achievement (3).png"); // Sprinter
    texAchi[4].loadFromFile("achievement (4).png"); // Ukryte (Halucynek)

    bool odblokowane[5] = {false, false, false, false, false};
    sf::Sprite popupSprite;
    popupSprite.setPosition(window.getSize().x / 2.f - 150.f, 20.f); // Wyśrodkowane u góry

    bool pokazPopup = false;
    sf::Clock popupZegar;
    // ------------------------------------

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

                // --- NAPRAWIONE KLIKANIE W MENU ---
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int akcja = menu.check_click(mousePos);
                    if (akcja != 0) {
                        choice = akcja; // Zmienia na 2 (Graj) lub 3 (Osiągnięcia) w zależności co klikniesz
                    }
                }
                // ----------------------------------
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

            // --- LOGIKA POPUPU W GRZE ---
            if (plansza1.achi_perfekcjonista && !odblokowane[0]) {
                odblokowane[0] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[0]);
            }
            // Ryzykant: zjadł min. 3 złe i więcej złych niż dobrych
            else if (plansza1.zjedzone_zle >= 3 && plansza1.zjedzone_zle > plansza1.zjedzone_dobre && !odblokowane[1]) {
                odblokowane[1] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[1]);
            }
            else if (plansza1.wejscia_w_krzaki >= 5 && !odblokowane[2]) {
                odblokowane[2] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[2]);
            }
            else if (plansza1.achi_sprinter && !odblokowane[3]) {
                odblokowane[3] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[3]);
            }
            else if (plansza1.achi_halucynek && !odblokowane[4]) {
                odblokowane[4] = true; pokazPopup = true; popupZegar.restart(); popupSprite.setTexture(texAchi[4]);
            }

            if (pokazPopup && popupZegar.getElapsedTime().asSeconds() > 3.0f) {
                pokazPopup = false;
            }

            if (pokazPopup) {
                window.draw(popupSprite);
            }
            // ----------------------------
            break;
        }
        case 3:
        {
            // --- NASŁUCHIWANIE ZDARZEŃ (ZAPOBIEGA CRASHOM) ---
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int akcja = osiagniecia.check_click(mousePos);
                    if (akcja == 1) {
                        choice = 1; // 1 oznacza powrót do Menu
                    }
                }
            }
            // -------------------------------------------------

            osiagniecia.draw_everything();

            int y_pos = 150; // Wysokość pierwszego obrazka na liście
            bool cokolwiek_odblokowane = false;

            for(int i = 0; i < 5; i++) {
                if (odblokowane[i]) {
                    sf::Sprite s(texAchi[i]);
                    s.setPosition(window.getSize().x / 2.f - 150.f, y_pos);
                    window.draw(s);
                    y_pos += 80; // Odstęp pionowy między obrazkami
                    cokolwiek_odblokowane = true;
                }
            }


            break;
        }
        }
        window.display();
    }
    plansza1.save_data();
    return 0;
}