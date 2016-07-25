/*
** This class is used for represent the shader of a terrain.
*/

#pragma once

#include "shaders/AShaderProgram.h"

class TerrainShader : public ShaderProgram
{
public:
	TerrainShader();
	virtual ~TerrainShader();

	void	loadTransformationMatrix(glm::mat4 matrix);
	void	loadProjectionMatrix(glm::mat4 matrix);
	void	loadViewMatrix(Camera camera);
	void	loadLights(std::vector<Light> lights);
	void	loadShineVariables(float shineDamper, float reflectivity);
	void	loadSkyColour(float r, float g, float b);
	void	connectTextureUnits();
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
	GLint	_locationSkyColour;
	GLint	_locationBackgroundTexture;
	GLint	_locationrTexture;
	GLint	_locationgTexture;
	GLint	_locationbTexture;
	GLint	_locationBlendMap;
	GLint	_locationPlane;

	int 	_maxLights = 4;
};
