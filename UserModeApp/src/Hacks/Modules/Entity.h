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

	int Crosshair;
	std::uintptr_t ClippingWeapon;
	int WeaponId;
	int WeaponAmmo;

	int fFlags;
	bool IsOnGround;

	std::uintptr_t GameSceneNode;
	std::uintptr_t BoneArray;
	Vector3 Origin;
	Vector3 Head;
};

Entity GetEntityFromPawn(const HANDLE driver_handle, const std::uintptr_t client, std::uintptr_t EntityPawn);
Entity GetLocalEntity(const HANDLE driver_handle, const std::uintptr_t client);
std::vector <Entity> GetAllEntities(const HANDLE driver_handle, const std::uintptr_t client);
int GetEntityCount(const HANDLE driver_handle, const std::uintptr_t client);