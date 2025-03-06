#ifndef WINDOWRENDERER_H
#define WINDOWRENDERER_H

#include <SFML/Graphics.hpp>

class WindowRenderer {
public:
	WindowRenderer(sf::RenderWindow& window);
	void drawWindowTitlesText(std::vector<std::string> windowTitles, sf::Font);

private:
	sf::RenderWindow& window;

};

#endif
