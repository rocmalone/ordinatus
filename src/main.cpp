#include "WindowManager.h"
#include "KeyboardHook.h"
#include "Utils.h"

WindowManager* g_windowManager = nullptr; // Global WindowManager


// Necessary to pass a function to keyboard hook
void ToggleWindowVisibility() {
    if (g_windowManager) {
        g_windowManager->toggleVisibility();
    }
}

int main() {
    disableMinimizeAnimation();

    WindowManager windowManager;
    g_windowManager = &windowManager;

    setWindowManagerCallback(ToggleWindowVisibility);

    setKeyboardHook();
    windowManager.run();
    removeKeyboardHook();

    return 0;
}
