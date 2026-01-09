#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>

class logManager {
public:
	static logManager& getInstance();

	static void logThis(const std::string& message);
	static void logThis(int value, int valueTwo);
	static void logThis(const std::string& message, int value);
	static void logThis(int value, const std::string& message);
	static void logThis(const std::string& message, const std::string& value);
	static void logThis(int value, const std::string& message, int valueTwo, const std::string& messageTwo);
	static void logThis(const std::string& message, int value, const std::string& messageTwo, int valueTwo);

	static void logThis(float value, float valueTwo);
	static void logThis(const std::string& message, float value);
	static void logThis(float value, const std::string& message); 
	static void logThis(float value, const std::string& message, float valueTwo, const std::string& messageTwo);
	static void logThis(const std::string& message, float value, const std::string& messageTwo, float valueTwo);
private:
	logManager() = default;
	~logManager() = default;

	logManager(const logManager&) = delete;
	logManager& operator=(const logManager&) = delete;

	static std::string getFormattedTimeNow();
};

#endif // LOGMANAGER_H
