/*
** This class is used to get to mouse coords in the world.
*/
#pragma once
#include <glm/glm.hpp>
#include <tools/Maths.h>

class Camera;

class MousePicker
{
public:
	MousePicker(Camera& camera, glm::mat4 projectionMatrix);
	~MousePicker();

	void		update();
	glm::vec2	getNormalizedDeviceCoords(float mouseX, float mouseY);
	glm::vec3	getCurrentRay();

private:
	Camera&		_camera;
	glm::vec3	_currentRay;	
	glm::mat4	_projectionMatrix;
	glm::mat4	_viewMatrix;

	glm::vec3	_calculateMouseRay();
	glm::vec4	_toEyeCoords(glm::vec4 clipCoords);
	glm::vec3	_toWorldCoords(glm::vec4 eyeCoords);

};