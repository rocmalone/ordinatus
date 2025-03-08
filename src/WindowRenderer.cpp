#include "WindowRenderer.h"
#include "WinInfo.h"

WindowRenderer::WindowRenderer(sf::RenderWindow& window)
    : window(window)
{
}

void WindowRenderer::drawWindowTitlesText(std::vector<WinInfo>* windows, sf::Font font)
{
    sf::Text text(font, "default", 18);
    text.setFillColor(sf::Color::White);

    float y = 100.0f;
    int i = 1;
    for (const WinInfo& winInfo : *windows) {
        std::string displayText = winInfo.title;
        if (i < 5) {
            displayText = "Ctrl + " + std::to_string(i) + " - " + winInfo.title + std::to_string((int)winInfo.hwnd);
        }
        text.setString(displayText);
        text.setPosition(sf::Vector2f(10.0f, y));
        window.draw(text);
        y += 25.0f;
        i += 1;
    }
}
