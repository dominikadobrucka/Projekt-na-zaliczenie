#include "button.h"

Button::Button(sf::RenderWindow& window): window(window){
    button_tex.loadFromFile("./button.png");
    setTexture(button_tex);
    setScale(window.getSize().x/getGlobalBounds().width*0.2,0.2);
    setPosition(window.getSize().x*0.4,window.getSize().y*0.7);
}