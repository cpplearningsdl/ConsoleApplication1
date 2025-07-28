#include "logManager.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

logManager& logManager::getInstance() {
	static logManager instance;
	return instance;
}

void logManager::logThis(const std::string& message) { 
	std::cout << "[" << getFormattedTimeNow() << "] " << message << std::endl;
}
void logManager::logThis(const std::string& message, int value) {
	std::cout << "[" << getFormattedTimeNow() << "] " << message << ": " << value << std::endl;
}
void logManager::logThis(const std::string& message, const std::string& value){
	std::cout << "[" << getFormattedTimeNow() << "] " << message << ": " << value << std::endl;
}




std::string logManager::getFormattedTimeNow() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	std::tm timeStruct;
	localtime_s(&timeStruct, &now_c);

	std::ostringstream oss;
	oss << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}
