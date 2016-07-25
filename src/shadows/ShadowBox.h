#pragma once

#include "entities/Camera.h"

#include <glm/glm.hpp>

class ShadowBox
{
public:
	ShadowBox(glm::mat4& lightViewMatrix, Camera& camera);
	virtual ~ShadowBox();

	void		update();
	glm::vec3	getCenter();
	float		getWidth();
	float		getHeight();
	float		getLength();

private:
	float		_offset = 10;
	glm::vec4	_up = glm::vec4(0, 1, 0, 0);
	glm::vec4	_forward = glm::vec4(0, 0, -1, 0);
	float		_shadowDistance = 100;

	float		_minX, _maxX;
	float		_minY, _maxY;
	float		_minZ, _maxZ;

	glm::mat4&	_lightViewMatrix;
	Camera&		_camera;

	float		_farHeight;
	float		_farWidth;
	float		_nearHeight;
	float		_nearWidth;

	std::vector<glm::vec4>	_calculateFrustumVertices(glm::mat4 rotation, glm::vec3 forwardVector, glm::vec3 centerNear, glm::vec3 centerFar);
	glm::vec4	_calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width);
	glm::mat4	_calculateCameraRotationMatrix();
	void		_calculateWidthsAndHeights();
	float		_getAspectRatio();
};
