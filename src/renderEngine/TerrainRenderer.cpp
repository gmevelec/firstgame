#include "renderEngine/TerrainRenderer.h"
#include "textures/TerrainTexturePack.h"
#include <iostream>

TerrainRenderer::TerrainRenderer(TerrainShader shader, glm::mat4 projectionMatrix):
_shader(shader)
{
	_shader.start();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.connectTextureUnits();
	_shader.stop();
}

TerrainRenderer::~TerrainRenderer()
{
	
}

void		TerrainRenderer::render(std::vector<Terrain> terrains)
{
	for (Terrain& terrain : terrains)
	{
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}


void 		TerrainRenderer::prepareTerrain(Terrain terrain)
{
	RawModel rawModel = terrain.getModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bindTextures(terrain);
	_shader.loadShineVariables(1, 0);
}

void 		TerrainRenderer::bindTextures(Terrain terrain)
{
	TerrainTexturePack texturePack = terrain.getTexturePack();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePack.getBackgroundTexture().getTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePack.getrTexture().getTextureID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturePack.getgTexture().getTextureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturePack.getbTexture().getTextureID());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain.getBlendMap().getTextureID());

}

void 		TerrainRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void 		TerrainRenderer::loadModelMatrix(Terrain terrain)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(glm::vec3(terrain.getX(), 0, terrain.getZ()), glm::vec3(0, 0, 0), 1);
	_shader.loadTransformationMatrix(transformationMatrix);
}
