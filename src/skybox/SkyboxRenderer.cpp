#include "skybox/SkyboxRenderer.h"
#include "tools/Logger.h"

SkyboxRenderer::SkyboxRenderer(Loader loader, glm::mat4 projectionMatrix):
_cube(loader.loadToVAO(_vertices, 3)),
_texture(loader.loadCubeMap(_textureFiles)),
_nightTexture(loader.loadCubeMap(_nightTextureFiles))
{
	_shader.start();
	_shader.connectTextureUnits();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.stop();
}

SkyboxRenderer::~SkyboxRenderer()
{
}

void		SkyboxRenderer::render(Camera camera, float r, float g, float b)
{
	_shader.start();
	_shader.loadViewMatrix(camera);
	_shader.loadFogColour(r, g, b);
	glBindVertexArray(_cube.getVaoID());
	glEnableVertexAttribArray(0);
	_bindTextures();
	glDrawArrays(GL_TRIANGLES, 0, _cube.getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	_shader.stop();
}

void 		SkyboxRenderer::_bindTextures()
{
	_time += MainGame::delta * 100;
	_time = fmod(_time, 24000);
	int texture1;
	int texture2;
	float blendFactor;		
	if(_time >= 0 && _time < 5000)
	{
		texture1 = _nightTexture;
		texture2 = _nightTexture;
		blendFactor = (_time - 0)/(5000 - 0);
	}
	else if(_time >= 5000 && _time < 8000)
	{
		texture1 = _nightTexture;
		texture2 = _texture;
		blendFactor = (_time - 5000)/(8000 - 5000);
	}
	else if(_time >= 8000 && _time < 21000)
	{
		texture1 = _texture;
		texture2 = _texture;
		blendFactor = (_time - 8000)/(21000 - 8000);
	}
	else
	{
		texture1 = _texture;
		texture2 = _nightTexture;
		blendFactor = (_time - 21000)/(24000 - 21000);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
	_shader.loadBlendFactor(blendFactor);
}

float		SkyboxRenderer::getTime()
{
	return (_time);
}
