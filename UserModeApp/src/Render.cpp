#include "pch.h"

void gui::Render() noexcept
{
	if (GetAsyncKeyState(VK_DELETE))
		ChangeWindowTransparency();

	if (!StartWindow && !SettingsWindow && !HacksWindow)
		StartWindow = true;
	if (!HacksWindow) {
		UseBhopToken = false;
		UseTriggerToken = false;
	}
	else {
		UseBhopToken = Settings.UseBHOP;
		UseTriggerToken = Settings.UseTrigger;
	}

	if (MsgBox::Window) {
		const std::string Title = "Invis Cheat | " + MsgBox::Title;

		ImVec2 WindowSize = ImVec2(300, 123);
		ImGui::SetNextWindowSize(WindowSize);
		ImGui::SetNextWindowPos(ImVec2(
			(WIDTH - WindowSize.x) / 2,
			(HEIGHT - WindowSize.y) / 2
		));
		ImGui::Begin(
			Title.c_str(),
			&MsgBox::Window,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		ImGui::Text("%s", MsgBox::Text1.c_str());
		ImGui::Text("%s", MsgBox::Text2.c_str());
		ImGui::Text("%s", MsgBox::Text3.c_str());

		ImGui::SetCursorPosY(ImGui::GetWindowHeight() - ImGui::GetStyle().WindowPadding.y - 21);
		if (ImGui::Button("Ok"))
			MsgBox::Window = false;

		ImGui::End();
	}

	if (StartWindow) {
		ImVec2 WindowSize = ImVec2(300, 123);
		ImGui::SetNextWindowSize(WindowSize);
		ImGui::SetNextWindowPos(ImVec2(
			WIDTH - 320,
			(HEIGHT - WindowSize.y) / 2
		));
		ImGui::Begin(
			StartTitle.c_str(),
			&isRunning,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		if (ImGui::Button("Start Hack")
			&& pid != 0
			&& driver_handle != INVALID_HANDLE_VALUE
			&& isAttachmentSuccessful == true
			&& client != 0)
		{
			HacksWindow = true;
			StartWindow = false;
		}
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			if (pid == 0
				|| driver_handle == INVALID_HANDLE_VALUE
				|| isAttachmentSuccessful == false
				|| client == 0)
			{
				if (pid == 0)
					ImGui::BulletText("Failed to find CS2");
				if (driver_handle == INVALID_HANDLE_VALUE)
					ImGui::BulletText("Failed to find Kernel Driver");
				if (isAttachmentSuccessful == false)
					ImGui::BulletText("Failed to attach to CS2");
				if (client == 0)
					ImGui::BulletText("Failed to find client.dll");
			}
			else {
				ImGui::Text("Everything is OK!");
				ImGui::Text("You Can Start Hack");
			}
			ImGui::EndTooltip();
		}

		if (pid == 0
			|| driver_handle == INVALID_HANDLE_VALUE
			|| isAttachmentSuccessful == false
			|| client == 0)
		{
			ImGui::SameLine(); ImGui::Text(" | "); ImGui::SameLine();
			if (ImGui::Button("Try to fix errors")) {
				pid = 0;
				driver_handle = INVALID_HANDLE_VALUE;
				isAttachmentSuccessful = false;
				client = 0;

				pid = get_process_id(L"cs2.exe");
				driver_handle = CreateFileW(L"\\\\.\\CheatDriver", GENERIC_READ, 0, nullptr,
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
				if (driver_handle == INVALID_HANDLE_VALUE) {
					start_process("C:\\Invis\\kdmapper.exe C:\\Invis\\KernelDriver.sys");
					driver_handle = CreateFileW(L"\\\\.\\CheatDriver", GENERIC_READ, 0, nullptr,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
				}
				if (pid != 0 && driver_handle != INVALID_HANDLE_VALUE) {
					if (driver::attach_to_process(driver_handle, pid) == true) {
						isAttachmentSuccessful = true;
						client = get_module_base(pid, L"client.dll");
					}
				}
			}
		}

		if (ImGui::Button("Settings")) {
			SettingsWindow = true;
			StartWindow = false;
		}

		ImGui::Separator();

		ImGui::Text("This Window");
		ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
		ImGui::TextColored(gui::windowTransparent ? Colors::Green : Colors::Red, gui::windowTransparent ? "Transparent" : "Not Transparent");
		ImGui::Text("%s:%s:%s %s.%s.%s",
			GetHour(), GetMinutes(), GetSeconds(),
			GetDay(), GetMonth(), GetYear()
		);

		ImGui::End();
	}

	if (SettingsWindow) {
		ImVec2 WindowSize = ImVec2(300.0f, 368.0f);
		if (Settings.UseEsp)
			WindowSize.y += 125.0f;
		if (Settings.UseTrigger)
			WindowSize.y += 25.0f;
		ImGui::SetNextWindowSize(WindowSize);
		ImGui::SetNextWindowPos(ImVec2(
			WIDTH - 320,
			(HEIGHT - WindowSize.y) / 2
		));
		ImGui::Begin(
			SettingsTitle.c_str(),
			&SettingsWindow,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		ImGui::SeparatorText("Esp");

		ImGui::Checkbox("Use Esp", &Settings.UseEsp);
		if (Settings.UseEsp) {
			ImGui::Checkbox("Use Box Esp", &Settings.UseBoxEsp);
			ImGui::Checkbox("Use Skeleton Esp", &Settings.UseSkeletonEsp);
			ImGui::Checkbox("Use Head Esp", &Settings.UseHeadEsp);
			ImGui::Checkbox("Show Player Name", &Settings.EspShowPlayerName);
			ImGui::Checkbox("Show Player Health", &Settings.EspShowPlayerHealth);
		}

		ImGui::SeparatorText("Trigger Bot (Working So Bad)");

		ImGui::Checkbox("Use Trigger Bot", &Settings.UseTrigger);
		if (Settings.UseTrigger) {
			ImGui::Hotkey("Trigger Bot Hotkey", &Settings.TriggerKey);
		}

		ImGui::SeparatorText("Bomb");

		ImGui::Checkbox("Use Bomb Esp", &Settings.UseBombEsp);

		ImGui::SeparatorText("Other");

		ImGui::Checkbox("Show Sight", &Settings.ShowSight);
		ImGui::Checkbox("Use Bhop", &Settings.UseBHOP);

		ImGui::SeparatorText("Gui");

		if (ImGui::Combo("Theme", &Settings.Theme, Themes::List, IM_ARRAYSIZE(Themes::List))) {
			switch (Settings.Theme) {
			case 1:
				Themes::ComfyStyle();
				break;
			default:
				ImGui::StyleColorsDark();
				break;
			}
		}

		ImGui::SliderInt("Refresh Time", &Settings.RefreshTime, 1, 100);

		ImGui::Separator();

		ImGui::Text("This Window");
		ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
		ImGui::TextColored(gui::windowTransparent ? Colors::Green : Colors::Red, gui::windowTransparent ? "Transparent" : "Not Transparent");
		ImGui::Text("%s:%s:%s %s.%s.%s",
			GetHour(), GetMinutes(), GetSeconds(),
			GetDay(), GetMonth(), GetYear()
		);

		ImGui::End();
	}

	if (HacksWindow) {
		ImVec2 WindowSize = ImVec2(300, 500);
		ImGui::SetNextWindowSize(WindowSize);
		ImGui::SetNextWindowPos(ImVec2(
			WIDTH - 320,
			(HEIGHT - WindowSize.y) / 2
		));
		ImGui::Begin(
			HacksTitle.c_str(),
			&HacksWindow,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		Entity LocalEntity = GetLocalEntity(driver_handle, client);

		std::vector <Entity> AllEntities = GetAllEntities(driver_handle, client);

		if (LocalEntity.EntityPawn == 0 || LocalEntity.Team == 0) {
			ImGui::SetWindowSize(ImVec2(300, 100));
			ImGui::Text("Local Player Pawn or Local Player Team not Found");
		}
		else {
			{ // Show Entities
				for (int i = 0; i < AllEntities.size(); i++) {
					Entity Entity = AllEntities[i];

					ImGui::TextColored(Entity.Team == 2 ? Colors::Orange : Entity.Team == 3 ? Colors::Blue : Colors::White, "%s%s", ICON_FA_USER, Entity.Name);
					ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
					ImGui::TextColored(Entity.Health <= 30 ? Colors::Red : Entity.Health <= 60 ? Colors::Yellow : Colors::Green, "%s%d", ICON_FA_HEART, Entity.Health);
					ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
					ImGui::TextColored(Entity.Armor <= 30 ? Colors::Red : Entity.Armor <= 60 ? Colors::Yellow : Colors::Green, "%s%d", ICON_FA_SHIELD, Entity.Armor);
				}
			}
			ImGui::Separator();
			{ // Show bomb
				Bomb Bomb = GetBomb(driver_handle, client);

				if (Bomb.IsPlanted) {
					const char* isC4PlantedText =
						Bomb.IsBeingDefused ? ICON_FA_SCISSORS "Being Defused"
						: Bomb.IsDefused ? ICON_FA_SCISSORS "Defused"
						: Bomb.IsExploded ? ICON_FA_EXPLOSION "Exploded"
						: ICON_FA_BOMB "Planted";

					const char* bombSiteText =
						Bomb.Site == 0 ? "A site"
						: Bomb.Site == 1 ? "B site"
						: "Unknown site";

					ImGui::Text("C4");
					ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
					ImGui::TextColored(Bomb.IsExploded ? Colors::Red : Bomb.IsDefused ? Colors::Green : Bomb.IsBeingDefused ? Colors::Blue : Colors::Yellow, "%s", isC4PlantedText);
					ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
					ImGui::Text("%s", bombSiteText);
				}
				else {
					ImGui::Text("C4");
					ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
					ImGui::TextColored(Colors::Gray, "Not Planted");
				}

			}
		}

		ImGui::Separator();

		ImGui::Text("This Window");
		ImGui::SameLine(); ImGui::Text(" - "); ImGui::SameLine();
		ImGui::TextColored(gui::windowTransparent ? Colors::Green : Colors::Red, gui::windowTransparent ? "Transparent" : "Not Transparent");
		ImGui::Text("%s:%s:%s %s.%s.%s",
			GetHour(), GetMinutes(), GetSeconds(),
			GetDay(), GetMonth(), GetYear()
		);

		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT));
		ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

		auto pDrawList = ImGui::GetWindowDrawList();

		const HWND ActiveWindow = GetActiveWindow();


		if (LocalEntity.EntityPawn != 0) {
			if (Settings.ShowSight) {
				pDrawList->AddLine(ImVec2(WIDTH / 2 - 10, HEIGHT / 2), ImVec2(WIDTH / 2 - 5, HEIGHT / 2), IM_COL32(0, 0, 255, 255), 2.0f);
				pDrawList->AddLine(ImVec2(WIDTH / 2, HEIGHT / 2 - 10), ImVec2(WIDTH / 2, HEIGHT / 2 - 5), IM_COL32(0, 0, 255, 255), 2.0f);

				pDrawList->AddLine(ImVec2(WIDTH / 2 + 5, HEIGHT / 2), ImVec2(WIDTH / 2 + 10, HEIGHT / 2), IM_COL32(0, 0, 255, 255), 2.0f);
				pDrawList->AddLine(ImVec2(WIDTH / 2, HEIGHT / 2 + 5), ImVec2(WIDTH / 2, HEIGHT / 2 + 10), IM_COL32(0, 0, 255, 255), 2.0f);
			}

			ViewMatrix_t ViewMatrix = driver::read_memory<ViewMatrix_t>(driver_handle, client + cs2_dumper::offsets::client_dll::dwViewMatrix);
			if (Settings.UseEsp) {
				for (int i = 0; i < AllEntities.size(); i++) {
					Entity Entity = AllEntities[i];

					const Vector3 screenPos = world_to_screen(&Entity.Origin, ViewMatrix);
					const Vector3 screenHead = world_to_screen(&Entity.Head, ViewMatrix);

					if (screenPos.z < 0.01f || !is_in_bounds(screenPos, 1920, 1080))
						continue;

					const float height = screenPos.y - screenHead.y;
					const float width = height / 2.4f;

					if (Settings.UseBoxEsp)
						pDrawList->AddRect(
							ImVec2(screenPos.x - width / 2, screenHead.y),
							ImVec2(screenHead.x + width / 2, screenHead.y + height),
							Entity.Team == 2 ? IM_COL32(255, 0, 0, 255) : Entity.Team == 3 ? IM_COL32(0, 0, 255, 255) : IM_COL32(255, 255, 255, 255));
					if (Settings.UseSkeletonEsp) {
						for (const auto& Connection : BoneConnections) {
							const std::string& BoneFrom = Connection.first;
							const std::string& BoneTo = Connection.second;

							CBones Bones = ReadBones(driver_handle, Entity.BoneArray, ViewMatrix);

							pDrawList->AddLine(
								ImVec2(Bones.BonePositions[BoneFrom].x, Bones.BonePositions[BoneFrom].y),
								ImVec2(Bones.BonePositions[BoneTo].x, Bones.BonePositions[BoneTo].y),
								Entity.Team == 2 ? IM_COL32(255, 0, 0, 255) : Entity.Team == 3 ? IM_COL32(0, 0, 255, 255) : IM_COL32(255, 255, 255, 255));
						}
					}
					if (Settings.UseHeadEsp) {
						Vector3 HeadPos = ReadHead(driver_handle, Entity.BoneArray, ViewMatrix);

						pDrawList->AddCircle(
							ImVec2(HeadPos.x, HeadPos.y),
							width / 5,
							Entity.Team == 2 ? IM_COL32(255, 0, 0, 255) : Entity.Team == 3 ? IM_COL32(0, 0, 255, 255) : IM_COL32(255, 255, 255, 255));
					}
					if (Settings.EspShowPlayerName)
						pDrawList->AddText(
							Font, 20,
							ImVec2(screenHead.x + (width / 2 + 5), screenHead.y),
							Entity.Team == 2 ? IM_COL32(255, 0, 0, 255) : Entity.Team == 3 ? IM_COL32(0, 0, 255, 255) : IM_COL32(255, 255, 255, 255),
							Entity.Name);
					if (Settings.EspShowPlayerHealth)
						pDrawList->AddText(
							Font, 20,
							ImVec2(screenHead.x + (width / 2 + 5), screenHead.y + 20),
							Entity.Health <= 30 ? IM_COL32(255, 0, 0, 255) : Entity.Health <= 60 ? IM_COL32(255, 255, 0, 255) : IM_COL32(0, 255, 0, 255),
							std::to_string(Entity.Health).c_str());
				}
			}

			if (Settings.UseBombEsp) {
				Bomb Bomb = GetBomb(driver_handle, client);

				if (Bomb.IsPlanted) {
					const Vector3 screenPos = world_to_screen(&Bomb.Origin, ViewMatrix);

					if (screenPos.z >= 0.01f) {

						const float Distance = std::round(LocalEntity.Origin.calculate_distance(screenPos) / 400.0f);

						const float height = 14 - Distance;
						const float width = height * 1.4f;

						pDrawList->AddRect(
							ImVec2(screenPos.x - width / 2, screenPos.y - height / 2),
							ImVec2(screenPos.x + width / 2, screenPos.y + height / 2),
							Bomb.IsExploded ? IM_COL32(255, 0, 0, 255) : Bomb.IsDefused ? IM_COL32(0, 255, 0, 255) : Bomb.IsBeingDefused ? IM_COL32(0, 0, 255, 255) : IM_COL32(255, 255, 0, 255));

						pDrawList->AddText(
							Font, 20,
							ImVec2(screenPos.x + (width / 2 + 5), screenPos.y),
							Bomb.IsExploded ? IM_COL32(255, 0, 0, 255) : Bomb.IsDefused ? IM_COL32(0, 255, 0, 255) : Bomb.IsBeingDefused ? IM_COL32(0, 0, 255, 255) : IM_COL32(255, 255, 0, 255),
							"C4");
					}
				}
			}
		}
		ImGui::End();
	}
}