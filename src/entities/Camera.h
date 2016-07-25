/*
** This class represents the camera.
*/

#pragma once

#include <glm/vec3.hpp>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include "entities/Player.h"

class Camera
{
public:

	/*
	** this function creates a camera with the vector vec3(0, 0, -1);
	*/
	Camera(Player* player);
	~Camera();

	glm::vec3	getPosition();
	float		getPitch();
	float		getYaw();
	float		getRoll();

	void		setPosition(glm::vec3 position);

	// Move the camera on the X axe.
	void		moveX(float dx);

	// Move the camera on the Y axe.
	void		moveY(float dy);

	// Move the camera on the Z axe.
	void		moveZ(float dz);


	void		move();

	void		invertPitch();

	float		calculateHorizontalDistance();
	float		calculateVerticalDistance();
	void		calculateZoom();
	void		calculatePitch();

	void		calculateAngleAroundPlayer();
	void		calculateCameraPosition(float horizDistance, float vertdistance);

private:
	glm::vec3	_position;
	float		_pitch = 20;
	float		_yaw = 0;	
	float		_roll = 0;

	Player*		_player;
	float		_distanceFromPlayer = 50;
	float		_angleAroundPlayer = 0;

	// float 		_mouseWheel = 0;
	// bool		_isLeftButtonPressed = false;
	// bool		_isRightButtonPressed = false;
	// float		_mouseX = 0;
	// float		_mouseY = 0;
	// float		_oldMouseX = 0;
	// float		_oldMouseY = 0;

};