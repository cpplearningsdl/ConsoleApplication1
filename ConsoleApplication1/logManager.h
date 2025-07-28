#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>

class logManager {
public:
	static logManager& getInstance();

	static void logThis(const std::string& message);
	static void logThis(const std::string& message, int value);
	static void logThis(const std::string& message, const std::string& value);
private:
	logManager() = default;
	~logManager() = default;

	logManager(const logManager&) = delete;
	logManager& operator=(const logManager&) = delete;

	static std::string getFormattedTimeNow();
};

#endif // LOGMANAGER_H
