/*
** This class is used for represent the shader of an Entity.
*/

#pragma once

#include "shaders/AShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	virtual ~StaticShader();

	void	loadTransformationMatrix(glm::mat4 matrix);
	void	loadProjectionMatrix(glm::mat4 matrix);
	void	loadViewMatrix(Camera camera);
	void	loadLights(std::vector<Light> lights);
	void	loadShineVariables(float shineDamper, float reflectivity);
	void	loadFakeLightingVariable(bool use);
	void	loadSkyColour(float r, float g, float b);
	void	loadNumberOfRows(int numberOfRows);
	void	loadOffset(float x, float y);
	void	loadClipPlane(glm::vec4 plane);

protected:
	void	bindAttributes();
	void	getAllUniformLocations();

private:
	GLint	_locationTransformationMatrix;
	GLint	_locationProjectionMatrix;
	GLint	_locationViewMatrix;
	GLint*	_locationLightPosition;
	GLint*	_locationLightColour;
	GLint*	_locationAttenuation;
	GLint	_locationShineDamper;
	GLint	_locationReflectivity;
	GLint	_locationUseFakeLighting;
	GLint	_locationSkyColour;
	GLint	_locationNumberOfRows;
	GLint	_locationOffset;
	GLint	_locationPlane;

	int 	_maxLights = 4;
};
