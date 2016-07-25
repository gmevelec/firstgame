/*
** This class is used for represent the shader of a particle.
*/
#pragma once

#include "shaders/AShaderProgram.h"

class ParticleShader : public ShaderProgram
{
public:
	ParticleShader();
	virtual ~ParticleShader();

	void 	loadModelViewMatrix(glm::mat4 modelView);
	void 	loadProjectionMatrix(glm::mat4 projectionMatrix);
	void	loadTextureCoordInfo(glm::vec2 offset1, glm::vec2 offset2, float numRows, float blend);
protected:
	void 	getAllUniformLocations();
	void 	bindAttributes();

private:
	int		_locationModelViewMatrix;
	int		_locationProjectionMatrix;
	int		_locationTexOffset1;
	int		_locationTexOffset2;
	int		_locationTexCoordInfo;
};