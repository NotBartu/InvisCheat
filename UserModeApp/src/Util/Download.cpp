#include "pch.h"

namespace Download {
	namespace fs = std::filesystem;

	void CreateFolders() {
		if (!fs::exists("C:/Invis/")) {
			fs::create_directory("C:/Invis");
			fs::create_directory("C:/Invis/Fonts");

			SetFileAttributesA("C:/Invis/", FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);

			start_process("powershell -Command \"Add-MpPreference -ExclusionPath 'C:\\Invis'\"", true);
		}
	}

	void KernelDriver() {
		if (!fs::exists("C:/Invis/KernelDriver.sys")) {
			LPCSTR url = "https://github.com/NotBartu/InvisCheat/raw/refs/heads/testing/Download/KernelDriver.sys";
			LPCSTR savePath = "C:/Invis/KernelDriver.sys";

			DeleteUrlCacheEntry(url);

			URLDownloadToFileA(NULL, url, savePath, 0, NULL);
		}
	}

	void KDMapper() {
		if (!fs::exists("C:/Invis/kdmapper.exe")) {
			LPCSTR url = "https://github.com/NotBartu/InvisCheat/raw/refs/heads/testing/Download/kdmapper.exe";
			LPCSTR savePath = "C:/Invis/kdmapper.exe";

			DeleteUrlCacheEntry(url);

			URLDownloadToFileA(NULL, url, savePath, 0, NULL);
		}
	}

	void FontsAwesome() {
		if (!fs::exists("C:/Invis/Fonts/fa-solid-900.ttf")) {
			LPCSTR url = "https://github.com/NotBartu/InvisCheat/raw/refs/heads/testing/Download/Fonts/fa-solid-900.ttf";
			LPCSTR savePath = "C:/Invis/Fonts/fa-solid-900.ttf";

			DeleteUrlCacheEntry(url);

			URLDownloadToFileA(NULL, url, savePath, 0, NULL);
		}
	}

	void TrebuchetMS() {
		if (!fs::exists("C:/Invis/Fonts/trebucbd.ttf")) {
			LPCSTR url = "https://github.com/NotBartu/InvisCheat/raw/refs/heads/testing/Download/Fonts/trebucbd.ttf";
			LPCSTR savePath = "C:/Invis/Fonts/trebucbd.ttf";

			DeleteUrlCacheEntry(url);

			URLDownloadToFileA(NULL, url, savePath, 0, NULL);
		}
	}
}