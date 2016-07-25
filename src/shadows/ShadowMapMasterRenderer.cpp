#include "shadows/ShadowMapMasterRenderer.h"

#include <math.h>

ShadowMapMasterRenderer::ShadowMapMasterRenderer(Camera& camera):
_shadowFbo(ShadowFrameBuffer(_shadowMapSize, _shadowMapSize)),
_shader(ShadowShader()),
_shadowBox(ShadowBox(_lightViewMatrix, camera)),
_entityRenderer(ShadowMapEntityRenderer(_shader, _projectionViewMatrix))
{
}

ShadowMapMasterRenderer::~ShadowMapMasterRenderer()
{
}

void		ShadowMapMasterRenderer::render(tMap entities, Light sun)
{
	_shadowBox.update();
	glm::vec3 sunPosition = sun.getPosition();
	glm::vec3 lightDirection = glm::vec3(-sunPosition);
	_prepare(lightDirection, _shadowBox);
	_entityRenderer.render(entities);
	_finish();
}

glm::mat4	ShadowMapMasterRenderer::getToShadowMapSpaceMatrix()
{
	return (_offset * _projectionViewMatrix);
}

void		ShadowMapMasterRenderer::cleanUp()
{
	_shader.cleanUp();
	_shadowFbo.cleanUp();
}

int			ShadowMapMasterRenderer::getShadowMap()
{
	return (_shadowFbo.getShadowMap());
}

glm::mat4	ShadowMapMasterRenderer::getLightSpaceTransform()
{
	return (_lightViewMatrix);
}

void		ShadowMapMasterRenderer::_prepare(glm::vec3 lightDirection, ShadowBox box)
{
	_updateOrthoProjectionMatrix(box.getWidth(), box.getHeight(), box.getLength());
	_updateLightViewMatrix(lightDirection, box.getCenter());
	_projectionViewMatrix = _projectionMatrix * _lightViewMatrix;
	_shadowFbo.bindFrameBuffer();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	_shader.start();
}

void		ShadowMapMasterRenderer::_finish()
{
	_shader.stop();
	_shadowFbo.unbindFrameBuffer();
}

void		ShadowMapMasterRenderer::_updateLightViewMatrix(glm::vec3 direction, glm::vec3 center)
{
	direction = glm::normalize(direction);
	center = glm::vec3(-center);
	_lightViewMatrix = glm::mat4(1.0);
	float pitch = (float)acos(glm::length(glm::vec2(direction.x, direction.y)));
	_lightViewMatrix = glm::rotate(_lightViewMatrix, pitch, glm::vec3(1, 0, 0));
	float yaw = (float)glm::degrees(((float)atan(direction.x / direction.z)));
	yaw = direction.z > 0 ? yaw - 180 : yaw;
	_lightViewMatrix = glm::rotate(_lightViewMatrix, -glm::radians(yaw), glm::vec3(0, 1, 0));
	_lightViewMatrix = glm::translate(_lightViewMatrix, center);
}

void		ShadowMapMasterRenderer::_updateOrthoProjectionMatrix(float width, float height, float length)
{
	_projectionMatrix = glm::mat4(1.0);
	_projectionMatrix[0][0] = 2.0f / width;
	_projectionMatrix[1][1] = 2.0f / height;
	_projectionMatrix[2][2] = -2.0f / length;
	_projectionMatrix[3][3] = 1;
}

glm::mat4	ShadowMapMasterRenderer::_createOffset()
{
	glm::mat4 offset = glm::mat4();
	offset = glm::translate(offset, glm::vec3(0.5f, 0.5f, 0.5f));
	offset = glm::scale(offset, glm::vec3(0.5f, 0.5f, 0.5f));
	return (offset);
}
