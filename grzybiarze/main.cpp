#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
//#include <memory>

class Object :public sf::Sprite{
public:
    Object(){};
};

class Mushroom : public Object{
public:
    Mushroom(sf::RenderWindow& window, std::string &arg_tekstura) :
        points_for(10),window(window)
    {
        sf::FloatRect rectangle_bounds = getGlobalBounds();
        tekstura.loadFromFile(arg_tekstura);
        setTexture(tekstura);
        setPosition(rand()%window.getSize().x-rectangle_bounds.width, rand()%window.getSize().y-rectangle_bounds.height);
        setScale(0.05, 0.05);
    }
    ~Mushroom(){};
    int Get_points(){
        return points_for;
    }
private:
    int points_for;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    friend class Cmap;
};

class Przeszkoda{
    //obiekty, przez które nie można przenikać np. drzewa
};
class Bush{
    // krzak malin, można przenikać ale spowalnia
};

class Booster{};

class Character : public Object {
public:
    Character(const sf::Vector3f& velocity, sf::RenderWindow& window, std::string &arg_tekstura) :
        velocity(velocity), window(window), points(0), high_score(0)
    {
        std::fstream input_file("./character_data.txt", std::ios::in);
        if (input_file.is_open()) {
            input_file >> high_score;
            while (!input_file.eof()) {
                std::string line;
                input_file >> line;

                if(line[0]=='1')
                {
                achievements.emplace_back(1);
                }
                else {achievements.emplace_back(0);}
                input_file >>line;
            }
        }
        tekstura.loadFromFile("./postacprzyklad.png");
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
void add_points(int points_to_add)  //dodawanie punktow, edycja najwyzszego wyniku
    {
    points += points_to_add;
        if(points>high_score)
        {
            high_score=points;
        }
        std::cout<<points<<"/"<<high_score<<std::endl;
    }
private:
    sf::Vector3f velocity;
    sf::RenderWindow& window;
    sf::Texture tekstura;
    int points;     //obecne punkty w czasie rozgrywki
    int high_score;
    std::vector<bool> achievements;
    friend class Cmap;
};

class CMap
{
public:
    CMap(sf::RenderWindow& window, std::string tex_character,std::string tex_mushroom) :
        window(window), my_mushroom(window,tex_mushroom)
    {
        for(int i=0; i<4; i++)
        graphicobjects.emplace_back(new Mushroom(window,tex_mushroom)); //dodajemy 4 grzyby do narysowania

        my_character = new Character(sf::Vector3f(3000, 3000, 0), window, tex_character);
    }

std::vector<Mushroom*> to_draw()
    {
    return graphicobjects;
    }

Character* player()
    {
    return my_character;
    }

    void pick_mushrooms() //sprawdzamy czy postac dotyka grzybka, jesli tak to go usuwamy z wektora
    {
        for (auto &s : graphicobjects)
        {
            sf::FloatRect boundingBox = my_character->getGlobalBounds();
            if(boundingBox.contains(s->getPosition().x+(s->getGlobalBounds().width/2),s->getPosition().y+(s->getGlobalBounds().height)/2))
            {
                my_character->add_points(s->Get_points());
                graphicobjects.erase(std::remove(graphicobjects.begin(), graphicobjects.end(), s), graphicobjects.end());;
            }
        }
    }

private:
    sf::RenderWindow& window;
    Character* my_character;
    Mushroom my_mushroom;
    std::vector<Mushroom*> graphicobjects;
};

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
    CMap plansza1(window,tex2,tex1);

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
                    plansza1.player()->animate(elapsed,'w');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                plansza1.player()->animate(elapsed,'s');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    plansza1.player()->animate(elapsed,'a');
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                plansza1.player()->animate(elapsed,'d');
            }
        }

        plansza1.pick_mushrooms();


        // clear the window with black color
        window.clear(sf::Color::Black);
        //rysowanie wszystkiego
        window.draw(bg);
        for (auto &s : plansza1.to_draw())
        {
            window.draw(*s);
        }
        window.draw(*plansza1.player());

        // end the current frame
        window.display();
    }

    return 0;
}
