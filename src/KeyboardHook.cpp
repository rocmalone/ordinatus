#include "KeyboardHook.h"
#include <iostream>

HHOOK keyboardHook;

// Set callback functions
void (*winKeyUpCallback)() = nullptr;
void (*winArrowCallback)(int) = nullptr;
void (*ctrlWinArrowCallback)(int) = nullptr;
void (*shiftWinArrowCallback)(int) = nullptr;

bool winKeyDown = false;
bool ctrlKeyDown = false;
bool shiftKeyDown = false;
bool openLauncherOnWinKeyUp = true;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardStruct = (KBDLLHOOKSTRUCT*)lParam;

        if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            if (pKeyboardStruct->vkCode == VK_LWIN || pKeyboardStruct->vkCode == VK_RWIN) {
                std::cout << "WIN KEY UP" << '\n';
                winKeyDown = false;
                if (openLauncherOnWinKeyUp) {
                    winKeyUpCallback();
                }
                openLauncherOnWinKeyUp = true;
            }
            if (pKeyboardStruct->vkCode == VK_LCONTROL || pKeyboardStruct->vkCode == VK_RCONTROL) {
                std::cout << "CTRL KEY UP" << '\n';
                ctrlKeyDown = false;
            }
            if (pKeyboardStruct->vkCode == VK_LSHIFT || pKeyboardStruct->vkCode == VK_RSHIFT) {
                std::cout << "SHIFT KEY UP" << '\n';
                shiftKeyDown = false;
            }
        }

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (pKeyboardStruct->vkCode == VK_LWIN || pKeyboardStruct->vkCode == VK_RWIN) {
                if (!winKeyDown) {
                    std::cout << "WIN KEY DOWN" << '\n';
                    winKeyDown = true;
                }
                return 1;
            }
            else {
                openLauncherOnWinKeyUp = false;
            }

            if (pKeyboardStruct->vkCode == VK_LCONTROL || pKeyboardStruct->vkCode == VK_RCONTROL) {
                if (!ctrlKeyDown) {
                    std::cout << "CTRL KEY DOWN" << '\n';
                    ctrlKeyDown = true;
                }
            }

            if (pKeyboardStruct->vkCode == VK_LSHIFT || pKeyboardStruct->vkCode == VK_RSHIFT) {
                if (!shiftKeyDown) {
                    std::cout << "SHIFT KEY DOWN" << '\n';
                    shiftKeyDown = true;
                }
            }

            // Detect key combinations
            if (winKeyDown) {
                if (ctrlKeyDown && ctrlWinArrowCallback) {
                    ctrlWinArrowCallback(pKeyboardStruct->vkCode);
                }
                else if (shiftKeyDown && shiftWinArrowCallback) {
                    shiftWinArrowCallback(pKeyboardStruct->vkCode);
                }
                else if (winArrowCallback) {
                    winArrowCallback(pKeyboardStruct->vkCode);
                }
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Hook setup and removal functions
void setKeyboardHook() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
}

void removeKeyboardHook() {
    UnhookWindowsHookEx(keyboardHook);
}

// Callback setters
void setWinArrowCallback(void (*callback)(int)) {
    winArrowCallback = callback;
}

void setCtrlWinArrowCallback(void (*callback)(int)) {
    ctrlWinArrowCallback = callback;
}

void setShiftWinArrowCallback(void (*callback)(int)) {
    shiftWinArrowCallback = callback;
}

void setWinKeyUpCallback(void (*callback)()) {
    winKeyUpCallback = callback;
}
