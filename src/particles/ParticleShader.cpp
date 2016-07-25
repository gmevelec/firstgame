#include "particles/ParticleShader.h"

ParticleShader::ParticleShader() : ShaderProgram("./Resources/shaders/particleshader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

ParticleShader::~ParticleShader()
{
}

void		ParticleShader::getAllUniformLocations()
{
	_locationModelViewMatrix = getUniformLocation("modelViewMatrix");
	_locationProjectionMatrix = getUniformLocation("projectionMatrix");
	_locationTexOffset1 = getUniformLocation("texOffset1");
	_locationTexOffset2 = getUniformLocation("texOffset2");
	_locationTexCoordInfo = getUniformLocation("texCoordInfo");
}

void		ParticleShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void		ParticleShader::loadTextureCoordInfo(glm::vec2 offset1, glm::vec2 offset2, float numRows, float blend)
{
	loadVector2f(_locationTexOffset1, offset1);
	loadVector2f(_locationTexOffset2, offset2);
	loadVector2f(_locationTexCoordInfo, glm::vec2(numRows, blend));
}

void		ParticleShader::loadModelViewMatrix(glm::mat4 modelView)
{
	loadMatrix(_locationModelViewMatrix, modelView);
}

void		ParticleShader::loadProjectionMatrix(glm::mat4 projectionMatrix)
{
	loadMatrix(_locationProjectionMatrix, projectionMatrix);
}