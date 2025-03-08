#ifndef WINDOWRENDERER_H
#define WINDOWRENDERER_H

#include <SFML/Graphics.hpp>
#include "WinInfo.h"

class WindowRenderer {
public:
	WindowRenderer(sf::RenderWindow& window);
	void drawWindowTitlesText(std::vector<WinInfo>* windows, sf::Font);

private:
	sf::RenderWindow& window;

};

#endif
