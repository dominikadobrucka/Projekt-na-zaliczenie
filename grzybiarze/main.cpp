#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <memory>

class Mushroom{};
class Przeszkoda{
    //obiekty, przez które nie można przenikać np. drzewa
};
class Bush{
    // krzak malin, można przenikać ale spowalnia
};
class CMap
{
    //plansza
};
class Booster{};

class Character : public sf::Sprite {
public:
    Character(const sf::Vector3f& velocity, sf::RenderWindow& window, sf::Texture &tekstura) :
        velocity(velocity), window(window), points(0), high_score(0)
    {
        setTexture(tekstura);
        setScale(0.3, 0.3);
        setTextureRect(sf::IntRect(0, 0, 150, 190));
        setPosition(300, 300);
    }

    void animate(const sf::Time &elapsed, char direction) {
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(direction=='w' && rectangle_bounds.top>0){        //chodzenie strzalkami, nieprzenikanie przez krawędzie
            move(0.0, -(velocity.y*elapsed.asSeconds()));
            setTextureRect(sf::IntRect(0, 610, 150, 190));  // zmiana pozycji postaci
        }
        if(direction=='s' && rectangle_bounds.top+rectangle_bounds.height < window.getSize().y){
            move(0.0, velocity.y*elapsed.asSeconds());
            setTextureRect(sf::IntRect(0, 0, 150, 190));
        }
        if(direction=='a' && rectangle_bounds.left > 0){
            move(-(velocity.x*elapsed.asSeconds()), 0.0);
            setTextureRect(sf::IntRect(150, 400, 150, 190));
        }
        if(direction=='d' && rectangle_bounds.left + rectangle_bounds.width < window.getSize().x){
            move(velocity.x*elapsed.asSeconds(), 0.0);
            setTextureRect(sf::IntRect(0, 200, 150, 190));
        }
    }
private:
    sf::Vector3f velocity;
    sf::RenderWindow& window;
    int points;     //to na później
    int high_score;
};

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");

    //std::vector<sf::Drawable*> DrawableObjects; //wektor objektów do narysowania

    sf::Texture tekstura_postac;                            //ładowanie tekstur
    tekstura_postac.loadFromFile("./postacprzyklad.png");
    tekstura_postac.setRepeated(true);
    sf::Texture grass;
    grass.loadFromFile("./grass.png");
    grass.setRepeated(true);

    Character postac(sf::Vector3f(3000, 3000, 0), window, tekstura_postac); //tworzenie obiektów
    sf::Sprite plansza;
    plansza.setTexture(grass);
    plansza.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Time elapsed = clock.restart();

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //chodzenie WSAD lub strzałki
                    postac.animate(elapsed,'w');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                postac.animate(elapsed,'s');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    postac.animate(elapsed,'a');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                postac.animate(elapsed,'d');
            }
        }


        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(plansza);       //rysowanie obiektów
        window.draw(postac);
        // end the current frame
        window.display();
    }

    return 0;
}
