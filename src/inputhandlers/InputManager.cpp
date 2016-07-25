#include "InputManager.h"

std::stack<SDL_Event> InputManager::_queue;

InputManager::InputManager()
{
	_next = 0;
}

InputManager::~InputManager()
{
}

void	InputManager::handleEvents()
{

	if (!InputManager::_queue.empty())
	{
		if (_next)
		{
			_next->handleEvents();
		}
		else
		{
			LOG(WARNING, type(this), "Can't handle that request. Need a new InputManager. type = " + to_string(InputManager::_queue.top().type));
			InputManager::_queue.pop();
		}
	}
}
void	InputManager::addEventToQueue(SDL_Event event)
{
	InputManager::_queue.push(event);
}

void	InputManager::setNext(InputManager* next)
{
	_next = next;
}
void	InputManager::add(InputManager* next)
{
	if (_next)
	{
		_next->add(next);
	}
	else
	{
		_next = next;
	}
}

std::stack<SDL_Event>&	InputManager::getQueue()
{
	return (InputManager::_queue);
}