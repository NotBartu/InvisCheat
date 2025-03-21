#pragma once

#include <iostream>
#include <Windows.h>

namespace Console {
    inline HWND hWnd = GetConsoleWindow();
    inline HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    void EnableAnsi();
    void Clear();
    void PrintMinus();
}