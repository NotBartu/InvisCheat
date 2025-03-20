#pragma once

#include <iostream>
#include <vector>
#include <conio.h>

#include <chrono>
#include <thread>

#include "CS2MEM/client_dll.hpp"
#include "CS2MEM/buttons.hpp"
#include "CS2MEM/offsets.hpp"

#include "Modules/Settings.hpp"
#include "Modules/Entity.hpp"
#include "Modules/Bomb.hpp"
#include "Modules/Bhop.hpp"

#include "driver.hpp"
#include "process.hpp"

#include "../Extra/colors.hpp"
#include "../Extra/console.hpp"

namespace Hacks {
	void StartKernelDriver() {
		start_process("C:\\InvisCheat\\kdmapper.exe C:\\InvisCheat\\KernelDriver.sys");
		std::this_thread::sleep_for(std::chrono::seconds(1));
		Console::Clear();
		std::cout << "Started kernel driver successfully!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	int StartLoop(Setting Settings) {
		bool showConsole = true;

		Console::Clear();

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

				SetWindowLong(Console::hWnd, GWL_EXSTYLE, GetWindowLong(Console::hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
				SetLayeredWindowAttributes(Console::hWnd, 0, 150, LWA_ALPHA);

				std::atomic_bool bhop_cancellation_token = false;

				if (Settings.UseBHOP) {
					if (Settings.UseRage) {
						std::thread Thread(StartRageBhop, std::ref(bhop_cancellation_token), driver_handle, client);
						Thread.detach();
					}
					else {
						std::thread Thread(StartLegitBhop, std::ref(bhop_cancellation_token), driver_handle, client);
						Thread.detach();
					}
				}

				while (true) {
					Console::Clear();
					if (GetAsyncKeyState(VK_END))
						break;
					if (GetAsyncKeyState(VK_INSERT))
					{
						if (showConsole)
							ShowWindow(Console::hWnd, SW_HIDE);
						else
							ShowWindow(Console::hWnd, SW_NORMAL);

						showConsole = !showConsole;
					}

					const std::uintptr_t localEntityPawn = driver::read_memory<std::uintptr_t>
						(driver_handle, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);

					const std::uintptr_t localEntityTeam = driver::read_memory<std::uintptr_t>
						(driver_handle, localEntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

					if (localEntityPawn == 0 || localEntityTeam == 0) {
						std::cout << "Local Player Pawn or Local Player Team not found. Skipping." << std::endl;
						std::this_thread::sleep_for(std::chrono::seconds(2));
						continue;
					}

					{ // Show Entities
						Console::PrintMinus();

						std::vector <Entity> AllEntities = GetAllEntities(driver_handle, client);

						for (int i = 0; i < AllEntities.size(); i++) {
							Entity Entity = AllEntities[i];

							std::cout
								<< ((Entity.Team == 2) ? Colors::Foreground::BoldBright::YELLOW : (Entity.Team == 3) ? Colors::Foreground::Bold::BLUE : Colors::Foreground::Bold::WHITE)
								<< Entity.Name << Colors::Foreground::BoldBright::WHITE
								<< " - " << ((Entity.Health <= 20) ? Colors::Foreground::BoldBright::RED : (Entity.Health <= 70) ? Colors::Foreground::BoldBright::YELLOW : Colors::Foreground::Bright::GREEN)
								<< Entity.Health << Colors::Foreground::BoldBright::WHITE << " HP - "
								<< Entity.Armor << " Armor"
								<< Colors::RESET << std::endl;
						}
					}

					{ // Show bomb
						Console::PrintMinus();
						Bomb Bomb = GetBomb(driver_handle, client);

						if (Bomb.IsPlanted) {
							std::string isC4PlantedText =
								Bomb.IsBeingDefused ? "Being Defused"
								: Bomb.IsDefused ? "Defused"
								: Bomb.IsExploded ? "Exploded"
								: "Planted";

							std::string bombSiteText =
								Bomb.Site == 0 ? "A site"
								: Bomb.Site == 1 ? "B site"
								: "Unknown";

							std::cout << "C4 - "
								<< (Bomb.IsExploded ? Colors::Foreground::BoldBright::RED : Bomb.IsDefused ? Colors::Foreground::Bright::GREEN : Bomb.IsBeingDefused ? Colors::Foreground::BoldBright::BLUE : Colors::Foreground::BoldBright::YELLOW)
								<< isC4PlantedText << Colors::RESET
								<< " at " << Colors::Foreground::BoldBright::WHITE << bombSiteText << Colors::RESET << std::endl;
						}
						else {
							std::cout << "C4 - " << Colors::Foreground::BoldBright::WHITE << "Not planted" << Colors::RESET << std::endl;
						}
					}
					Console::PrintMinus();

					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				bhop_cancellation_token = true;
			}
			CloseHandle(driver_handle);
		}
		SetWindowLong(Console::hWnd, GWL_EXSTYLE, GetWindowLong(Console::hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(Console::hWnd, 0, 255, LWA_ALPHA);

		Console::Clear();
		std::cout << "Press Enter to continue: ";
		std::cin.get();
		return 0;
	}
};