#include "shaders/SkyboxShader.h"

SkyboxShader::SkyboxShader(): ShaderProgram("./Resources/shaders/skyboxshader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

SkyboxShader::~SkyboxShader()
{
}

void	SkyboxShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void	SkyboxShader::getAllUniformLocations()
{
	_locationProjectionMatrix = getUniformLocation("projectionMatrix");
	_locationViewMatrix = getUniformLocation("viewMatrix");
	_locationFogColour = getUniformLocation("fogColour");
	_locationCubeMap = getUniformLocation("cubeMap");
	_locationCubeMap2 = getUniformLocation("cubeMap2");
	_locationBlendFactor = getUniformLocation("blendFactor");
}

void			SkyboxShader::connectTextureUnits()
{
	loadInt(_locationCubeMap, 0);
	loadInt(_locationCubeMap2, 1);
}

void			SkyboxShader::loadBlendFactor(float blend)
{
	loadFloat(_locationBlendFactor, blend);
}

void			SkyboxShader::loadFogColour(float r, float g, float b)
{
	loadVector3f(_locationFogColour, glm::vec3(r, g, b));
}

void			SkyboxShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationProjectionMatrix, matrix);
}

void			SkyboxShader::loadViewMatrix(Camera camera)
{
	glm::mat4 	viewMatrix = Maths::createViewMatrix(camera);
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
	_rotation += _rotateSpeed * MainGame::delta;
	viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(_rotation), glm::vec3(0, 1, 0));
	loadMatrix(_locationViewMatrix, viewMatrix);
}