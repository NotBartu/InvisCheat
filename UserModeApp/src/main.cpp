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
		std::cout << "2. Open settings menu" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << std::endl;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		std::cout << "Choice: "; const char choice = _getch(); std::cout << choice << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		switch (choice) {
		case '1':
			Hacks::StartLoop(Settings);
			break;
		case '2':
			Settings = Hacks::StartSettings(Settings);
			break;
		case '0':
			std::cout << "Exiting." << std::endl;
			exit = true;
			break;
		default:
			break;
			
		}
	}
	return 0;
}

#else
#error This app can run only on PC with Windows OS.
#endif