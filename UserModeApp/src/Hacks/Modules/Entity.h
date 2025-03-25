#pragma once
#include <Windows.h>
#include <vector>
#include "../../Util/Vector.h"

struct Entity {
	std::uintptr_t Entity;
	std::uintptr_t EntityController;
	std::uintptr_t EntityControllerPawn;
	std::uintptr_t EntityPawn;

	char Name[16] = { 0 };
	int Team;

	bool IsAlive;
	int Health;
	int Armor;

	bool IsOnGround;
	std::uintptr_t GameSceneNode;
	std::uintptr_t BoneArray;
	Vector3 Origin;
	Vector3 Head;
};

std::vector <Entity> GetAllEntities(const HANDLE driver_handle, const std::uintptr_t client);