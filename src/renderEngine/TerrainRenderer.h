/*
** This class is used to render a terrain.
*/

#pragma once

#include "shaders/TerrainShader.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include "terrains/Terrain.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader shader, glm::mat4 projectionMatrix);
	virtual ~TerrainRenderer();

	void		render(std::vector<Terrain> terrains);

private:

	TerrainShader	_shader;


	void		prepareTerrain(Terrain terrain);
	void		unbindTexturedModel();
	void		prepareInstance(Terrain terrain);
	void 		loadModelMatrix(Terrain terrain);
	void 		bindTextures(Terrain terrain);


};