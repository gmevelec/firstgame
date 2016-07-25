#include "shadows/ShadowShader.h"

ShadowShader::ShadowShader(): ShaderProgram("./Resources/shaders/shadowshader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

ShadowShader::~ShadowShader()
{
}

void		ShadowShader::getAllUniformLocations()
{
	_locationMvpMatrix = getUniformLocation("mvpMatrix");
}

void		ShadowShader::bindAttributes()
{
	bindAttribute(0, "in_position");
}

void		ShadowShader::loadMvpMatrix(glm::mat4 mvpMatrix)
{
	loadMatrix(_locationMvpMatrix, mvpMatrix);
}
