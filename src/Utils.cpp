#include "Utils.h"
#include <iostream>

bool disableMinimizeAnimation() {
    ANIMATIONINFO animInfo;
    animInfo.cbSize = sizeof(animInfo);
    animInfo.iMinAnimate = 0;
    return SystemParametersInfo(SPI_SETANIMATION, sizeof(animInfo), &animInfo, 0);
}

bool enableMinimizeAnimation() {
    ANIMATIONINFO animInfo;
    animInfo.cbSize = sizeof(animInfo);
    animInfo.iMinAnimate = 1;
    return SystemParametersInfo(SPI_SETANIMATION, sizeof(animInfo), &animInfo, 0);
}

sf::Font loadSystemFont(const std::string& fontName) {
    char windowsFontPath[MAX_PATH];
    if (GetWindowsDirectory(windowsFontPath, MAX_PATH)) {
        std::string fontPath = std::string(windowsFontPath) + "\\Fonts\\" + fontName;
        sf::Font font;
        if (font.openFromFile(fontPath)) {
            return font;
        }
    }
    std::cerr << "Failed to load system font: " << fontName << std::endl;
    return sf::Font();
}

HWND getSFMLWindowHandle(sf::RenderWindow& window) {
    return static_cast<HWND>(window.getNativeHandle());
}

bool isWindowInTaskbarAndRoot(HWND hwnd) {
    LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

    // WS_EX_TOOLWINDOW excludes the window from the taskbar
    // Check if this bit flag is set using bitwise-and
    if (exStyle & WS_EX_TOOLWINDOW) {
        return false;
    }

    if (exStyle & WS_EX_APPWINDOW) {
        return true;
    }

    // Get the application's root window
    HWND root = GetAncestor(hwnd, GA_ROOTOWNER);

    // If the root window is this window, then we display it
    return (root == hwnd);
}
