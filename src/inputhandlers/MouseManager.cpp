#include "inputhandlers/MouseManager.h"

mouseStatus_t	MouseManager::mouseStatus;

MouseManager::MouseManager()
{
	_next = 0;
}

MouseManager::~MouseManager()
{
}

void	MouseManager::handleEvents()
{
	SDL_Event event = _queue.top();

	if (event.type == SDL_MOUSEMOTION)
	{
		mouseStatus.x = event.motion.x;
		mouseStatus.y = event.motion.y;
		mouseStatus.deltaX = mouseStatus.x - mouseStatus.oldX;
		mouseStatus.deltaY = mouseStatus.y - mouseStatus.oldY;
		mouseStatus.oldX = mouseStatus.x;
		mouseStatus.oldY = mouseStatus.y;
		InputManager::_queue.pop();
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			mouseStatus.isLeftButtonPressed = true;
		}
		else
		{
			mouseStatus.isRightButtonPressed = true;
		}
		InputManager::_queue.pop();
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			mouseStatus.isLeftButtonPressed = false;
		}
		else
		{
			mouseStatus.isRightButtonPressed = false;
		}
		InputManager::_queue.pop();
	}
	else if (event.type == SDL_MOUSEWHEEL)
	{
		mouseStatus.wheel = event.wheel.y;
		InputManager::_queue.pop();
	}
	else
	{
		InputManager::handleEvents();
	}
}
