#include "tools/Logger.h"
#include <ctime>

std::fstream	Logger::logFile;

std::map<eLogType, std::string> Logger::fmap;

Logger::Logger()
{
	Logger::fmap[FINE] = std::string(GREEN) + "[FINE]	";
	Logger::fmap[INFO] = std::string(WHITE) + "[INFO]	";
	Logger::fmap[DEBUG] = std::string(CYAN) + "[DEBUG]	";
	Logger::fmap[ERROR] = std::string(RED) + "[ERROR]	";
	Logger::fmap[WARNING] = std::string(YELLOW) + "[WARNING]";
	Logger::logFile.open("log_file.txt", std::fstream::out);
	Logger::logFile << "-----------------------------START-----------------------------" << std::endl;
	std::cout << "-----------------------------START-----------------------------" << std::endl;
}

Logger::~Logger()
{
	Logger::logFile << "------------------------------END------------------------------" << std::endl;
	std::cout << "------------------------------END------------------------------" << std::endl;
	Logger::logFile.close();
}
