#include "Fonts.h"
#include "imgui.h"
#include "Icons.h"

namespace Fonts {
	// All Icons
	constexpr float baseFontSize = 14.0f;
	constexpr float iconFontSize = baseFontSize - 1.0f;

	void Base() {
		ImGuiIO& io = ::ImGui::GetIO();
		Font = io.Fonts->AddFontFromFileTTF("C:/Invis/Fonts/trebucbd.ttf", baseFontSize, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	}
	void FAwesome() {
		ImGuiIO& io = ::ImGui::GetIO();

		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.GlyphMinAdvanceX = iconFontSize;

		io.Fonts->AddFontFromFileTTF("C:/Invis/Fonts/fa-solid-900.ttf", iconFontSize, &icons_config, icons_ranges);
	}
}