#include "pch.h"

void StartTrigger(std::atomic_bool& UseTrigger, int& TriggerKey, HANDLE& driver_handle, std::uintptr_t& client) {
	while (true) {
		if (!UseTrigger) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}

		Entity LocalEntity = GetLocalEntity(driver_handle, client);

		if (LocalEntity.EntityPawn == 0 || LocalEntity.Crosshair == 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}
		
		const uintptr_t EntityList = driver::read_memory<std::uintptr_t>(driver_handle, client + cs2_dumper::offsets::client_dll::dwEntityList);

		std::uintptr_t ListEntry = driver::read_memory<std::uintptr_t>(driver_handle, EntityList + 8 * (LocalEntity.Crosshair >> 9) + 0x10);
		std::uintptr_t CrossEntityPawn = driver::read_memory<std::uintptr_t>(driver_handle, ListEntry + 120 * (LocalEntity.Crosshair & 0x1FF));

		Entity CrossEntity = GetEntityFromPawn(driver_handle, client, CrossEntityPawn);

		if (CrossEntity.IsAlive && CrossEntity.Team != LocalEntity.Team && CrossEntity.Team != 0 && GetAsyncKeyState(TriggerKey)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			Buttons::Shoot(driver_handle, client);
			continue;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return;
}