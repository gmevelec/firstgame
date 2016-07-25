#pragma once

#include "renderEngine/EntityRenderer.h"
#include "models/RawModel.h"
#include "entities/Entity.h"
#include "shadows/ShadowShader.h"

#include <glm/glm.hpp>

class ShadowMapEntityRenderer
{
public:
	ShadowMapEntityRenderer(ShadowShader shader, glm::mat4 projectionMatrix);
	~ShadowMapEntityRenderer();

	void	render(tMap entities);

private:
	ShadowShader	_shader;
	glm::mat4		_projectionViewMatrix;

	void	_bindModel(RawModel rawModel);
	void	_prepareInstance(Entity entity);
};
