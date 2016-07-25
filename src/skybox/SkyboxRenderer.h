/*
** This class is used to render the skybox.
*/

#pragma once
#include "shaders/SkyboxShader.h"
#include "entities/Camera.h"

class SkyboxRenderer
{
public:
	SkyboxRenderer(Loader loader, glm::mat4 projectionMatrix);
	virtual ~SkyboxRenderer();

	void	render(Camera camera, float r, float g, float b);

	float	getTime();
	
private:
	static constexpr float SIZE = 500.0f;
	
	std::vector<float> _vertices = {        
	    -SIZE,  SIZE, -SIZE,
	    -SIZE, -SIZE, -SIZE,
	    SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,
	     SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,

	    -SIZE, -SIZE,  SIZE,
	    -SIZE, -SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE,  SIZE,
	    -SIZE, -SIZE,  SIZE,

	     SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,

	    -SIZE, -SIZE,  SIZE,
	    -SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE, -SIZE,  SIZE,
	    -SIZE, -SIZE,  SIZE,

	    -SIZE,  SIZE, -SIZE,
	     SIZE,  SIZE, -SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	    -SIZE,  SIZE,  SIZE,
	    -SIZE,  SIZE, -SIZE,

	    -SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE,  SIZE,
	     SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE,  SIZE,
	     SIZE, -SIZE,  SIZE
	};

	std::vector<std::string> 	_textureFiles = {"./Resources/skybox/right.png", "./Resources/skybox/left.png", "./Resources/skybox/top.png", "./Resources/skybox/bottom.png", "./Resources/skybox/back.png", "./Resources/skybox/front.png"};
	std::vector<std::string> 	_nightTextureFiles = {"./Resources/skybox/nightRight.png", "./Resources/skybox/nightLeft.png", "./Resources/skybox/nightTop.png", "./Resources/skybox/nightBottom.png", "./Resources/skybox/nightBack.png", "./Resources/skybox/nightFront.png"};
	RawModel					_cube;
	int							_texture;
	int							_nightTexture;
	SkyboxShader				_shader;
	float						_time = 0;
	
	void 		_bindTextures();

};