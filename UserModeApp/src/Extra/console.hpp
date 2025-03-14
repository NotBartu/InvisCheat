#pragma once

#include <iostream>
#include <Windows.h>

namespace Console {
    HWND hWnd = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    void Clear() {
        std::cout << "\033[2J\033[1;1H";
    }

    void PrintMinus() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            std::cout << std::string(width, '-') << std::endl;
        }
    }
}