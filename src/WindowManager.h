#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <string>

class WindowManager {
public:
    WindowManager();
    void run();
    void toggleVisibility();
    void updateWindowList();
    HWND getNativeHandle();
    void configureWindowStyle();

private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<std::string> windowTitles;
    bool isVisible;
    void draw();
};

#endif
