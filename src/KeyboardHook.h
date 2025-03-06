#ifndef KEYBOARDHOOK_H
#define KEYBOARDHOOK_H

#include <Windows.h>

void setKeyboardHook();
void removeKeyboardHook();
void setWindowManagerCallback(void (*callback)());

#endif
