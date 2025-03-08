#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <string>

struct WindowInfo {
    HWND hwnd;
    std::string title;
};

class WindowManager {
public:
    WindowManager();
    void run();
    void toggleVisibility();
    void updateWindowList();
    void focusWindow(HWND hwnd);
    HWND getForegroundWindow();
    HWND getNativeHandle();
    void configureWindowStyle();

private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<WindowInfo> windows;
    bool isVisible;
    void draw();
};



#endif
