#include "pch.h"

Hacks::Setting Settings;

ImFont* Font;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

void ChangeWindowTransparency() {
	LONG exStyle = GetWindowLong(gui::window, GWL_EXSTYLE);

	if (!gui::windowTransparent) {
		exStyle |= WS_EX_TRANSPARENT;
	}
	else {
		exStyle &= ~WS_EX_TRANSPARENT;
	}

	gui::windowTransparent = !gui::windowTransparent;

	SetWindowLong(gui::window, GWL_EXSTYLE, exStyle);
	RedrawWindow(gui::window, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
void ShowMsgBox(std::string Title, std::string Line1, std::string Line2, std::string Line3) {
	gui::MsgBox::Title = Title;
	gui::MsgBox::Text1 = Line1;
	gui::MsgBox::Text2 = Line2;
	gui::MsgBox::Text3 = Line3;

	gui::MsgBox::Window = true;
}

std::vector<std::pair<std::string, std::string>> BoneConnections = {
	{"neck_0", "spine_1"},
	{"spine_1", "spine_2"},
	{"spine_2", "pelvis"},
	{"spine_1", "arm_upper_L"},
	{"arm_upper_L", "arm_lower_L"},
	{"arm_lower_L", "hand_L"},
	{"spine_1", "arm_upper_R"},
	{"arm_upper_R", "arm_lower_R"},
	{"arm_lower_R", "hand_R"},
	{"pelvis", "leg_upper_L"},
	{"leg_upper_L", "leg_lower_L"},
	{"leg_lower_L", "ankle_L"},
	{"pelvis", "leg_upper_R"},
	{"leg_upper_R", "leg_lower_R"},
	{"leg_lower_R", "ankle_R"}
};

static LRESULT WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}	
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(const char* windowName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "Invis";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	window = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST,
		"Invis",
		windowName,
		WS_POPUP,
		0,
		0,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);

	SetLayeredWindowAttributes(window, RGB(0, 0, 0), 0, LWA_COLORKEY);
	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	Download::CreateFolders();

	std::thread Thread1(Download::KernelDriver);
	std::thread Thread2(Download::KDMapper);
	std::thread Thread3(Download::FontsAwesome);
	std::thread Thread4(Download::TrebuchetMS);

	Thread1.join();
	Thread2.join();
	Thread3.join();
	Thread4.join();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();

	float baseFontSize = 14.0f;
	float iconFontSize = baseFontSize - 1.0f;
	Font = io.Fonts->AddFontFromFileTTF("C:/Invis/Fonts/trebucbd.ttf", baseFontSize, nullptr, io.Fonts->GetGlyphRangesCyrillic());

	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.GlyphMinAdvanceX = iconFontSize;
	io.Fonts->AddFontFromFileTTF("C:/Invis/Fonts/fa-solid-900.ttf", iconFontSize, &icons_config, icons_ranges);

	io.IniFilename = "Invis.ini";

	ComfyStyle();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	// Player Esp
	Settings.UseEsp = false;
	Settings.UseBoxEsp = false;
	Settings.UseSkeletonEsp = true;
	Settings.UseHeadEsp = true;
	Settings.EspShowPlayerName = true;
	Settings.EspShowPlayerHealth = true;

	// Bomb Esp
	Settings.UseBombEsp = true;

	// Other
	Settings.ShowSight = true;
	Settings.UseBHOP = true;
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}
	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

void gui::Render() noexcept
{
	if (GetAsyncKeyState(VK_DELETE))
		ChangeWindowTransparency();

	if (!StartWindow && !SettingsWindow && !HacksWindow)
		StartWindow = true;
	if (!HacksWindow) {
		UseBhopToken = false;
	}
	else {
		UseBhopToken = Settings.UseBHOP;
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
			"Invis Cheat | Starting",
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
		ImGui::SameLine(); ImGui::Text(" | "); ImGui::SameLine();
		if (ImGui::Button("Test MsgBox"))
			ShowMsgBox("Test MsgBox", "Test 1", "Test 2", "Test 3");

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
		ImVec2 WindowSize = ImVec2(300, 500);
		ImGui::SetNextWindowSize(WindowSize);
		ImGui::SetNextWindowPos(ImVec2(
			WIDTH - 320,
			(HEIGHT - WindowSize.y) / 2
		));
		ImGui::Begin(
			"Invis Cheat | Settings",
			&SettingsWindow,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		ImGui::Checkbox("Use Esp", &Settings.UseEsp);
		if (Settings.UseEsp) {
			ImGui::Checkbox("Use Box Esp", &Settings.UseBoxEsp);
			ImGui::Checkbox("Use Skeleton Esp", &Settings.UseSkeletonEsp);
			ImGui::Checkbox("Use Head Esp", &Settings.UseHeadEsp);
			ImGui::Checkbox("Show Player Name", &Settings.EspShowPlayerName);
			ImGui::Checkbox("Show Player Health", &Settings.EspShowPlayerHealth);
		}

		ImGui::Separator();

		ImGui::Checkbox("Use Bomb Esp", &Settings.UseBombEsp);

		ImGui::Separator();

		ImGui::Checkbox("Show Sight", &Settings.ShowSight);
		ImGui::Checkbox("Use Bhop", &Settings.UseBHOP);

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
			"Invis Cheat | Hacks",
			&HacksWindow,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		const std::uintptr_t localEntityPawn = driver::read_memory<std::uintptr_t>
			(driver_handle, client + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);

		const std::uintptr_t localEntityTeam = driver::read_memory<std::uintptr_t>
			(driver_handle, localEntityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

		const Vector3 localEntityOrigin = driver::read_memory<Vector3>
			(driver_handle, localEntityPawn + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);

		std::vector <Entity> AllEntities = GetAllEntities(driver_handle, client);

		if (localEntityPawn == 0 || localEntityTeam == 0) {
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


		if (localEntityPawn != 0) {
			if (Settings.ShowSight) {
				pDrawList->AddLine(ImVec2(WIDTH / 2 - 10, HEIGHT / 2), ImVec2(WIDTH / 2 - 5, HEIGHT / 2), ImColor(0, 0, 255), 2.0f);
				pDrawList->AddLine(ImVec2(WIDTH / 2, HEIGHT / 2 - 10), ImVec2(WIDTH / 2, HEIGHT / 2 - 5), ImColor(0, 0, 255), 2.0f);

				pDrawList->AddLine(ImVec2(WIDTH / 2 + 5, HEIGHT / 2), ImVec2(WIDTH / 2 + 10, HEIGHT / 2), ImColor(0, 0, 255), 2.0f);
				pDrawList->AddLine(ImVec2(WIDTH / 2, HEIGHT / 2 + 5), ImVec2(WIDTH / 2, HEIGHT / 2 + 10), ImColor(0, 0, 255), 2.0f);
			}

			view_matrix_t view_matrix = driver::read_memory<view_matrix_t>(driver_handle, client + cs2_dumper::offsets::client_dll::dwViewMatrix);
			if (Settings.UseEsp) {
				for (int i = 0; i < AllEntities.size(); i++) {
					Entity Entity = AllEntities[i];

					const Vector3 screenPos = world_to_screen(&Entity.Origin, view_matrix);
					const Vector3 screenHead = world_to_screen(&Entity.Head, view_matrix);

					if (screenPos.z < 0.01f || !is_in_bounds(screenPos, 1920, 1080))
						continue;

					const float height = screenPos.y - screenHead.y;
					const float width = height / 2.4f;

					if (Settings.UseBoxEsp) 
						pDrawList->AddRect(
							ImVec2(screenPos.x - width / 2, screenHead.y), 
							ImVec2(screenHead.x + width / 2, screenHead.y + height), 
							Entity.Team == 2 ? ImColor(255, 0, 0) : Entity.Team == 3 ? ImColor(0, 0, 255) : ImColor(255, 255, 255));
					if (Settings.UseSkeletonEsp) {
						for (const auto& Connection : BoneConnections) {
							const std::string& BoneFrom = Connection.first;
							const std::string& BoneTo = Connection.second;

							CBones Bones = ReadBones(driver_handle, Entity.BoneArray, view_matrix);

							pDrawList->AddLine(
								ImVec2(Bones.BonePositions[BoneFrom].x, Bones.BonePositions[BoneFrom].y), 
								ImVec2(Bones.BonePositions[BoneTo].x, Bones.BonePositions[BoneTo].y), 
								Entity.Team == 2 ? ImColor(255, 0, 0) : Entity.Team == 3 ? ImColor(0, 0, 255) : ImColor(255, 255, 255));
						}
					}
					if (Settings.UseHeadEsp) {
						Vector3 HeadPos = ReadHead(driver_handle, Entity.BoneArray, view_matrix);

						pDrawList->AddCircle(
							ImVec2(HeadPos.x, HeadPos.y),
							width / 5,
							Entity.Team == 2 ? ImColor(255, 0, 0) : Entity.Team == 3 ? ImColor(0, 0, 255) : ImColor(255, 255, 255));
					}
					if (Settings.EspShowPlayerName) 
						pDrawList->AddText(
							Font, 20, 
							ImVec2(screenHead.x + (width / 2 + 5), screenHead.y), 
							Entity.Team == 2 ? ImColor(255, 0, 0) : Entity.Team == 3 ? ImColor(0, 0, 255) : ImColor(255, 255, 255), 
							Entity.Name);
					if (Settings.EspShowPlayerHealth) 
						pDrawList->AddText(
							Font, 20, 
							ImVec2(screenHead.x + (width / 2 + 5), screenHead.y + 20), 
							Entity.Health <= 30 ? ImColor(255, 0, 0) : Entity.Health <= 60 ? ImColor(255, 255, 0) : ImColor(0, 255, 0), 
							std::to_string(Entity.Health).c_str());
				}
			}

			if (Settings.UseBombEsp) {
				Bomb Bomb = GetBomb(driver_handle, client);

				if (Bomb.IsPlanted) {
					const Vector3 screenPos = world_to_screen(&Bomb.Origin, view_matrix);

					if (screenPos.z >= 0.01f) {

						const float Distance = std::round(localEntityOrigin.calculate_distance(screenPos) / 400.0f);

						const float height = 14 - Distance;
						const float width = height * 1.4f;

						pDrawList->AddRect(
							ImVec2(screenPos.x - width / 2, screenPos.y - height / 2),
							ImVec2(screenPos.x + width / 2, screenPos.y + height / 2),
							Bomb.IsExploded ? ImColor(255, 0, 0) : Bomb.IsDefused ? ImColor(0, 255, 0) : Bomb.IsBeingDefused ? ImColor(0, 0, 255) : ImColor(255, 255, 0));

						pDrawList->AddText(
							Font, 20,
							ImVec2(screenPos.x + (width / 2 + 5), screenPos.y),
							Bomb.IsExploded ? ImColor(255, 0, 0) : Bomb.IsDefused ? ImColor(0, 255, 0) : Bomb.IsBeingDefused ? ImColor(0, 0, 255) : ImColor(255, 255, 0),
							"C4");
					}
				}
			}
		}
		ImGui::End();
	}
}