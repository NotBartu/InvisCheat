#include "console.h"

#include <iostream>
#include <Windows.h>

namespace Console {
    void EnableAnsi() {
        DWORD dwMode = 0;
        GetConsoleMode(hConsole, &dwMode);
        SetConsoleMode(hConsole, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

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