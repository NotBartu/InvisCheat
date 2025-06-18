#pragma once

void StartTrigger(std::atomic_bool& UseTrigger, int& TriggerKey, HANDLE& driver_handle, std::uintptr_t& client);