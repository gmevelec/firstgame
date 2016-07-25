#include "shadows/ShadowBox.h"
#include "engineTester/MainGame.h"
#include "renderEngine/MasterRenderer.h"

#include <vector>

ShadowBox::ShadowBox(glm::mat4& lightViewMatrix, Camera& camera):
_lightViewMatrix(lightViewMatrix),
_camera(camera)
{
	_calculateWidthsAndHeights();
}

ShadowBox::~ShadowBox()
{
}

void		ShadowBox::update()
{
	glm::mat4 rotation = _calculateCameraRotationMatrix();
	glm::vec4 forwardVector4f = rotation * _forward;
	glm::vec3 forwardVector(forwardVector4f);

	glm::vec3 toFar = glm::vec3(forwardVector);
	toFar *= _shadowDistance;
	glm::vec3 toNear = glm::vec3(forwardVector);
	toNear *=  MasterRenderer::_NEAR_PLANE;
	glm::vec3 centerNear = toNear + _camera.getPosition();
	glm::vec3 centerFar = toFar + _camera.getPosition();

	std::vector<glm::vec4> points = _calculateFrustumVertices(rotation, forwardVector, centerNear, centerFar);

	bool first = true;
	for (glm::vec4 point : points)
	{
		if (first)
		{
			_minX = point.x;
			_maxX = point.x;
			_minY = point.y;
			_maxY = point.y;
			_minZ = point.z;
			_maxZ = point.z;
			first = false;
		}
		if (point.x > _maxX)
		{
			_maxX = point.x;
		}
		else if (point.x < _minX)
		{
			_minX = point.x;
		}
		if (point.y > _maxY)
		{
			_maxY = point.y;
		}
		else if (point.y < _minY)
		{
			_minY = point.y;
		}
		if (point.z > _maxZ)
		{
			_maxZ = point.z;
		}
		else if (point.z < _minZ)
		{
			_minZ = point.z;
		}
	}
	_maxZ += _offset;
}

glm::vec3	ShadowBox::getCenter()
{
	float x = (_minX + _maxX) / 2.0f;
	float y = (_minY + _maxY) / 2.0f;
	float z = (_minZ + _maxZ) / 2.0f;
	glm::vec4 cen = glm::vec4(x, y, z, 1);
	glm::mat4 intervetedLight;
	intervetedLight = glm::inverse(_lightViewMatrix);
	glm::vec4 ret = intervetedLight * cen;
	return (glm::vec3(ret));
}

float		ShadowBox::getWidth()
{
	return (_maxX - _minX);
}

float		ShadowBox::getHeight()
{
	return (_maxY - _minY);
}

float		ShadowBox::getLength()
{
	return (_maxZ - _minZ);
}


std::vector<glm::vec4>	ShadowBox::_calculateFrustumVertices(glm::mat4 rotation, glm::vec3 forwardVector, glm::vec3 centerNear, glm::vec3 centerFar)
{
	glm::vec4 upVector4f = rotation * _up;
	glm::vec3 upVector(upVector4f);
	glm::vec3 rightVector = glm::cross(forwardVector, upVector);
	glm::vec3 downVector(-upVector);
	glm::vec3 leftVector(-rightVector);
	glm::vec3 farTop = centerFar + glm::vec3(upVector.x * _farHeight, upVector.y * _farHeight, upVector.z * _farHeight);
	glm::vec3 farBottom = centerFar + glm::vec3(downVector.x * _farHeight, downVector.y * _farHeight, downVector.z * _farHeight);
	glm::vec3 nearTop = centerNear + glm::vec3(upVector.x * _nearHeight, upVector.y * _nearHeight, upVector.z * _nearHeight);
	glm::vec3 nearBottom = centerNear + glm::vec3(downVector.x * _nearHeight, downVector.y * _nearHeight, downVector.z * _nearHeight);

	std::vector<glm::vec4> points;
	points.resize(8);
	points[0] = _calculateLightSpaceFrustumCorner(farTop, rightVector, _farWidth);
	points[1] = _calculateLightSpaceFrustumCorner(farTop, leftVector, _farWidth);
	points[2] = _calculateLightSpaceFrustumCorner(farBottom, rightVector, _farWidth);
	points[3] = _calculateLightSpaceFrustumCorner(farBottom, leftVector, _farWidth);
	points[4] = _calculateLightSpaceFrustumCorner(nearTop, rightVector, _nearWidth);
	points[5] = _calculateLightSpaceFrustumCorner(nearTop, leftVector, _nearWidth);
	points[6] = _calculateLightSpaceFrustumCorner(nearBottom, rightVector, _nearWidth);
	points[7] = _calculateLightSpaceFrustumCorner(nearBottom, leftVector, _nearWidth);

	return (points);
}

glm::vec4	ShadowBox::_calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width)
{
	glm::vec3 point = startPoint + glm::vec3(direction.x * width, direction.y * width, direction.z * width);
	glm::vec4 point4f(point.x, point.y, point.z, 1.0f);
	point4f = _lightViewMatrix * point4f;
	return (point4f);
}

glm::mat4	ShadowBox::_calculateCameraRotationMatrix()
{
	glm::mat4 rotation;
	rotation = glm::rotate(rotation, glm::radians(-_camera.getYaw()), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(-_camera.getPitch()), glm::vec3(1, 0, 0));
	return (rotation);
}

void		ShadowBox::_calculateWidthsAndHeights()
{
	_farWidth = (float)(_shadowDistance * tan(glm::radians(MasterRenderer::_FOV)));
	_nearWidth = (float)(MasterRenderer::_NEAR_PLANE * tan(glm::radians(MasterRenderer::_FOV)));
	_farHeight = _farWidth / _getAspectRatio();
	_nearHeight = _nearWidth / _getAspectRatio();
}

float		ShadowBox::_getAspectRatio()
{
	return ((float)MainGame::screenWidth / (float)MainGame::screenHeight);
}
