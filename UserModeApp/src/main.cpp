#include "pch.h"

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	// create gui
	gui::CreateHWindow("Invis");
	gui::CreateDevice();
	gui::CreateImGui();

	gui::pid = get_process_id(L"cs2.exe");
	gui::driver_handle = CreateFileW(L"\\\\.\\CheatDriver", GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (gui::pid != 0 && gui::driver_handle != INVALID_HANDLE_VALUE) {
		if (driver::attach_to_process(gui::driver_handle, gui::pid) == true) {
			gui::isAttachmentSuccessful = true;
			gui::client = get_module_base(gui::pid, L"client.dll");
		}
	}
	
	std::thread Thread(StartBhop, std::ref(gui::UseBhopToken), std::ref(gui::driver_handle), std::ref(gui::client));
	Thread.detach();


	while (gui::isRunning)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}