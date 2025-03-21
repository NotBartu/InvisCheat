#pragma once
#include <Windows.h>
#include <vector>

struct Entity {
	std::uintptr_t Entity;
	std::uintptr_t EntityController;
	std::uintptr_t EntityControllerPawn;
	std::uintptr_t EntityPawn;

	char Name[32] = { 0 };
	int Team;

	bool IsAlive;
	int Health;
	int Armor;

	bool IsOnGround;
};

std::vector <Entity> GetAllEntities(const HANDLE driver_handle, const std::uintptr_t client);