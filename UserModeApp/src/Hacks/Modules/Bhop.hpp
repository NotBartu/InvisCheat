#pragma once

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


void StartLegitBhop(std::atomic_bool& bhop_cancellation_token, const HANDLE driver_handle, const std::uintptr_t client) {
	while (!bhop_cancellation_token.load()) {
		const std::uintptr_t localEntityPawn = driver::read_memory<std::uintptr_t>
			(driver_handle, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
		if (localEntityPawn == 0) continue;

		std::uint32_t fFlags = driver::read_memory<std::uint32_t>(driver_handle, localEntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags);

		if (GetAsyncKeyState(VK_SPACE) && (fFlags == standing || fFlags == crouching)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, plusButton);

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, minusButton);
		}
	}
}

void StartRageBhop(std::atomic_bool& bhop_cancellation_token, const HANDLE driver_handle, const std::uintptr_t client) {
	while (!bhop_cancellation_token.load()) {
		const std::uintptr_t localEntityPawn = driver::read_memory<std::uintptr_t>
			(driver_handle, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
		if (localEntityPawn == 0) continue;

		std::uint32_t fFlags = driver::read_memory<std::uint32_t>(driver_handle, localEntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags);

		if (GetAsyncKeyState(VK_SPACE) && (fFlags == standing || fFlags == crouching)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, plusButton);
			driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::duck, plusButton);

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, minusButton);
			driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::duck, minusButton);
		}
	}
}