#pragma once

namespace Hacks {
	struct Setting {
		bool ShowEntityInfo;
		bool ShowBombInfo;
	};
	void StartKernelDriver();
	Setting StartSettings(Setting Settings);
	int StartLoop(Setting Settings);
};