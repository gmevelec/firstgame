#pragma once

#include "shadows/ShadowFrameBuffer.h"
#include "shadows/ShadowShader.h"
#include "shadows/ShadowBox.h"
#include "shadows/ShadowMapEntityRenderer.h"

#include "entities/Camera.h"
#include "entities/Light.h"

#include "renderEngine/EntityRenderer.h"

#include <glm/glm.hpp>

class ShadowMapMasterRenderer
{
public:
	ShadowMapMasterRenderer(Camera& camera);
	~ShadowMapMasterRenderer();

	void		render(tMap entities, Light sun);
	glm::mat4	getToShadowMapSpaceMatrix();
	void		cleanUp();
	int			getShadowMap();
	glm::mat4	getLightSpaceTransform();

private:
	glm::mat4				_projectionMatrix = glm::mat4();
	glm::mat4				_lightViewMatrix = glm::mat4();
	glm::mat4				_projectionViewMatrix = glm::mat4();
	glm::mat4				_offset = _createOffset();
	int						_shadowMapSize = 2048;
	ShadowFrameBuffer		_shadowFbo;
	ShadowShader			_shader;
	ShadowBox				_shadowBox;
	ShadowMapEntityRenderer	_entityRenderer;

	void		_prepare(glm::vec3 lightDirection, ShadowBox box);
	void		_finish();
	void		_updateLightViewMatrix(glm::vec3 direction, glm::vec3 center);
	void		_updateOrthoProjectionMatrix(float width, float height, float length);
	glm::mat4	_createOffset();
};
