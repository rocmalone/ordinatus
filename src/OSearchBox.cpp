#include "OSearchBox.h"

// Constructor Implementation
OSearchBox::OSearchBox(float x, float y, float width, float height, sf::Font& font)
    : text(font, "default", 24) // Corrected sf::Text initialization
{
    // Configure text
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(x + 5, y + 5));

    // Configure box
    box.setSize(sf::Vector2f(width, height));
    box.setPosition(sf::Vector2f(x, y));
    box.setFillColor(sf::Color::Green);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);
}

// Handle user input events
void OSearchBox::handleEvent(sf::Event event, sf::RenderWindow& window) {

    //if (event.is<sf::Event::MouseButtonPressed>()) {
    //    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    //    //isFocused = box.getGlobalBounds().contains(mousePos);
    //    //box.setOutlineColor(isFocused ? sf::Color::Blue : sf::Color::White);
    //}

    if (const auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
        if (textEntered->unicode > 127) {
            return;
        }

        
        // Backspace
        if (textEntered->unicode == '\b' && !inputString.empty()) {
            inputString.pop_back();
        }
        // Enter
        else if (textEntered->unicode == '\r') {
            inputString.clear();
        }
        // Other keys
        else {
            inputString += static_cast<char>(textEntered->unicode);
        }
        std::cout << "Input string: " << inputString << std::endl;
        text.setString(inputString);
    }
}

// Draw function
void OSearchBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}
