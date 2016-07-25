/*
** this class is used to load the game.
*/

#pragma once

#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <stdio.h>
#include <vector>

#include "inputhandlers/InputManager.h"
#include "inputhandlers/KeyboardManager.h"
#include "inputhandlers/MouseManager.h"


class MasterRenderer;
class Light;

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	virtual ~MainGame();
	
	static int 	screenWidth;
	static int 	screenHeight;

	static long		lastFrameTime;
	static float	delta;

	void	run();

private:
	SDL_Window*		_window;
	GameState		_gameState;

	InputManager	*_im = new InputManager();
	InputManager	*_kbm = new KeyboardManager();
	InputManager	*_mm = new MouseManager();

	void		_updateFrame();
	void		_initSystems();
	void		_processInput();
	void		_gameLoop();
	void		_updateDayLight(MasterRenderer* renderer, std::vector<Light>& lights);
};
