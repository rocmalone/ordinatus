#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>

bool disableMinimizeAnimation();
bool enableMinimizeAnimation();
sf::Font loadSystemFont(const std::string& fontName);
bool isWindowInTaskbarAndRoot(HWND hwnd);

#endif
