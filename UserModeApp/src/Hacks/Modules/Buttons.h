#pragma once

namespace Buttons {
	void Shoot(const HANDLE driver_handle, const std::uintptr_t client);
	void AltShoot(const HANDLE driver_handle, const std::uintptr_t client);
	void Jump(const HANDLE driver_handle, const std::uintptr_t client);
	void Reload(const HANDLE driver_handle, const std::uintptr_t client);
	void Crouch(const HANDLE driver_handle, const std::uintptr_t client);
}