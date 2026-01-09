#include "logManager.h"
#include "json.hpp"
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
//ints
void logManager::logThis(int value, int valueTwo) {
	std::cout << "[" << getFormattedTimeNow() << "] " << value << " : " << valueTwo << std::endl;
}
void logManager::logThis(const std::string& message, int value) {
	std::cout << "[" << getFormattedTimeNow() << "] " << message << ": " << value << std::endl;
}
void logManager::logThis(int value, const std::string& message) {
	std::cout << "[" << getFormattedTimeNow() << "] " << value << ": " << message << std::endl;
}
void logManager::logThis(int value, const std::string& message, int valueTwo, const std::string& messageTwo) {
	std::cout << "[" << getFormattedTimeNow() << "] " << value << ": " << message << valueTwo << ": " << messageTwo << std::endl;
}

void logManager::logThis(const std::string& message, const std::string& value){
	std::cout << "[" << getFormattedTimeNow() << "] " << message << ": " << value << std::endl;
}

void logManager::logThis(const std::string& message, int value, const std::string& messageTwo, int valueTwo) {
	std::cout << "[" << getFormattedTimeNow() << "] " << message << ": " << value << messageTwo << ": " << valueTwo << std::endl;
}

//floats
void logManager::logThis(float value, float valueTwo) {
	std::cout << "[" << getFormattedTimeNow() << "] " << value << " : " << valueTwo << std::endl;
}
void logManager::logThis(const std::string& message, float value) {
	std::cout << "[" << getFormattedTimeNow() << "] " << message << ": " << value << std::endl;
}
void logManager::logThis(float value, const std::string& message) {
	std::cout << "[" << getFormattedTimeNow() << "] " << value << ": " << message << std::endl;
}
void logManager::logThis(float value, const std::string& message, float valueTwo, const std::string& messageTwo) {
	std::cout << "[" << getFormattedTimeNow() << "] " << value << ": " << message << valueTwo << ": " << messageTwo << std::endl;
}
 

void logManager::logThis(const std::string& message, float value, const std::string& messageTwo, float valueTwo) {
	std::cout << "[" << getFormattedTimeNow() << "] " << message << ": " << value << messageTwo << ": " << valueTwo << std::endl;
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

template<typename T>
inline void spillGuts(const T& obj) {
	nlohmann::ordered_json j = obj;
	logManager::logThis("Spilling Guts: \n", j.dump(4));
}