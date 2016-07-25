#include "water/WaterRenderer.h"
#include "tools/Maths.h"
#include "engineTester/MainGame.h"
#include "renderEngine/MasterRenderer.h"
#include <vector>

std::vector<GLfloat> WaterRenderer::vertices = {-1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1};

WaterRenderer::WaterRenderer(Loader loader, WaterShader shader, glm::mat4 projectionMatrix, WaterFrameBuffer fbos):
_quad(loader.loadToVAO(vertices, 2)),
_shader(shader),
_fbos(fbos),
_dudvTexture(loader.loadTexture(_dudvMap)),
_normalMapTexture(loader.loadTexture(_normalMap))
{
	_shader.start();
	_shader.connectTextureUnits();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.stop();
}

WaterRenderer::~WaterRenderer()
{
}

void 	WaterRenderer::render(std::vector<WaterTile> water, Camera camera, Light sun)
{
	_prepareRender(camera, sun);
	for (WaterTile tile: water)
	{
		glm::mat4 modelMatrix = Maths::createTransformationMatrix(glm::vec3(tile.getX(), tile.getHeight(), tile.getZ()), glm::vec3(0, 0, 0), WaterTile::tile_size);
		_shader.loadModelMatrix(modelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, _quad.getVertexCount());
	}
	_unbind();
}

void	WaterRenderer::_prepareRender(Camera camera, Light sun)
{
	_shader.start();
	_shader.loadViewMatrix(camera);
	_moveFactor += _waveSpeed * MainGame::delta;
	_moveFactor = fmod(_moveFactor, 1);
	_shader.loadMoveFactor(_moveFactor);
	_shader.loadLight(sun);
	_shader.loadSkyColour(MasterRenderer::_RED, MasterRenderer::_GREEN, MasterRenderer::_BLUE);
	glBindVertexArray(_quad.getVaoID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _fbos.getReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _fbos.getRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _dudvTexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _normalMapTexture);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _fbos.getRefractionDepthTexture());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void	WaterRenderer::_unbind()
{
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	_shader.stop();
}

void	WaterRenderer::_setUpVAO(Loader loader)
{
	_quad = loader.loadToVAO(vertices, 2);
}