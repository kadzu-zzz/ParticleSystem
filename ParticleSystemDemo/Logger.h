#pragma once

#include <list>
#include <string>

enum LogLevel {
	INFO,
	WARNING,
	SEVERE,
	ERROR
};
 
class Logger {
public:
	Logger();
	~Logger();

	void logMessage(LogLevel level, std::string message);

	void outputLog();
protected:
	std::string getNameForLevel(LogLevel level);

	std::list<std::string> buffer;
};

