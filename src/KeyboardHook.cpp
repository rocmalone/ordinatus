#include "KeyboardHook.h"
#include <iostream>

HHOOK keyboardHook;
void (*windowToggleCallback)() = nullptr;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardStruct = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (pKeyboardStruct->vkCode == VK_LWIN || pKeyboardStruct->vkCode == VK_RWIN) {
                std::cout << "Windows key pressed" << std::endl;
                if (windowToggleCallback) windowToggleCallback();
                return 1;
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void setKeyboardHook() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
}

void removeKeyboardHook() {
    UnhookWindowsHookEx(keyboardHook);
}

void setWindowManagerCallback(void (*callback)()) {
    windowToggleCallback = callback;
}
