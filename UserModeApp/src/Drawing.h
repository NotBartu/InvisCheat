#ifndef DRAWING_H
#define DRAWING_H

#include "pch.h"

class Drawing
{
private:
	static ImGuiWindowFlags WindowFlags;

	static bool bDrawAll;
	static bool bDrawStarterMenu;
	static bool bDrawHackMenu;
	static bool bDrawSettingsMenu;

	static Hacks::Setting Settings;
public:
	static void Active();

	static bool isActive();
	static bool isStartingMenuActive();
	static bool isHackMenuActive();
	static bool isSettingsMenuActive();

	static void DrawAll();
};
#endif