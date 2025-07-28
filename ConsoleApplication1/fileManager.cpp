#include "fileManager.h"
#include <fstream>
#include <sstream>
#include <iostream> 

std::string fileManager::openTextFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "Failed to open text file: " << filePath << "\n";
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
 