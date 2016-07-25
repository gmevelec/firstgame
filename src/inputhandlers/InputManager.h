/*
** This class is the main manager for input handling.
*/
#pragma once

#include <stack>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include "tools/Logger.h"


class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	
	virtual void	handleEvents();
	void			addEventToQueue(SDL_Event event);

	void			setNext(InputManager* next);
	void			add(InputManager* next);

	std::stack<SDL_Event>& getQueue();

protected:
	static std::stack<SDL_Event>	_queue;

private:
	InputManager*			_next;

};