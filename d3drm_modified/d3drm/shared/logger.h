#pragma once
#include <string>
#include <cstdarg>
#include <mutex>

class Logger {
public:
	Logger(std::string logFilePath);
	virtual ~Logger();

	void Clear();

	void Critical(const char* format, ...);
	void Error(const char* format, ...);
	void Warning(const char* format, ...);
	void Informational(const char* format, ...);
	void Debug(const char* format, ...);
	void Trace(const char* format, ...);

private:
	char* _logBuffer;
	std::string _logFilePath;
	void Log(const char* format, va_list arguments, const char* prefix);

	std::mutex _mutex;
};
