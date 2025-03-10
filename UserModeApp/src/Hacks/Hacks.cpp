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
	/*
	namespace CS2Attachment {
		HANDLE driver_handle = NULL;
		std::uintptr_t client = NULL;

		bool isCS2AttachmentInitialized = false;
		int initializeCS2Attachment() {
			if (!isCS2AttachmentInitialized) {
				const DWORD pid = get_process_id(L"cs2.exe");

				if (pid == 0) {
					return 1;
				}

				driver_handle = CreateFileW(L"\\\\.\\CheatDriver", GENERIC_READ, 0, nullptr,
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

				if (driver_handle == INVALID_HANDLE_VALUE) {
					driver_handle = NULL;
					return 1;
				}

				if (driver::attach_to_process(driver_handle, pid) == true) {
					if (client = get_module_base(pid, L"client.dll"); client != 0) {
						isCS2AttachmentInitialized = true;
						return 0;
					}
					else {
						return 1;
					}
				}
				else {
					return 1;
				}
			}
			else {
				return 0;
			}
		}
		void closeCS2Attachment() {
			CloseHandle(driver_handle);
			client = NULL;
			isCS2AttachmentInitialized = false;
		}
	}
	*/
	struct Setting {
		bool ShowEntityInfo;
		bool ShowBombInfo;
	};
	struct Entity {
		uintptr_t Entity;
		uintptr_t EntityController;
		uintptr_t EntityControllerPawn;
		uintptr_t EntityPawn;

		char EntityName[32] = { 0 };
		int EntityTeam;

		bool EntityIsAlive;
		int EntityHealth;
		int EntityArmor;
	
		bool EntityIsOnGround;
	};
	/*
	struct Entity {
		uintptr_t Entity;
		uintptr_t EntityController;
		uintptr_t EntityControllerPawn;
		uintptr_t EntityPawn;

		char* EntityName;
		int EntityTeam;
		int EntityHealth;
		int EntityArmor;
	};
	struct Bomb {
		bool IsC4Planted;

		uintptr_t PlantedC4;
		bool IsBeingDefused;
		bool IsDefused;
		bool IsExploded;
		int bombSite;
	};
	*/

	void StartKernelDriver() {
		start_process("C:\\InvisCheat\\kdmapper.exe C:\\InvisCheat\\KernelDriver.sys");
		std::cout << "\033[2J\033[1;1H";
		std::cout << "Started kernel driver successfully!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
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

				std::this_thread::sleep_for(std::chrono::seconds(1)); 

				SetWindowLong(console, GWL_EXSTYLE, GetWindowLong(console, GWL_EXSTYLE) | WS_EX_LAYERED);
				SetLayeredWindowAttributes(console, 0, 150, LWA_ALPHA);

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

							Entity Entity;

							Entity.Entity = driver::read_memory<std::uintptr_t>(driver_handle, EntityList + ((8 * (i & 0x7FFF) >> 9) + 16));
							if (Entity.Entity == 0)
								continue;

							Entity.EntityController = driver::read_memory<std::uintptr_t>(driver_handle, Entity.Entity + (120) * (i & 0x1FF));
							if (Entity.EntityController == 0)
								continue;

							Entity.EntityControllerPawn = driver::read_memory<std::uintptr_t>(driver_handle, Entity.EntityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
							if (Entity.EntityControllerPawn == 0)
								continue;

							Entity.Entity = driver::read_memory<std::uintptr_t>(driver_handle, EntityList + (0x8 * ((Entity.EntityControllerPawn & 0x7FFF) >> 9) + 16));
							if (Entity.Entity == 0)
								continue;

							Entity.EntityPawn = driver::read_memory<std::uintptr_t>(driver_handle, Entity.Entity + (120) * (Entity.EntityControllerPawn & 0x1FF));
							if (Entity.EntityPawn == 0)
								continue;

							Entity.EntityTeam = driver::read_memory<int>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

							Entity.EntityIsAlive = driver::read_memory<bool>(driver_handle, Entity.EntityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive);
							if (!Entity.EntityIsAlive)
								continue;

							Entity.EntityHealth = driver::read_memory<int>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
							Entity.EntityArmor = driver::read_memory<int>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);

							Entity.EntityIsOnGround = 
								driver::read_memory<uint32_t>(driver_handle, 
									Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags)
								& (1 << 0);

							const bool isEntityInBuyZone = driver::read_memory<bool>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_bInBuyZone);
							const int isEntityInBombZone = driver::read_memory<int>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_nWhichBombZone);
							std::string entityPosition;
							if (isEntityInBuyZone) {
								switch (Entity.EntityTeam) {
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

							uintptr_t entityNameAddress = driver::read_memory<std::uintptr_t>(driver_handle, Entity.EntityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_sSanitizedPlayerName);

							read_memory_array(driver_handle, entityNameAddress, Entity.EntityName);

							std::cout 
								<< ((Entity.EntityTeam == 2) ? Colors::Foreground::BoldBright::YELLOW : (Entity.EntityTeam == 3) ? Colors::Foreground::Bold::BLUE : Colors::Foreground::Bold::WHITE)
								<< i << ". " << Entity.EntityName << Colors::Foreground::BoldBright::WHITE
								<< " - " << ((Entity.EntityHealth <= 20) ? Colors::Foreground::BoldBright::RED : (Entity.EntityHealth <= 70) ? Colors::Foreground::BoldBright::YELLOW : Colors::Foreground::Bright::GREEN)
								<< Entity.EntityHealth << Colors::Foreground::BoldBright::WHITE << " HP - "
								<< Entity.EntityArmor << " Armor"
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
								<< (isExploded ? Colors::Foreground::BoldBright::RED : isDefused ? Colors::Foreground::Bright::GREEN : isBeingDefused ? Colors::Foreground::BoldBright::BLUE : Colors::Foreground::BoldBright::YELLOW) 
								<< isC4PlantedText << Colors::RESET 
								<< " at " << Colors::Foreground::BoldBright::WHITE << bombSiteText << Colors::RESET << std::endl;
						}
						else {
							isC4PlantedText = "Not planted";
							std::cout << "C4 - " << Colors::Foreground::BoldBright::WHITE << isC4PlantedText << Colors::RESET << std::endl;
						}
					}

					std::cout << "----------------------------------------------------------" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
			}
			CloseHandle(driver_handle);
		}

		ShowWindow(console, SW_RESTORE);
		SetForegroundWindow(console);
		SetWindowLong(console, GWL_EXSTYLE, GetWindowLong(console, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(console, 0, 255, LWA_ALPHA);

		std::cout << "\033[2J\033[1;1H";
		std::cout << "Press Enter to continue: ";
		std::cin.get();
	}
	/*
	Entity* GetAllEntities() {
		if (CS2Attachment::initializeCS2Attachment() != 0) {
			char unknownName[8] = "Unknown";
			Entity Unknown[1] = { 0, 0, 0, 0, unknownName, 0, 0, 0 };
			return Unknown; 
		}
		
		Entity AllEntities[64] = { 0 };

		int NextEntity = 0;
		for (int i = 0; i < 64; i++)
		{
			const uintptr_t EntityList = driver::read_memory<std::uintptr_t>(CS2Attachment::driver_handle, CS2Attachment::client + cs2_dumper::offsets::client_dll::dwEntityList);
			
			uintptr_t Entity = driver::read_memory<std::uintptr_t>(CS2Attachment::driver_handle, EntityList + ((8 * (i & 0x7FFF) >> 9) + 16));
			if (Entity == 0)
				continue;

			const uintptr_t EntityController = driver::read_memory<std::uintptr_t>(CS2Attachment::driver_handle, Entity + (120) * (i & 0x1FF));
			if (EntityController == 0)
				continue;

			const uintptr_t EntityControllerPawn = driver::read_memory<std::uintptr_t>(CS2Attachment::driver_handle, EntityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
			if (EntityControllerPawn == 0)
				continue;

			Entity = driver::read_memory<std::uintptr_t>(CS2Attachment::driver_handle, EntityList + (0x8 * ((EntityControllerPawn & 0x7FFF) >> 9) + 16));
			if (Entity == 0)
				continue;

			const uintptr_t EntityPawn = driver::read_memory<std::uintptr_t>(CS2Attachment::driver_handle, Entity + (120) * (EntityControllerPawn & 0x1FF));
			if (EntityPawn == 0)
				continue;

			const int EntityTeam = driver::read_memory<int>(CS2Attachment::driver_handle, EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

			const int EntityHealth = driver::read_memory<int>(CS2Attachment::driver_handle, EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
			if (EntityHealth == 0)
				continue;
			const int EntityArmor = driver::read_memory<int>(CS2Attachment::driver_handle, EntityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);

			uintptr_t EntityNameAddress = driver::read_memory<std::uintptr_t>(CS2Attachment::driver_handle, EntityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_sSanitizedPlayerName);
			char EntityName[32] = { 0 };
			read_memory_array(CS2Attachment::driver_handle, EntityNameAddress, EntityName);

			AllEntities[NextEntity] = { Entity, EntityController, EntityControllerPawn, EntityPawn, EntityName, EntityTeam, EntityHealth, EntityArmor };
			NextEntity++;
		}

		return AllEntities;
	}
	*/
};