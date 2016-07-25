/*
** This class is used for represent the shader of the skybox.
*/

#pragma once

#include "shaders/AShaderProgram.h"
#include "engineTester/MainGame.h"

class SkyboxShader : public ShaderProgram
{
public:
	SkyboxShader();
	virtual ~SkyboxShader();

	void	loadProjectionMatrix(glm::mat4 matrix);
	void	loadViewMatrix(Camera camera);
	void	loadFogColour(float r, float g, float b);
	void	connectTextureUnits();
	void	loadBlendFactor(float blend);

protected:
	void	bindAttributes();
	void	getAllUniformLocations();

private:
	float	_rotateSpeed = 1.0f;
	float	_rotation = 0;

	GLint	_locationProjectionMatrix;
	GLint	_locationViewMatrix;
	GLint	_locationFogColour;
	GLint	_locationCubeMap;
	GLint	_locationCubeMap2;
	GLint	_locationBlendFactor;

};
