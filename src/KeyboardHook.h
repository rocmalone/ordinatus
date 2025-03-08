#ifndef KEYBOARDHOOK_H
#define KEYBOARDHOOK_H

#include <Windows.h>

void setKeyboardHook();
void removeKeyboardHook();
void setWinKeyUpCallback(void (*callback)());
void setWinArrowCallback(void (*callback)(int));
void setCtrlWinArrowCallback(void (*callback)(int));
void setShiftWinArrowCallback(void (*callback)(int));


#endif
