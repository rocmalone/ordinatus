#include "WindowManager.h"
#include "Utils.h"
#include <iostream>
#include "WindowRenderer.h"
#include "OSearchBox.h"


WindowManager::WindowManager()
    : window(sf::RenderWindow(sf::VideoMode({ 600u, 400u }), "CMake SFML Project", sf::Style::None)) {

    window.setFramerateLimit(120);
    font = loadSystemFont("arial.ttf"); // Load system font
    configureWindowStyle();
    ShowWindow(getNativeHandle(), SW_HIDE); // Hide initially
}

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM ptr_titles) {
    char title[256];
    // If the window is visible, has a title, in taskbar, and is the root window of the app
    if (IsWindowVisible(hwnd) 
        && GetWindowText(hwnd, title, sizeof(title)) > 0
        && isWindowInTaskbarAndRoot(hwnd)) {
        
        auto* titles = reinterpret_cast<std::vector<std::string>*>(ptr_titles);
        titles->push_back(title);
    }
    return TRUE;
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

void WindowManager::run() {
    
    WindowRenderer renderer(window);
    OSearchBox searchBox(100, 150, 300, 50, font);
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (!event.has_value()) {
                continue;
            }

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            searchBox.handleEvent(*event, window);
        }
        window.clear(sf::Color::Black);
        renderer.drawWindowTitlesText(windowTitles, font);
        searchBox.draw(window);
        
        

        window.display();
    }
}
