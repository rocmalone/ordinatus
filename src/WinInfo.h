#ifndef WIN_INFO_H
#define WIN_INFO_H

#include <windows.h>
#include <string>

struct WinInfo {
    HWND hwnd;
    std::string title;
};

#endif // WIN_INFO_H
