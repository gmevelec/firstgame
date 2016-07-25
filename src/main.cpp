#include "engineTester/MainGame.h"
#include "tools/Logger.h"
#include <iostream>

int main(void)
{
	try
	{
		Logger		logger;
		MainGame	mainGame;
	
		mainGame.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}