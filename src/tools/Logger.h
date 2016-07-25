/*
** This class is used to do a logging system.
** Every log is display on the terminal and write in the log_file.txt file.
*/

#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>
#include <typeinfo>

#include "tools/Type.h"

#define RED		"\x1B[31m"
#define GREEN	"\x1B[32m"
#define YELLOW	"\x1B[33m"
#define BLUE	"\x1B[34m"
#define MAGENTA	"\x1B[35m"
#define CYAN	"\x1B[36m"
#define WHITE	"\x1B[37m"
#define RESET	"\033[0m"

/*
** Enums for the type of the output.
*/
enum eLogType {FINE, INFO, DEBUG, ERROR, WARNING};

#define LOG(type, owner, msg) Logger::write(type, owner, msg)

class Logger
{
public:
	Logger();
	virtual ~Logger();

	/*
	** The output log file.
	*/
	static std::fstream	logFile;

	static std::map<eLogType, std::string> fmap;

	/*
	** Write the current date and hour.
	*/
	static void	getTime()
	{
		std::ostream out(NULL);
		time_t t = time(0);
		struct tm * now = localtime( & t );
		std::cout << std::setfill('0') << std::setw(2)
					<< (now->tm_year + 1900) << '-' 
					<< std::setfill('0') << std::setw(2)
					<< (now->tm_mon + 1) << '-'
					<< std::setfill('0') << std::setw(2)
					<< now->tm_mday << " "
					<< std::setfill('0') << std::setw(2)
					<< now->tm_hour << ":"
					<< std::setfill('0') << std::setw(2)
					<< now->tm_min << ":"
					<< std::setfill('0') << std::setw(2)
					<< now->tm_sec;
		Logger::logFile << std::setfill('0') << std::setw(2)
					<< (now->tm_year + 1900) << '-' 
					<< std::setfill('0') << std::setw(2)
					<< (now->tm_mon + 1) << '-'
					<< std::setfill('0') << std::setw(2)
					<< now->tm_mday << " "
					<< std::setfill('0') << std::setw(2)
					<< now->tm_hour << ":"
					<< std::setfill('0') << std::setw(2)
					<< now->tm_min << ":"
					<< std::setfill('0') << std::setw(2)
					<< now->tm_sec;
	}

	/*
	** This function write the tye of the info, the time, the owner and the message to display.
	**
	** @param type 		The type of the info (See enum above).
	** @param owner		The instance who own the message.
	** @param msg 		The message to display.
	*/
	static void	write(eLogType type, std::string owner, const std::string& msg)
	{
		std::cout << fmap[type] << "	";
		Logger::logFile << fmap[type] << "	";
		Logger::getTime();
		std::cout << "	"
				<< owner
				<< "	"
				<< msg << RESET << std::endl;

		Logger::logFile << "	"
				<< owner
				<< "	"
				<< msg << RESET << std::endl;
	}

};
