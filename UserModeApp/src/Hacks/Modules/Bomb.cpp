#include "Bomb.h"

#include <iostream>

#include "../CS2MEM/client_dll.hpp"
#include "../CS2MEM/offsets.hpp"

#include "../driver.hpp"

Bomb GetBomb(const HANDLE driver_handle, const std::uintptr_t client)
{
	Bomb Bomb;

	Bomb.IsPlanted = driver::read_memory<bool>(driver_handle, client + cs2_dumper::offsets::client_dll::dwPlantedC4 - 0x8);
	if (Bomb.IsPlanted) {
		Bomb.PlantedC4 = driver::read_memory<std::uintptr_t>(driver_handle,
			driver::read_memory<std::uintptr_t>(driver_handle, client + cs2_dumper::offsets::client_dll::dwPlantedC4));

		Bomb.Site = driver::read_memory<int>(driver_handle, Bomb.PlantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_nBombSite);

		Bomb.IsBeingDefused = driver::read_memory<bool>(driver_handle, Bomb.PlantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_bBeingDefused);
		Bomb.IsDefused = driver::read_memory<bool>(driver_handle, Bomb.PlantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_bBombDefused);
		Bomb.IsExploded = driver::read_memory<bool>(driver_handle, Bomb.PlantedC4 + cs2_dumper::schemas::client_dll::C_PlantedC4::m_bHasExploded);
	}
	return Bomb;
}
