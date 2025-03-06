#ifndef OSEARCHBOX_H
#define OSEARCHBOX_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class OSearchBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    bool isFocused = false;
    std::string inputString;

public:
    OSearchBox(float x, float y, float width, float height, sf::Font& font);

    void handleEvent(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif // OSEARCHBOX_H
