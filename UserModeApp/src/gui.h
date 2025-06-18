#pragma once

constexpr std::string_view InvisVersion = "0.2";

namespace gui
{
	// constant window size
	constexpr int WIDTH = 1920;
	constexpr int HEIGHT = 1080;

	// when this changes, exit threads
	// and close menu :)
	inline bool isRunning = true;

	// winapi window vars
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };
	inline bool windowTransparent = false;

	// points for window movement
	inline POINTS position = { };

	// direct x state vars
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	// handle window creation & destruction
	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;

	// handle device creation & destruction
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	// handle ImGui creation & destruction
	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	// handle ImGui rendering
	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;

	// window functions
	void ChangeWindowTransparency() noexcept;

	// imgui windows
	inline bool StartWindow = true;
	inline bool SettingsWindow = false;
	inline bool HacksWindow = false;

	// imgui window titles
	inline const std::string StartTitle = std::string("Invis Cheat ") + std::string(InvisVersion) + std::string(" | Start");
	inline const std::string SettingsTitle = std::string("Invis Cheat ") + std::string(InvisVersion) + std::string(" | Settings");
	inline const std::string HacksTitle = std::string("Invis Cheat ") + std::string(InvisVersion) + std::string(" | Hacks");

	// MsgBox
	namespace MsgBox {
		void Show(std::string Title, std::string Line1, std::string Line2, std::string Line3) noexcept;

		inline bool Window = false;

		inline std::string Title = "MsgBox";
		inline std::string Text1 = "1.";
		inline std::string Text2 = "2.";
		inline std::string Text3 = "3.";
	}

	// handles and other things
	inline DWORD pid = 0;
	inline HANDLE driver_handle = INVALID_HANDLE_VALUE;
	inline bool isAttachmentSuccessful = false;
	inline std::uintptr_t client = 0;

	// thread tokens
	inline std::atomic_bool UseBhopToken = false;
	inline std::atomic_bool UseTriggerToken = false;
}