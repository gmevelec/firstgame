#include "tools/MousePicker.h"
#include "inputhandlers/MouseManager.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

MousePicker::MousePicker(Camera& camera, glm::mat4 projectionMatrix):
_camera(camera),
_projectionMatrix(projectionMatrix),
_viewMatrix(Maths::createViewMatrix(_camera))
{
}

MousePicker::~MousePicker()
{
}

void	MousePicker::update()
{
	_viewMatrix = Maths::createViewMatrix(_camera);
	_currentRay = _calculateMouseRay();
}

glm::vec3	MousePicker::_calculateMouseRay()
{
	float mouseX = MouseManager::mouseStatus.x;
	float mouseY = MouseManager::mouseStatus.y;
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = _toEyeCoords(clipCoords);
	glm::vec3 worldRay = _toWorldCoords(eyeCoords);
	return (worldRay);
}

glm::vec3	MousePicker::_toWorldCoords(glm::vec4 eyeCoords)
{
	glm::mat4 invertedView = glm::inverse(_viewMatrix);
	glm::vec4 rayworld = invertedView * eyeCoords;
	glm::vec3 mouseRay(rayworld);
	mouseRay = glm::normalize(mouseRay);
	return (mouseRay);
}

glm::vec4	MousePicker::_toEyeCoords(glm::vec4 clipCoords)
{
	glm::mat4 invertedProjection = glm::inverse(_projectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return (glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f));
}

glm::vec2	MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY)
{
	float x = (2.0f * mouseX) / (float)MainGame::screenWidth - 1.0f;
	float y = (2.0f * mouseY) / (float)MainGame::screenHeight - 1.0f;
	return (glm::vec2(x, -y));
}

glm::vec3	MousePicker::getCurrentRay()
{
	return (_currentRay);
}