#pragma once

#include <iostream>
#include "../../Util/Vector.h"

#include "../CS2MEM/client_dll.hpp"
#include "../CS2MEM/offsets.hpp"

#include "../driver.hpp"

struct Bomb {
	bool IsPlanted;

	std::uintptr_t PlantedC4;

	int Site;

	bool IsBeingDefused;
	bool IsDefused;
	bool IsExploded;

	std::uintptr_t GameSceneNode;
	Vector3 Origin;
};

Bomb GetBomb(const HANDLE driver_handle, const std::uintptr_t client); 