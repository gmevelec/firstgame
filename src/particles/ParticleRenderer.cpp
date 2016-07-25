#include "particles/ParticleRenderer.h"
#include "particles/ParticleShader.h"

std::vector<float>	ParticleRenderer::_vertices = {-0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, -0.5};

ParticleRenderer::ParticleRenderer(Loader loader, glm::mat4 projectionMatrix):
_quad(loader.loadToVAO(ParticleRenderer::_vertices, 2)),
_shader(ParticleShader())
{
	_shader.start();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.stop();
}

ParticleRenderer::~ParticleRenderer()
{
}

void		ParticleRenderer::render(pMap& particles, Camera camera)
{
	glm::mat4	viewMatrix = Maths::createViewMatrix(camera);
	_prepare();
	std::map<ParticleTexture, std::vector<Particle>>::iterator itTexture;
	for (itTexture = particles.begin(); itTexture != particles.end(); itTexture++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, itTexture->first.getTextureID());
		for (Particle particle: itTexture->second)
		{
			_updateModelViewMatrix(particle.getPosition(), particle.getRotation(), particle.getScale(), viewMatrix);
			_shader.loadTextureCoordInfo(particle.getTexOffset1(), particle.getTexOffset2(), (itTexture->first).getNumberOfRows(), particle.getBlendFactor());
			glDrawArrays(GL_TRIANGLE_STRIP, 0, _quad.getVertexCount());
		}
	}
	_finishRendering();
}

void		ParticleRenderer::cleanUp()
{
	_shader.cleanUp();
}

void 		ParticleRenderer::_updateModelViewMatrix(glm::vec3 position, float rotation, float scale, glm::mat4 viewMatrix)
{
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix[0][0] = viewMatrix[0][0];
	modelMatrix[0][1] = viewMatrix[1][0];
	modelMatrix[0][2] = viewMatrix[2][0];
	modelMatrix[1][0] = viewMatrix[0][1];
	modelMatrix[1][1] = viewMatrix[1][1];
	modelMatrix[1][2] = viewMatrix[2][1];
	modelMatrix[2][0] = viewMatrix[0][2];
	modelMatrix[2][1] = viewMatrix[1][2];
	modelMatrix[2][2] = viewMatrix[2][2];
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	_shader.loadModelViewMatrix(modelViewMatrix);
}

void		ParticleRenderer::_prepare()
{
	_shader.start();
	glBindVertexArray(_quad.getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);
}

void		ParticleRenderer::_finishRendering()
{
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	_shader.stop();
}

