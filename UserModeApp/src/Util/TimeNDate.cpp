#include "pch.h"

const std::tm GetTimeNDate() {
	const std::time_t time = std::time(nullptr);
	struct std::tm TimeNDate;

	localtime_s(&TimeNDate, &time);

	return TimeNDate;
}

// Date

const char* GetYear() {
	const std::tm TimeNDate = GetTimeNDate();

	static std::string s;
	s = std::to_string(TimeNDate.tm_year + 1900);

	return s.c_str();
}


const char* GetMonth() {
	const std::tm TimeNDate = GetTimeNDate();

	static std::string s;
	s = std::to_string(TimeNDate.tm_mon + 1);

	return s.c_str();
}

const char* GetDay() {
	const std::tm TimeNDate = GetTimeNDate();

	static std::string s;
	s = std::to_string(TimeNDate.tm_mday);

	return s.c_str();
}

// Time

const char* GetHour() {
	const std::tm TimeNDate = GetTimeNDate();

	static std::string s;
	s = std::to_string(TimeNDate.tm_hour);

	return s.c_str();
}

const char* GetMinutes() {
	const std::tm TimeNDate = GetTimeNDate();

	static std::string s;
	s = (TimeNDate.tm_min < 10 ? "0" : "") + std::to_string(TimeNDate.tm_min);

	return s.c_str();
}

const char* GetSeconds() {
	const std::tm TimeNDate = GetTimeNDate();

	static std::string s;
	s = (TimeNDate.tm_sec < 10 ? "0" : "") + std::to_string(TimeNDate.tm_sec);

	return s.c_str();
}