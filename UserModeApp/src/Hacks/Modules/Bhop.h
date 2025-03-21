#pragma once
#include <Windows.h>
#include <iostream>

void StartLegitBhop(std::atomic_bool& bhop_cancellation_token, const HANDLE driver_handle, const std::uintptr_t client);
void StartRageBhop(std::atomic_bool& bhop_cancellation_token, const HANDLE driver_handle, const std::uintptr_t client);