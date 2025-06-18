#include "pch.h"

constexpr std::uint32_t standing = 65665;
constexpr std::uint32_t crouching = 65667;

constexpr std::uint32_t plusButton = 65637;
constexpr std::uint32_t minusButton = 256;


void StartBhop(std::atomic_bool& UseBhop, HANDLE& driver_handle, std::uintptr_t& client) {
	while (true) {
		if (!UseBhop) { 
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue; 
		}
		Entity LocalEntity = GetLocalEntity(driver_handle, client);
		if (LocalEntity.EntityPawn == 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}

		if (GetAsyncKeyState(VK_SPACE) && (LocalEntity.fFlags == standing || LocalEntity.fFlags == crouching)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			Buttons::Jump(driver_handle, client);
		} else std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	return;
}