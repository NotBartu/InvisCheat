#include <iostream>
#include <conio.h>

#include <chrono>
#include <thread>

#include "CS2MEM/client_dll.hpp"
#include "CS2MEM/offsets.hpp"

#include "driver.hpp"
#include "process.hpp"

#include "../Extra/colors.h"

template<typename T>
void read_memory_array(HANDLE driver_handle, uintptr_t address, T* buffer) {
	size_t size = sizeof(buffer);
	for (size_t i = 0; i < size; ++i) {
		buffer[i] = driver::read_memory<char>(driver_handle, address + i);
		if (buffer[i] == '\0') break;
	}
}
namespace Hacks {
	struct Setting {
		bool ShowEntityInfo;
		bool ShowBombInfo;
	};
	Setting StartSettings(Setting Settings) {
		bool exit = false;

		while (true) {
			std::cout << "\033[2J\033[1;1H";
			if (exit)
				break;

			std::cout << "Press those keys to:" << std::endl;
			std::cout << "1. Change ShowEntityInfo value" << std::endl;
			std::cout << "2. Change ShowBombInfo value" << std::endl;
			std::cout << "0. Exit" << std::endl;
			std::cout << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
	int StartLoop(Setting Settings) {
		HWND console = GetConsoleWindow();

		bool showConsole = true;

		SetWindowLong(console, GWL_EXSTYLE, GetWindowLong(console, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(console, 0, 150, LWA_ALPHA);


		std::cout << "\033[2J\033[1;1H";

		const DWORD pid = get_process_id(L"cs2.exe");

		if (pid == 0) {
			std::cout << "Failed to find cs2" << std::endl;
			std::cin.get();
			return 1;
		}

		const HANDLE driver_handle = CreateFileW(L"\\\\.\\CheatDriver", GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (driver_handle == INVALID_HANDLE_VALUE) {
			std::cout << "Failed to find driver" << std::endl;
			std::cin.get();
			return 1;
		}

		if (driver::attach_to_process(driver_handle, pid) == true) {
			std::cout << "Attachment successful!" << std::endl;

			if (const std::uintptr_t client = get_module_base(pid, L"client.dll"); client != 0) {
				std::cout << "Client found!" << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(500));

				INPUT hop;
				hop.type = INPUT_KEYBOARD;
				hop.ki.wVk = VK_APPS;
				hop.ki.dwExtraInfo = 0;
				hop.ki.time = 0;

				while (true) {
					std::cout << "\033[2J\033[1;1H"; // Clearing console
					if (GetAsyncKeyState(VK_END))
						break;
					if (GetAsyncKeyState(VK_INSERT)) 
						{
							if (showConsole)
								ShowWindow(console, SW_HIDE);
							else
								ShowWindow(console, SW_NORMAL);

							showConsole = !showConsole;
						}

					const auto localEntityPawn = driver::read_memory<std::uintptr_t>
						(driver_handle, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);

					const auto localEntityTeam = driver::read_memory<std::uintptr_t>
						(driver_handle, localEntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

					if (localEntityPawn == 0 || localEntityTeam == 0) {
						std::cout << "Local Player Pawn or Local Player Team not found. Skipping." << std::endl;
						std::this_thread::sleep_for(std::chrono::seconds(2));
						continue;
					}

					if (Settings.ShowEntityInfo) {
						std::cout << "----------------------------------------------------------" << std::endl;
						for (int i = 0; i < 64; i++)
						{

							const uintptr_t EntityList = driver::read_memory<std::uintptr_t>(driver_handle, client + cs2_dumper::offsets::client_dll::dwEntityList);

							uintptr_t Entity = driver::read_memory<std::uintptr_t>(driver_handle, EntityList + ((8 * (i & 0x7FFF) >> 9) + 16));
							if (Entity == 0)
								continue;

							const uintptr_t entityController = driver::read_memory<std::uintptr_t>(driver_handle, Entity + (120) * (i & 0x1FF));
							if (entityController == 0)
								continue;

							const uintptr_t entityControllerPawn = driver::read_memory<std::uintptr_t>(driver_handle, entityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
							if (entityControllerPawn == 0)
								continue;

							Entity = driver::read_memory<std::uintptr_t>(driver_handle, EntityList + (0x8 * ((entityControllerPawn & 0x7FFF) >> 9) + 16));
							if (Entity == 0)
								continue;

							const uintptr_t entityPawn = driver::read_memory<std::uintptr_t>(driver_handle, Entity + (120) * (entityControllerPawn & 0x1FF));
							if (entityPawn == 0)
								continue;

							const int entityTeam = driver::read_memory<int>(driver_handle, entityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

							const int entityHealth = driver::read_memory<int>(driver_handle, entityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
							if (entityHealth == 0)
								continue;
							const int entityArmor = driver::read_memory<int>(driver_handle, entityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);

							const bool isEntityInBuyZone = driver::read_memory<bool>(driver_handle, entityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_bInBuyZone);
							const int isEntityInBombZone = driver::read_memory<int>(driver_handle, entityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_nWhichBombZone);
							std::string entityPosition;
							if (isEntityInBuyZone) {
								switch (entityTeam) {
								case 2:
									entityPosition = " - at T spawn";
									break;
								case 3:
									entityPosition = " - at CT spawn";
									break;
								default:
									entityPosition = "";
									break;
								}
							}
							else if (isEntityInBombZone != 0) {
								switch (isEntityInBombZone) {
								case 1:
									entityPosition = " - at A site";
									break;
								case 2:
									entityPosition = " - at B site";
									break;
								default:
									entityPosition = "";
									break;
								}
							}

							uintptr_t entityNameAddress = driver::read_memory<std::uintptr_t>(driver_handle, entityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_sSanitizedPlayerName);

							char entityName[32] = { 0 };
							read_memory_array(driver_handle, entityNameAddress, entityName);

							std::cout 
								<< ((entityTeam == 2) ? Colors::BOLDBRIGHTYELLOW : (entityTeam == 3) ? Colors::BOLDBLUE : Colors::BOLDWHITE)
								<< i << ". " << entityName << Colors::BOLDBRIGHTWHITE
								<< " - " << ((entityHealth <= 20) ? Colors::BOLDBRIGHTRED : (entityHealth <= 70) ? Colors::BOLDBRIGHTYELLOW : Colors::BRIGHTGREEN)
								<< entityHealth << Colors::BOLDBRIGHTWHITE << " HP - "
								<< entityArmor << " Armor" 
								<< entityPosition << Colors::RESET << std::endl;

						}
					}

					if (Settings.ShowBombInfo) {
						std::cout << "----------------------------------------------------------" << std::endl;
						const bool isC4Planted = driver::read_memory<bool>(driver_handle, client + cs2_dumper::offsets::client_dll::dwPlantedC4 - 0x8);

						std::string isC4PlantedText;
						std::string bombSiteText = "Unknown";

						if (isC4Planted) {
							isC4PlantedText = "Planted";

							const auto plantedC4 = driver::read_memory<std::uintptr_t>(driver_handle,
								driver::read_memory<std::uintptr_t>(driver_handle, client + cs2_dumper::offsets::client_dll::dwPlantedC4));

							const bool isBeingDefused = driver::read_memory<bool>(driver_handle, plantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_bBeingDefused);
							if (isBeingDefused)
								isC4PlantedText = "Being Defused";

							const bool isDefused = driver::read_memory<bool>(driver_handle, plantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_bBombDefused);
							if (isDefused)
								isC4PlantedText = "Defused";

							const bool isExploded = driver::read_memory<bool>(driver_handle, plantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_bHasExploded);
							if (isExploded)
								isC4PlantedText = "Exploded";

							int bombSite = driver::read_memory<int>(driver_handle, plantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_nBombSite);
							if (bombSite == 0)
								bombSiteText = "A site";
							else if (bombSite == 1)
								bombSiteText = "B site";
							else
								bombSiteText = "Unknown";

							std::cout << "C4 - " 
								<< (isExploded ? Colors::BOLDBRIGHTRED : isDefused ? Colors::BRIGHTGREEN : isBeingDefused ? Colors::BOLDBRIGHTBLUE : Colors::BOLDBRIGHTYELLOW) 
								<< isC4PlantedText << Colors::RESET 
								<< " at " << Colors::BOLDBRIGHTWHITE << bombSiteText << Colors::RESET << std::endl;
						}
						else {
							isC4PlantedText = "Not planted";
							std::cout << "C4 - " << Colors::BOLDBRIGHTWHITE << isC4PlantedText << Colors::RESET << std::endl;
						}
					}

					std::cout << "----------------------------------------------------------" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
			}
			CloseHandle(driver_handle);
		}

		ShowWindow(console, SW_NORMAL);
		SetWindowLong(console, GWL_EXSTYLE, GetWindowLong(console, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(console, 0, 255, LWA_ALPHA);

		std::cout << "\033[2J\033[1;1H";
		std::cout << "Press Enter to continue: ";
		std::cin.get();
	}
};