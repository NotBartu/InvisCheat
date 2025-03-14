#pragma once
#include <iostream>
#include <vector>

#include "../CS2MEM/client_dll.hpp"
#include "../CS2MEM/offsets.hpp"

#include "../driver.hpp"

struct Entity {
	uintptr_t Entity;
	uintptr_t EntityController;
	uintptr_t EntityControllerPawn;
	uintptr_t EntityPawn;

	char Name[32] = { 0 };
	int Team;

	bool IsAlive;
	int Health;
	int Armor;

	bool IsOnGround;
};

std::vector <Entity> GetAllEntities(const HANDLE driver_handle, const std::uintptr_t client) {
	std::vector <Entity> Entities;
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

		Entity.Team = driver::read_memory<int>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

		Entity.IsAlive = driver::read_memory<bool>(driver_handle, Entity.EntityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive);
		if (!Entity.IsAlive)
			continue;

		Entity.Health = driver::read_memory<int>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);
		Entity.Armor = driver::read_memory<int>(driver_handle, Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);

		Entity.IsOnGround =
			driver::read_memory<uint32_t>(driver_handle,
				Entity.EntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags)
			& (1 << 0);


		uintptr_t entityNameAddress = driver::read_memory<std::uintptr_t>(driver_handle, Entity.EntityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_sSanitizedPlayerName);

		driver::read_memory_array(driver_handle, entityNameAddress, Entity.Name);

		Entities.push_back(Entity);
	}
	return Entities;
}