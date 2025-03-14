#pragma once

#include <iostream>
#include <conio.h>

#include <chrono>
#include <thread>

#include "../../Extra/console.hpp"

namespace Hacks {
	struct Setting {
		bool ShowEntityInfo;
		bool ShowBombInfo;
	};


	Setting StartSettings(Setting Settings) {
		bool exit = false;

		while (true) {
			Console::Clear();
			if (exit)
				break;

			std::cout << "Press those keys to:" << std::endl;
			std::cout << "1. Change ShowEntityInfo value" << std::endl;
			std::cout << "2. Change ShowBombInfo value" << std::endl;
			std::cout << "0. Exit" << std::endl;
			std::cout << std::endl;

			std::cout << "Choice: "; const char choice = _getch(); std::cout << choice << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			char choice1;

			switch (choice) {
			case '1':
				std::cout << "Set ShowEntityInfo (0 or 1): "; choice1 = _getch(); std::cout << choice << std::endl;
				if (choice1 == '1') {
					Settings.ShowEntityInfo = true;
				}
				else {
					Settings.ShowEntityInfo = false;
				}
				break;
			case '2':
				std::cout << "Set ShowBombInfo (0 or 1): "; choice1 = _getch(); std::cout << choice << std::endl;
				if (choice1 == '1') {
					Settings.ShowBombInfo = true;
				}
				else {
					Settings.ShowBombInfo = false;
				}
				break;
			case '0':
				std::cout << "Exiting." << std::endl;
				exit = true;
				break;
			default:
				break;
			}
		}

		return Settings;
	}
}