#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>

HHOOK keyboardHook; // Hook for global keyboard events
sf::RenderWindow* windowPtr = nullptr;
bool isWindowVisible = false;

HWND GetSFMLWindowHandle(sf::RenderWindow& window) {
    return static_cast<HWND>(window.getNativeHandle());
}

/// <summary>
/// Disable the animation for minimizing the launcher
/// </summary>
/// <returns></returns>
static bool DisableMinimizeAnimation() {
    ANIMATIONINFO animInfo;
    animInfo.cbSize = sizeof(animInfo);
    animInfo.iMinAnimate = 0; // Disable animation

    return SystemParametersInfo(SPI_SETANIMATION, sizeof(animInfo), &animInfo, 0);
}

static bool EnableMinimizeAnimation() {
    ANIMATIONINFO animInfo;
    animInfo.cbSize = sizeof(animInfo);
    animInfo.iMinAnimate = 1; // Enable animation

    return SystemParametersInfo(SPI_SETANIMATION, sizeof(animInfo), &animInfo, 0);
}


void ToggleSFMLWindowVisibility() {
    if (!windowPtr)
        return;

    HWND hwnd = GetSFMLWindowHandle(*windowPtr);
    if (!isWindowVisible) {
        ShowWindow(hwnd, SW_SHOW);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // Always on top
        isWindowVisible = true;
    }
    else {
        DisableMinimizeAnimation();
        ShowWindow(hwnd, SW_HIDE);
        isWindowVisible = false;
        EnableMinimizeAnimation();
    }
}


static void ConfigureWindowStyle(HWND hwnd) {
    // Get current window style
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

    // Remove WS_EX_APPWINDOW (show taskbar icon) and add WS_EX_TOOLWINDOW (no taskbar icon)
    style &= ~WS_EX_APPWINDOW;
    style |= WS_EX_TOOLWINDOW;

    // Apply style
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, style);
}

// Low-level keyboard hook callback function
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardStruct = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (pKeyboardStruct->vkCode == VK_LWIN || pKeyboardStruct->vkCode == VK_RWIN) {
                std::cout << "Windows key pressed" << std::endl;
                ToggleSFMLWindowVisibility();
                
                return 1; // Block Windows key default behavior
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void SetKeyboardHook() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
}

void RemoveKeyboardHook() {
    UnhookWindowsHookEx(keyboardHook);
}

int main()
{
    SetKeyboardHook();
    

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project", sf::Style::None);
    window.setFramerateLimit(144);
    windowPtr = &window;

    ConfigureWindowStyle(GetSFMLWindowHandle(window));

    // Hide the launcher window initially
    ShowWindow(GetSFMLWindowHandle(window), SW_HIDE);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
    RemoveKeyboardHook();

    return 0;
}
