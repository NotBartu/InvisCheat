#include "Drawing.h"
#include "Hacks/Hacks.h"

ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;

bool Drawing::bDrawAll = true;
bool Drawing::bDrawStarterMenu = true;
bool Drawing::bDrawHackMenu = false;
bool Drawing::bDrawSettingsMenu = false;

Hacks::Setting Drawing::Settings = { true, true };

void Drawing::Active()
{
	bDrawAll = true;
	bDrawStarterMenu = true;
	bDrawSettingsMenu = false;
}

bool Drawing::isActive()
{
	return bDrawAll == true;
}

bool Drawing::isStartingMenuActive()
{
	return bDrawStarterMenu == true;
}

bool Drawing::isHackMenuActive()
{
	return bDrawHackMenu == true;
}

bool Drawing::isSettingsMenuActive()
{
	return bDrawSettingsMenu == true;
}

void Drawing::DrawAll()
{
	if (isActive()) {
		if (isStartingMenuActive())
		{
			ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
			ImGui::Begin("Starter Window", &bDrawStarterMenu, WindowFlags);
			{
				if (ImGui::Button("Start Hack")) { bDrawStarterMenu = false; bDrawHackMenu = true; }
				if (ImGui::Button("Start Kernel Driver")) Hacks::StartKernelDriver(); 
				if (ImGui::Button("Open Settings Menu")) { bDrawStarterMenu = false; bDrawSettingsMenu = true; }
				ImGui::Separator();
				if (ImGui::Button("Exit")) { bDrawAll = false; }
			}
			ImGui::End();
		}
		if (isHackMenuActive())
		{
			Hacks::Entity *Entities = Hacks::GetAllEntities();

			ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
			ImGui::Begin("Starter Window", &bDrawStarterMenu, WindowFlags);
			{
				for (int i = 0; i <= sizeof(Entities) ; i++) {
					ImGui::Text("%c - %d HP - %d Armor - %d Team", Entities[i].EntityName, Entities[i].EntityHealth, Entities[i].EntityArmor, Entities[i].EntityTeam);
				}
				ImGui::Separator();
				if (ImGui::Button("Exit")) { bDrawStarterMenu = true; bDrawHackMenu = false; }
			}
			ImGui::End();
		}
		if (isSettingsMenuActive())
		{
			ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiCond_Once);
			ImGui::Begin("Settings Window", &bDrawStarterMenu, WindowFlags);
			{
				ImGui::Checkbox("Show Entity Info", &Drawing::Settings.ShowEntityInfo);
				ImGui::Checkbox("Show Bomb Info", &Drawing::Settings.ShowBombInfo);
				ImGui::Separator();
				if (ImGui::Button("Exit")) { bDrawStarterMenu = true; bDrawSettingsMenu = false; }
			}
			ImGui::End();
		}
	}
}
