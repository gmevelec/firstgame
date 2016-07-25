/*
** This class is used for represent the shader of an NormalMapped Entity.
*/

#pragma once

#include "shaders/AShaderProgram.h"

class NormalMappingShader : public ShaderProgram
{
public:
	NormalMappingShader();
	virtual ~NormalMappingShader();

	void	loadTransformationMatrix(glm::mat4 matrix);
	void	loadProjectionMatrix(glm::mat4 matrix);
	void	loadViewMatrix(glm::mat4 viewMatrix);
	void	loadLights(std::vector<Light> lights, glm::mat4 viewMatrix);
	void	loadShineVariables(float shineDamper, float reflectivity);
	void	loadSkyColour(float r, float g, float b);
	void	loadNumberOfRows(int numberOfRows);
	void	loadOffset(float x, float y);
	void	loadClipPlane(glm::vec4 plane);
	void	connectTextureUnits();

protected:
	void	bindAttributes();
	void	getAllUniformLocations();

private:
	GLint	_locationTransformationMatrix;
	GLint	_locationProjectionMatrix;
	GLint	_locationViewMatrix;
	GLint*	_locationLightPositionEyeSpace;
	GLint*	_locationLightColour;
	GLint*	_locationAttenuation;
	GLint	_locationShineDamper;
	GLint	_locationReflectivity;
	GLint	_locationSkyColour;
	GLint	_locationNumberOfRows;
	GLint	_locationOffset;
	GLint	_locationPlane;
	GLint	_locationModelTexture;
	GLint	_locationNormalMap;

	int 	_maxLights = 4;

	glm::vec3 	_getEyeSpacePosition(Light light, glm::mat4 viewMatrix);
};
