/*
** This class is used to render a NormalMapped object.
*/
#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include "entities/Light.h"
#include "entities/Entity.h"
#include "entities/Camera.h"
#include "models/TexturedModel.h"
#include "normalmapping/NormalMappingShader.h"
#include "renderEngine/EntityRenderer.h"


class NormalMappingRenderer
{
public:
	NormalMappingRenderer(glm::mat4 projectionMatrix);
	~NormalMappingRenderer();

	void		render(tMap entities, glm::vec4 clipPlane, std::vector<Light> lights, Camera camera);
	void		cleanUp();

private:
	NormalMappingShader		_shader;

	void		_prepareTexturedModel(TexturedModel model);
	void		_unbindTexturedModel();
	void		_prepareInstance(Entity entity);
	void		_prepare(glm::vec4 clipPlane, std::vector<Light> lights, Camera camera);
};