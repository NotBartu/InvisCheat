#pragma once
#include <Windows.h>
#include <iostream>

void StartBhop(std::atomic_bool& UseRage, std::atomic_bool& UseBhop, HANDLE& driver_handle, std::uintptr_t& client);