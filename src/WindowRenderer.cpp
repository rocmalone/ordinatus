#include "WindowRenderer.h"

WindowRenderer::WindowRenderer(sf::RenderWindow& window)
    : window(window)
{
}

void WindowRenderer::drawWindowTitlesText(std::vector<std::string> windowTitles, sf::Font font)
{
    sf::Text text(font, "default", 18);
    text.setFillColor(sf::Color::White);

    float y = 100.0f;
    int i = 1;
    for (const std::string& title : windowTitles) {
        std::string displayText = title;
        if (i < 5) {
            displayText = "Ctrl + " + std::to_string(i) + " - " + title;
        }
        text.setString(displayText);
        text.setPosition(sf::Vector2f(10.0f, y));
        window.draw(text);
        y += 25.0f;
        i += 1;
    }
}
