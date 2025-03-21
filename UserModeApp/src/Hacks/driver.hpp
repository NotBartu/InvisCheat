#pragma once
#pragma warning ( disable : 4312 )

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

namespace driver {
	namespace codes {
		// Used to setup the driver
		constexpr ULONG attach =
			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

		// Read process memory
		constexpr ULONG read =
			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

		// Write process memory
		constexpr ULONG write =
			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

	} // namespace codes

	struct Request {
		HANDLE process_id;

		PVOID target;
		PVOID buffer;

		SIZE_T size;
		SIZE_T return_size;
	};

	inline bool attach_to_process(HANDLE driver_handle, const DWORD pid) {
		Request r;
		r.process_id = reinterpret_cast<HANDLE>(pid);

		return DeviceIoControl(driver_handle, codes::attach, &r, sizeof(r),
			&r, sizeof(r), nullptr, nullptr);
	}

	template <class T>
	inline T read_memory(HANDLE driver_handle, const std::uintptr_t addr) {
		T temp = {};

		Request r;
		r.target = reinterpret_cast<PVOID>(addr);
		r.buffer = &temp;
		r.size = sizeof(T);

		DeviceIoControl(driver_handle, codes::read, &r, sizeof(r),
			&r, sizeof(r), nullptr, nullptr);

		return temp;
	}

	template<typename T>
	inline void read_memory_array(HANDLE driver_handle, uintptr_t address, T* buffer) {
		size_t size = sizeof(buffer);
		for (size_t i = 0; i < size; ++i) {
			buffer[i] = driver::read_memory<char>(driver_handle, address + i);
			if (buffer[i] == '\0') break;
		}
	}

	template <class T>
	inline void write_memory(HANDLE driver_handle, const std::uintptr_t addr, const T& value) {
		Request r;
		r.target = reinterpret_cast<PVOID>(addr);
		r.buffer = (PVOID)&value;
		r.size = sizeof(T);

		DeviceIoControl(driver_handle, codes::write, &r, sizeof(r),
			&r, sizeof(r), nullptr, nullptr);
	}
} // namespace driver