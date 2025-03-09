#pragma once

namespace Hacks {
	struct Setting {
		bool ShowEntityInfo;
		bool ShowBombInfo;
	};
	/*
	struct Entity {
		uintptr_t Entity;
		uintptr_t EntityController;
		uintptr_t EntityControllerPawn;
		uintptr_t EntityPawn;

		char EntityName[32];
		int EntityTeam;
		int EntityHealth;
		int EntityArmor;
	};
	struct Bomb {
		bool IsC4Planted;

		uintptr_t PlantedC4;
		bool IsBeingDefused;
		bool IsDefused;
		bool IsExploded;
		int bombSite;
	};
	*/
	void StartKernelDriver();
	Setting StartSettings(Setting Settings);
	int StartLoop(Setting Settings);
	// Entity* GetAllEntities();
};