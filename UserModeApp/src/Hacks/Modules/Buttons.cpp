#include "pch.h"

constexpr std::uint32_t PlusButton = 65637;
constexpr std::uint32_t MinusButton = 256;

namespace Buttons {
	void Shoot(const HANDLE driver_handle, const std::uintptr_t client) {
		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::attack, PlusButton);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::attack, MinusButton);
	}

	void AltShoot(const HANDLE driver_handle, const std::uintptr_t client) {
		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::attack2, PlusButton);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::attack2, MinusButton);
	}

	void Jump(const HANDLE driver_handle, const std::uintptr_t client) {
		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, PlusButton);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::jump, MinusButton);
	}

	void Reload(const HANDLE driver_handle, const std::uintptr_t client) {
		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::reload, PlusButton);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::reload, MinusButton);
	}

	void Crouch(const HANDLE driver_handle, const std::uintptr_t client) {
		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::duck, PlusButton);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		driver::write_memory<std::uint32_t>(driver_handle, client + cs2_dumper::buttons::duck, MinusButton);
	}
}