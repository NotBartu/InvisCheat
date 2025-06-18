#pragma once

namespace Hacks {
	struct Setting {
		// Player Esp
		bool UseEsp;
		bool UseBoxEsp;
		bool UseSkeletonEsp;
		bool UseHeadEsp;
		bool EspShowPlayerName;
		bool EspShowPlayerHealth;

		// Trigger Bot
		bool UseTrigger;
		int TriggerKey;

		// Bomb Esp
		bool UseBombEsp;

		// Other
		bool ShowSight;
		bool UseBHOP;

		// Gui
		int Theme;
		int RefreshTime;
	};
}

inline Hacks::Setting Settings;