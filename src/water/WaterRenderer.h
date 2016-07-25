/*
** This class is used to render the water.
*/
#pragma once

#include "renderEngine/Loader.h"
#include "water/WaterShader.h"
#include "water/WaterTile.h"
#include "water/WaterFrameBuffer.h"
#include "models/RawModel.h"
#include <glm/glm.hpp>

class WaterRenderer
{
public:
	WaterRenderer(Loader loader, WaterShader shader, glm::mat4 projectionMatrix, WaterFrameBuffer fbos);
	~WaterRenderer();

	void	render(std::vector<WaterTile> water, Camera camera, Light sun);
private:
	RawModel			_quad;
	WaterShader			_shader;
	WaterFrameBuffer	_fbos;

	const std::string	_dudvMap = "Resources/water/waterDUDV.png";
	const std::string	_normalMap = "Resources/water/normalMap.png";
	int					_dudvTexture;
	int					_normalMapTexture;
	float				_waveSpeed = 0.03;
	float				_moveFactor = 0;

	static std::vector<GLfloat> vertices;

	void	_prepareRender(Camera camera, Light sun);
	void	_unbind();
	void	_setUpVAO(Loader loader);
};