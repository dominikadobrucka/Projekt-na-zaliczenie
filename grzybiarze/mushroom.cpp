#include "mushroom.h"
Mushroom::Mushroom(sf::RenderWindow& window) :
    points_for(10),window(window)
{
    int gatunek = rand()%100;
    if (gatunek==0 ||gatunek==1) //kania: prawdopodobienstwo 2%
    {
        tekstura.loadFromFile("./kania.png");
        points_for=50;
    }
    else if(gatunek>=2&&gatunek<=50)
    {
        tekstura.loadFromFile("./podgrzybek.png");
        points_for=20;
    }
    else
    {
        tekstura.loadFromFile("./borowik.png");
        points_for=10;
    }
    setTexture(tekstura);
    setPosition(rand()%window.getSize().x-50, rand()%window.getSize().y-50);
    setScale(0.03, 0.03);
}

int Mushroom::Get_points()
{
    return points_for;
}

