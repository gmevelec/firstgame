#include "normalmapping/NormalMappingRenderer.h"
#include "tools/Maths.h"
#include "renderEngine/MasterRenderer.h"
#include <iostream>

NormalMappingRenderer::NormalMappingRenderer(glm::mat4 projectionMatrix):
_shader(NormalMappingShader())
{
	_shader.start();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.connectTextureUnits();
	_shader.stop();
}

NormalMappingRenderer::~NormalMappingRenderer()
{
}

void		NormalMappingRenderer::render(tMap entities, glm::vec4 clipPlane, std::vector<Light> lights, Camera camera)
{
	_shader.start();
	_prepare(clipPlane, lights, camera);
	std::map<TexturedModel, std::vector<Entity>>::iterator model;
	for (model = entities.begin(); model != entities.end(); model++)
	{
		_prepareTexturedModel(model->first);
		std::vector<Entity> batch = entities.find(model->first)->second;
		std::vector<Entity>::iterator entity;
		for (Entity entity: model->second)
		{
			_prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, model->first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		_unbindTexturedModel();
	}
	_shader.stop();
}

void		NormalMappingRenderer::cleanUp()
{
	_shader.cleanUp();
}


void		NormalMappingRenderer::_prepareTexturedModel(TexturedModel model)
{
	RawModel rawModel = model.getRawModel();
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	ModelTexture texture = model.getTexture();
	_shader.loadNumberOfRows(texture.getNumberOfRows());
	if (texture.getTransparancy())
	{
		MasterRenderer::disableCulling();
	}
	_shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, model.getTexture().getNormalMap());
}

void		NormalMappingRenderer::_unbindTexturedModel()
{
	MasterRenderer::enableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindVertexArray(0);
}

void		NormalMappingRenderer::_prepareInstance(Entity entity)
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
	_shader.loadTransformationMatrix(transformationMatrix);
	_shader.loadOffset(entity.getTextureXOffset(), entity.getTextureYOffset());
}

void		NormalMappingRenderer::_prepare(glm::vec4 clipPlane, std::vector<Light> lights, Camera camera)
{
	_shader.loadClipPlane(clipPlane);
	_shader.loadSkyColour(MasterRenderer::_RED, MasterRenderer::_GREEN, MasterRenderer::_BLUE);
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	_shader.loadLights(lights, viewMatrix);
	_shader.loadViewMatrix(viewMatrix);
}
