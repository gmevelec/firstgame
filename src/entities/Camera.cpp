#include "entities/Camera.h"
#include "inputhandlers/MouseManager.h"

Camera::Camera(Player* player):
_player(player)
{
}

Camera::~Camera()
{

}

void		Camera::move()
{
	calculateZoom();
	calculatePitch();
	calculateAngleAroundPlayer();
	float horizontalDistance = calculateHorizontalDistance();
	float verticalDistance = calculateVerticalDistance();
	calculateCameraPosition(horizontalDistance, verticalDistance);
	_yaw = 180 - (_player->getRotation().y + _angleAroundPlayer);
}

void		Camera::invertPitch()
{
	_pitch = -_pitch;
}


float		Camera::calculateHorizontalDistance()
{
	return ((float)(_distanceFromPlayer * cos(glm::radians(_pitch))));
}

float		Camera::calculateVerticalDistance()
{
	return ((float)(_distanceFromPlayer * sin(glm::radians(_pitch))));
}

void		Camera::calculateZoom()
{
	float zoomLevel = MouseManager::mouseStatus.wheel;
	_distanceFromPlayer += zoomLevel;
	if (_distanceFromPlayer > 80)
		_distanceFromPlayer = 80;
	if (_distanceFromPlayer < 20)
		_distanceFromPlayer = 20;
	MouseManager::mouseStatus.wheel = 0;
}

void		Camera::calculatePitch()
{
	if (MouseManager::mouseStatus.isRightButtonPressed)
	{
		float pithChange = (MouseManager::mouseStatus.deltaY) * 0.1;
		_pitch -= pithChange;
		if (_pitch > 90)
			_pitch = 90;
		if (_pitch < 5)
			_pitch = 5;
		MouseManager::mouseStatus.deltaY = 0;
	}
}

void		Camera::calculateAngleAroundPlayer()
{
	if (MouseManager::mouseStatus.isRightButtonPressed)
	{
		float angleChange = (MouseManager::mouseStatus.deltaX) * 0.3;
		_angleAroundPlayer -= angleChange;
		MouseManager::mouseStatus.deltaX = 0;
	}
}

void		Camera::calculateCameraPosition(float horizDistance, float vertDistance)
{
	float theta = _player->getRotation().y + _angleAroundPlayer;
	float offsetX = (float)(horizDistance * sin(glm::radians(theta)));
	float offsetZ = (float)(horizDistance * cos(glm::radians(theta)));
	_position.x = _player->getPosition().x - offsetX;
	_position.z = _player->getPosition().z - offsetZ;
	_position.y = _player->getPosition().y + vertDistance;
}

void		Camera::moveX(float dx)
{
	_position.x += dx;
}
void		Camera::moveY(float dy)
{
	_position.y += dy;
}
void		Camera::moveZ(float dz)
{
	_position.z += dz;
}

glm::vec3	Camera::getPosition()
{
	return (_position);
}

float		Camera::getPitch()
{
	return (_pitch);
}

float		Camera::getYaw()
{
	return (_yaw);
}

float		Camera::getRoll()
{
	return (_roll);
}

void		Camera::setPosition(glm::vec3 position)
{
	_position = position;
}

