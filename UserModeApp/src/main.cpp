#ifdef _WIN32

#include <iostream>
#include <Windows.h>
#include <cstring>
#include <conio.h>

#include <chrono>
#include <thread>

#include "Hacks/Hacks.h"
#include "Extra/colors.h"

int main() {
	HWND console = GetConsoleWindow();

	MoveWindow(console, 1400, 270, 500, 540, TRUE);
	SetWindowPos(console, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	ShowWindow(console, SW_NORMAL);
	SetWindowLong(console, GWL_EXSTYLE, GetWindowLong(console, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(console, 0, 255, LWA_ALPHA);

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	bool exit = false;

	Hacks::Setting Settings;
	Settings.ShowEntityInfo = true;
	Settings.ShowBombInfo = true;
	while (true) {
		std::cout << "\033[2J\033[1;1H";
		if (exit)
			return 0;

		std::cout << "Press those keys to:" << std::endl;
		std::cout << "1. Start hack" << std::endl;
		std::cout << "2. Start Kernel Driver" << std::endl;
		std::cout << "3. Open settings menu" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << std::endl;
		
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    UI::Render();
			
		}
	}
	return 0;
}

#else
#error This app can run only on PC with Windows OS.
#endif