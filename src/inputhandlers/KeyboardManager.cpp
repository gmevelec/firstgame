#include "inputhandlers/KeyboardManager.h"

#include <fstream>
#include <sstream>
#include <string>

std::map<SDL_Keycode, bool>	KeyboardManager::key_pressed;
std::map<std::string, SDL_Keycode> KeyboardManager::key_actions;

KeyboardManager::KeyboardManager()
{
	_next = 0;
	fillKeyActionsWithFile();
}

KeyboardManager::~KeyboardManager()
{
}

void	KeyboardManager::handleEvents()
{
	SDL_Event event = _queue.top();
	if (event.type == SDL_KEYDOWN)
	{
		key_pressed[event.key.keysym.sym] = 1;
		InputManager::_queue.pop();
	}
	else if (event.type == SDL_KEYUP)
	{
		key_pressed[event.key.keysym.sym] = 0;
		InputManager::_queue.pop();
	}
	else if (event.type == SDL_TEXTEDITING)
	{
		InputManager::_queue.pop();
	}
	else if (event.type == SDL_TEXTINPUT)
	{
		InputManager::_queue.pop();
	}
	else if (event.type == SDL_KEYMAPCHANGED)
	{
		InputManager::_queue.pop();
	}
	else
	{
		InputManager::handleEvents();
	}
}

void		KeyboardManager::fillKeyActionsWithFile()
{
	std::ifstream file("./Resources/input/keyboardInput");
	std::string line;
	std::string delimiter = "=>";
	std::string token;
	std::stringstream trimmer;
	while(std::getline(file, line)) {
		if (line[0] != '#')
		{
			token = line.substr(0, line.find(delimiter));
			trimmer << token;
			token.clear();
			trimmer >> token;
			trimmer.clear();
			line.erase(0, line.find(delimiter) + delimiter.length());
			trimmer << line;
			line.clear();
			trimmer >> line;
			key_actions[token] = SDL_GetKeyFromName(line.c_str());
			trimmer.clear();
		}
	}
}