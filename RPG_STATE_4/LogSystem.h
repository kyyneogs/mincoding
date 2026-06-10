#pragma once

#include <string>

class LogSystem {
public:
	LogSystem() = default;
	~LogSystem() = default;

	void log(const std::string& what);
private:
};