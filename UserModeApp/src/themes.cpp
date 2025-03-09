#include "imgui/imgui.h"

namespace Theme {
    void SoftBlackTheme() {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowPadding = ImVec2(8, 8);
        style.WindowRounding = 6;
        style.FramePadding = ImVec2(5, 3);
        style.FrameRounding = 3.0f;
        style.ItemSpacing = ImVec2(5, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.IndentSpacing = 21;
        style.ScrollbarSize = 10.0f;
        style.ScrollbarRounding = 13;
        style.GrabMinSize = 8;
        style.GrabRounding = 1;
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.Alpha = 0.7f;

        style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.80f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.50f, 0.50f, 1.0f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.66f, 0.66f, 0.66f, 1.0f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.66f, 0.66f, 0.66f, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.70f, 0.70f, 0.73f, 1.0f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.0f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.0f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.0f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.70f, 0.70f, 0.73f, 1.0f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.95f, 0.95f, 0.70f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.70f, 0.70f, 0.73f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95f, 0.95f, 0.70f, 1.0f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 0.25f, 0.15f, 1.0f);
    }
    void SoftBlueTheme() {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowPadding = ImVec2(8, 8);
        style.WindowRounding = 6;
        style.FramePadding = ImVec2(5, 3);
        style.FrameRounding = 3.0f;
        style.ItemSpacing = ImVec2(5, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.IndentSpacing = 21;
        style.ScrollbarSize = 10.0f;
        style.ScrollbarRounding = 13;
        style.GrabMinSize = 8;
        style.GrabRounding = 1;
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.Alpha = 0.7f;

        style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.93, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.45f, 1.0f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.0f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.13f, 0.15f, 1.0f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.35f, 1.0f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.20f, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.28f, 1.0f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.34f, 1.0f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.17f, 1.0f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.12f, 1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.17f, 1.0f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.35f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.45f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.55f, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.70f, 0.70f, 0.90f, 1.0f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.90f, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.80f, 0.90f, 1.0f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.20f, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.60f, 0.60f, 0.90f, 1.0f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.28f, 0.56f, 0.96f, 1.0f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.23f, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.28f, 1.0f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.34f, 1.0f);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.40f, 0.40f, 0.45f, 1.0f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.50f, 0.50f, 0.55f, 1.0f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.60f, 0.60f, 0.65f, 1.0f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.20f, 0.23f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.25f, 0.28f, 1.0f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30f, 0.30f, 0.34f, 1.0f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.64f, 1.0f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.70f, 0.70f, 0.75f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.61f, 0.61f, 0.64f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.70f, 0.70f, 0.75f, 1.0f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.30f, 0.34f, 1.0f);
    }
}