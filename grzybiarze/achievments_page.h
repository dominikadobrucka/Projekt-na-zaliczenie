#ifndef ACHIEVMENTS_PAGE_H
#define ACHIEVMENTS_PAGE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
class achievments_page
{
public:
    achievments_page(sf::RenderWindow& window,sf::Event ev):window(window),event(ev){};
    void check_updates()
    {
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    void draw_everything()
    {
        window.clear(sf::Color::Black);
    }
private:
    sf::RenderWindow& window;
    sf::Event event;
};

#endif // ACHIEVMENTS_PAGE_H
