#include "shadows/ShadowMapEntityRenderer.h"

ShadowMapEntityRenderer::ShadowMapEntityRenderer(ShadowShader shader, glm::mat4 projectionViewMatrix):
_shader(shader),
_projectionViewMatrix(projectionViewMatrix)
{
}

ShadowMapEntityRenderer::~ShadowMapEntityRenderer()
{
}


void	ShadowMapEntityRenderer::render(tMap entities)
{
	std::map<TexturedModel, std::vector<Entity>>::iterator model;
	for (model = entities.begin(); model != entities.end(); ++model)
	{
		RawModel rawModel = model->first.getRawModel();
		_bindModel(rawModel);
		for (Entity entity: model->second)
		{
			_prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
		}
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void	ShadowMapEntityRenderer::_bindModel(RawModel rawModel)
{
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
}

void	ShadowMapEntityRenderer::_prepareInstance(Entity entity)
{
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
	glm::mat4 mvpMatrix = _projectionViewMatrix * modelMatrix;
	_shader.loadMvpMatrix(mvpMatrix);
}
