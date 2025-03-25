#include "Bhop.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "../CS2MEM/client_dll.hpp"
#include "../CS2MEM/offsets.hpp"
#include "../CS2MEM/buttons.hpp"

#include "../driver.hpp"

constexpr std::uint32_t standing = 65665;
constexpr std::uint32_t crouching = 65667;

constexpr std::uint32_t plusButton = 65637;
constexpr std::uint32_t minusButton = 256;


void StartBhop(std::atomic_bool& UseRage, std::atomic_bool& UseBhop, HANDLE& driver_handle, std::uintptr_t& client) {
	while (true) {
		if (!UseBhop) continue;
		const std::uintptr_t localEntityPawn = driver::read_memory<std::uintptr_t>
			(driver_handle, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
		if (localEntityPawn == 0) continue;

		const std::uint32_t fFlags = driver::read_memory<std::uint32_t>(driver_handle, localEntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags);

		if (GetAsyncKeyState(VK_SPACE) && (fFlags == standing || fFlags == crouching)) {
			if (UseRage) {
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, plusButton);
				driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::duck, plusButton);

				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, minusButton);
				driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::duck, minusButton);
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, plusButton);

				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, minusButton);
			}
		}
	}
	return;
}