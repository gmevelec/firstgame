/*
** This class is used for represent the shader of the water.
*/
#pragma once

#include "shaders/AShaderProgram.h"
#include "entities/Camera.h"
#include "entities/Light.h"

class WaterShader : public ShaderProgram
{
public:
	WaterShader();
	virtual ~WaterShader();
	
	void	loadProjectionMatrix(glm::mat4 matrix);
	void	loadViewMatrix(Camera camera);
	void	loadModelMatrix(glm::mat4 modelMatrix);
	void	connectTextureUnits();
	void	loadMoveFactor(float factor);
	void	loadLight(Light sun);
	void	loadSkyColour(float r, float g, float b);

protected:
	void	bindAttributes();
	void	getAllUniformLocations();

private:
	GLint	_locationProjectionMatrix;
	GLint	_locationViewMatrix;
	GLint	_locationModelMatrix;
	GLint	_locationReflectionTexture;
	GLint	_locationRefractionTexture;
	GLint	_locationDudvMap;
	GLint	_locationMoveFactor;
	GLint	_locationCameraPosition;
	GLint	_locationNormalMap;
	GLint	_locationDepthMap;
	GLint	_locationLightPosition;
	GLint	_locationLightColour;
	GLint	_locationSkyColour;
};