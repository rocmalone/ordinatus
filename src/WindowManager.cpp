#include "WindowManager.h"
#include "Utils.h"
#include <iostream>
#include <format>

/// <summary>
/// Callback function for EnumWindows, adds visible window titles to vector
/// </summary>
BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    char title[256];
    // If the window is visible and has a title
    if (IsWindowVisible(hwnd) 
        && GetWindowText(hwnd, title, sizeof(title)) > 0
        && isWindowInTaskbarAndRoot(hwnd)) {
        
        auto* titles = reinterpret_cast<std::vector<std::string>*>(lParam);
        titles->push_back(title);
    }
    return TRUE;
}

WindowManager::WindowManager()
    : window(sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project", sf::Style::None)) {

    window.setFramerateLimit(120);
    font = loadSystemFont("arial.ttf"); // Load system font
    configureWindowStyle();
    ShowWindow(getNativeHandle(), SW_HIDE); // Hide initially
}

/// <summary>
/// Get the native Windows handle of the SFML window
/// </summary>
HWND WindowManager::getNativeHandle() {
    return static_cast<HWND>(window.getNativeHandle());
}

/// <summary>
/// Configure window style to hide from taskbar
/// </summary>
void WindowManager::configureWindowStyle() {
    LONG_PTR style = GetWindowLongPtr(getNativeHandle(), GWL_EXSTYLE);
    style &= ~WS_EX_APPWINDOW;
    style |= WS_EX_TOOLWINDOW;
    SetWindowLongPtr(getNativeHandle(), GWL_EXSTYLE, style);
}

/// <summary>
/// Update the list of currently open windows
/// </summary>
void WindowManager::updateWindowList() {
    windowTitles.clear();
    EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&windowTitles));
}

/// <summary>
/// Toggle the visibility of the SFML window
/// </summary>
void WindowManager::toggleVisibility() {
    if (!isVisible) {
        ShowWindow(getNativeHandle(), SW_SHOW);
        SetWindowPos(getNativeHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        updateWindowList();
    }
    else {
        disableMinimizeAnimation();
        ShowWindow(getNativeHandle(), SW_HIDE);
        enableMinimizeAnimation();
    }
    isVisible = !isVisible;
}

/// <summary>
/// Draw the list of visible windows onto the SFML window
/// </summary>
void WindowManager::draw() {
    window.clear(sf::Color::Black);
    sf::Text text(font, "default", 18);
    text.setFillColor(sf::Color::White);

    float y = 20.0f;
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

void WindowManager::run() {
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        draw();

        window.display();
    }
}
