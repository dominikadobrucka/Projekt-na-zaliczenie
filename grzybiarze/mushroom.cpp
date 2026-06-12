#include "mushroom.h"

Mushroom::Mushroom(sf::RenderWindow& window) :
    points_for(10), window(window)
{
    int gatunek = rand() % 100;
    
    if (gatunek == 0 || gatunek == 1) 
    {
        tekstura.loadFromFile("./kania.png");
        points_for = 50;
        mushroom_type = "normal";
    }
    else if (gatunek >= 2 && gatunek <= 35)
    {
        tekstura.loadFromFile("./podgrzybek.png");
        points_for = 20;
        mushroom_type = "normal";
    }
    else if (gatunek >= 36 && gatunek <= 70)
    {
        tekstura.loadFromFile("./borowik.png");
        points_for = 10;
        mushroom_type = "normal";
    }
    else if (gatunek >= 71 && gatunek <= 85) 
    {
        tekstura.loadFromFile("./muchomor sromotnikowy .png");
        points_for = -25;
        mushroom_type = "normal";
    }
    else 
    {
        tekstura.loadFromFile("./halucynek.png");
        points_for = 0;
        mushroom_type = "halucynek";
    }

    setTexture(tekstura);
    setPosition(rand() % window.getSize().x - 50, rand() % window.getSize().y - 50);
    setScale(0.03, 0.03);
} 

int Mushroom::Get_points()
{
    return points_for;
}

std::string Mushroom::Get_type()
{
    return mushroom_type;
}