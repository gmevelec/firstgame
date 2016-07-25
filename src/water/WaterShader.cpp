#include "water/WaterShader.h"
#include "tools/Maths.h"

WaterShader::WaterShader(): ShaderProgram("./Resources/shaders/watershader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

WaterShader::~WaterShader()
{
}

void	WaterShader::loadProjectionMatrix(glm::mat4 projection)
{
	loadMatrix(_locationProjectionMatrix, projection);
}

void	WaterShader::loadViewMatrix(Camera camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(_locationViewMatrix, viewMatrix);
	loadVector3f(_locationCameraPosition, camera.getPosition());
}

void	WaterShader::loadModelMatrix(glm::mat4 modelMatrix)
{
	loadMatrix(_locationModelMatrix, modelMatrix);
}

void	WaterShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void	WaterShader::getAllUniformLocations()
{
	_locationProjectionMatrix = getUniformLocation("projectionMatrix");
	_locationViewMatrix = getUniformLocation("viewMatrix");
	_locationModelMatrix = getUniformLocation("modelMatrix");
	_locationReflectionTexture = getUniformLocation("reflectionTexture");
	_locationRefractionTexture = getUniformLocation("refractionTexture");
	_locationDudvMap = getUniformLocation("dudvMap");
	_locationMoveFactor = getUniformLocation("moveFactor");
	_locationCameraPosition = getUniformLocation("cameraPosition");
	_locationNormalMap = getUniformLocation("normalMap");
	_locationDepthMap = getUniformLocation("depthMap");
	_locationLightPosition = getUniformLocation("lightPosition");
	_locationLightColour = getUniformLocation("lightColour");
	_locationSkyColour = getUniformLocation("skyColour");
}

void	WaterShader::connectTextureUnits()
{
	loadInt(_locationReflectionTexture, 0);
	loadInt(_locationRefractionTexture, 1);
	loadInt(_locationDudvMap, 2);
	loadInt(_locationNormalMap, 3);
	loadInt(_locationDepthMap, 4);
}

void	WaterShader::loadSkyColour(float r, float g, float b)
{
	loadVector3f(_locationSkyColour, glm::vec3(r, g, b));
}

void	WaterShader::loadMoveFactor(float factor)
{
	loadFloat(_locationMoveFactor, factor);
}

void	WaterShader::loadLight(Light sun)
{
	loadVector3f(_locationLightPosition, sun.getPosition());
	loadVector3f(_locationLightColour, sun.getColour());
}