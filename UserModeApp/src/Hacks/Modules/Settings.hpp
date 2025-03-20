#pragma once

#include <iostream>
#include <conio.h>

#include <chrono>
#include <thread>

#include "../../Extra/console.hpp"

namespace Hacks {
	struct Setting {
		bool UseRage;
		bool UseBHOP;
	};


	Setting StartSettings(Setting Settings) {
		bool exit = false;

		while (true) {
			Console::Clear();
			if (exit)
				break;

			std::cout << "Press those keys to:" << std::endl;
			std::cout << "1. Set Legit or Rage" << std::endl;
			std::cout << "2. Change BHOP value" << std::endl;
			std::cout << "0. Exit" << std::endl;
			std::cout << std::endl;

			std::cout << "Choice: "; const char choice = _getch(); std::cout << choice << std::endl << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			char choice1;

			switch (choice) {
			case '1':
				std::cout << "Set Legit or Rage (0 or 1): "; choice1 = _getch(); std::cout << choice << std::endl;
				choice1 == '1' ? Settings.UseRage = true : Settings.UseRage = false;
				break;
			case '2':
				std::cout << "Set BHOP value (0 or 1): "; choice1 = _getch(); std::cout << choice << std::endl;
				choice1 == '1' ? Settings.UseBHOP = true : Settings.UseBHOP = false;
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