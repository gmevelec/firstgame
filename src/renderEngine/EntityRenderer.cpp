#include "renderEngine/EntityRenderer.h"
#include "renderEngine/MasterRenderer.h"
#include <GL/glew.h>
#include <iostream>
#include <math.h>

EntityRenderer::EntityRenderer(StaticShader shader, glm::mat4 projectionMatrix):
_shader(shader)
{
	_shader.start();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.stop();
}

EntityRenderer::~EntityRenderer()
{

}

void 		EntityRenderer::render(tMap entities)
{
	std::map<TexturedModel, std::vector<Entity>>::iterator model;
	for (model = entities.begin(); model != entities.end(); ++model)
	{
		prepareTexturedModel(model->first);
		std::vector<Entity> batch = entities.find(model->first)->second;
		std::vector<Entity>::iterator entity;
		for (Entity entity: model->second)
		{
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, model->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void 		EntityRenderer::prepareTexturedModel(TexturedModel model)
{
	RawModel rawModel = model.getRawModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ModelTexture texture = model.getTexture();
	_shader.loadNumberOfRows(texture.getNumberOfRows());
	if (texture.getTransparancy())
	{
		MasterRenderer::disableCulling();
	}
	_shader.loadFakeLightingVariable(texture.getUseFakeLighting());
	_shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getTextureID());
}

void 		EntityRenderer::unbindTexturedModel()
{
	MasterRenderer::enableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void 		EntityRenderer::prepareInstance(Entity entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
	_shader.loadTransformationMatrix(transformationMatrix);
	_shader.loadOffset(entity.getTextureXOffset(), entity.getTextureYOffset());
}
