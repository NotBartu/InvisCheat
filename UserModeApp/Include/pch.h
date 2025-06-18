#pragma once

#pragma comment(lib, "wininet.lib")

#include <d3d9.h>
#include <filesystem>
#include <Windows.h>
#include <Wininet.h>
#include <Urlmon.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include <ctime>

#include "../src/gui.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/Custom.h"
#include "ImGui/Themes.h"
#include "ImGui/Fonts.h"
#include "ImGui/Icons.h"
#include "ImGui/Colors.h"

#include "../src/Hacks/CS2MEM/client_dll.hpp"
#include "../src/Hacks/CS2MEM/offsets.hpp"
#include "../src/Hacks/CS2MEM/buttons.hpp"

#include "../src/Hacks/driver.hpp"
#include "../src/Hacks/process.hpp"

#include "../src/Hacks/Modules/Settings.h"
#include "../src/Hacks/Modules/Buttons.h"
#include "../src/Hacks/Modules/Bhop.h"
#include "../src/Hacks/Modules/Trigger.h"
#include "../src/Hacks/Modules/Entity.h"
#include "../src/Hacks/Modules/Bomb.h"

#include "../src/Util/Vector.h"
#include "../src/Util/Calculate.h"
#include "../src/Util/TimeNDate.h"
#include "../src/Util/Download.h"
// #include "ini.h"
