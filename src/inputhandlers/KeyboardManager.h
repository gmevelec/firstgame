/*
** This class is used to handle Keyboard inputs.
*/
#pragma once

#include "inputhandlers/InputManager.h"

class KeyboardManager : public InputManager
{
public:
	KeyboardManager();
	virtual ~KeyboardManager();
	
	void	handleEvents();
	void	fillKeyActionsWithFile();

	static std::map<SDL_Keycode, bool>			key_pressed;
	static std::map<std::string, SDL_Keycode>	key_actions;

private:
	InputManager*	_next;
};