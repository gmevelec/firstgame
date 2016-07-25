/*
** This class is used to handle Mouse inputs.
*/
#pragma once

#include "inputhandlers/InputManager.h"

typedef struct 	mouseStatus_s
{
	bool			isLeftButtonPressed = 0;
	bool			isRightButtonPressed = 0;
	int 			x = 0;
	int 			y = 0;
	int 			oldX = 0;
	int 			oldY = 0;
	int 			deltaX = 0;
	int 			deltaY = 0;
	int 			wheel = 0;
}				mouseStatus_t;

class MouseManager : public InputManager
{
public:
	MouseManager();
	virtual ~MouseManager();
	
	void	handleEvents();

	static mouseStatus_t	mouseStatus;
private:
	InputManager*	_next;
};