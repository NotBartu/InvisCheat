#pragma once

namespace Hacks {
	struct Setting {
		bool ShowEntityInfo;
		bool ShowBombInfo;
	};
	Setting StartSettings(Setting Settings);
	int StartLoop(Setting Settings);
};