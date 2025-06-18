#include "pch.h"

// Ini
// mINI::INIFile INIFile("Invis.ini");
// mINI::INIStructure INI;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

void gui::ChangeWindowTransparency() noexcept
{
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

	Fonts::Base();
	Fonts::FAwesome();

	io.IniFilename = nullptr;

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	Themes::Default();

	// Ini
	// INIFile.read(INI);

	// Settings
	// Player Esp
	Settings.UseEsp = true;
	Settings.UseBoxEsp = false;
	Settings.UseSkeletonEsp = true;
	Settings.UseHeadEsp = true;
	Settings.EspShowPlayerName = false;
	Settings.EspShowPlayerHealth = true;

	// Trigger Bot
	Settings.UseTrigger;
	Settings.TriggerKey = VK_MENU;

	// Bomb Esp
	Settings.UseBombEsp = true;

	// Other
	Settings.ShowSight = true;
	Settings.UseBHOP = true;

	// Gui
	Settings.Theme = 1;
	Settings.RefreshTime = 30;

	switch (Settings.Theme) {
	case 1:
		Themes::ComfyStyle();
		break;
	default: 
		ImGui::StyleColorsDark();
		break;
	}
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	/*
	// Ini
	INI["Esp"]["UseEsp"] = Settings.UseEsp;

	INI["Esp"]["UseBoxEsp"] = Settings.UseBoxEsp;
	INI["Esp"]["UseSkeletonEsp"] = Settings.UseSkeletonEsp;
	INI["Esp"]["UseHeadEsp"] = Settings.UseHeadEsp;
	INI["Esp"]["ShowPlayerName"] = Settings.EspShowPlayerName;
	INI["Esp"]["ShowPlayerHealth"] = Settings.EspShowPlayerHealth;

	INI["Trigger"]["UseTrigger"] = Settings.UseTrigger;
	INI["Trigger"]["TriggerKey"] = Settings.TriggerKey;

	INI["Bomb"]["UseBombEsp"] = Settings.UseBombEsp;

	INI["Other"]["ShowSight"] = Settings.ShowSight;
	INI["Other"]["UseBHOP"] = Settings.UseBHOP;

	INI["Gui"]["Theme"] = Settings.Theme;
	INI["Gui"]["RefreshTime"] = Settings.RefreshTime;

	INIFile.write(INI, true);
	*/
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

void gui::MsgBox::Show(
	std::string Title, 
	std::string Line1, 
	std::string Line2, 
	std::string Line3
) noexcept {
	gui::MsgBox::Title = Title;
	gui::MsgBox::Text1 = Line1;
	gui::MsgBox::Text2 = Line2;
	gui::MsgBox::Text3 = Line3;

	gui::MsgBox::Window = true;
}