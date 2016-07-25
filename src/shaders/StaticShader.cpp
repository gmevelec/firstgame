#include "shaders/StaticShader.h"

StaticShader::StaticShader(): ShaderProgram("./Resources/shaders/shader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

StaticShader::~StaticShader()
{
}

void	StaticShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void	StaticShader::getAllUniformLocations()
{
	_locationTransformationMatrix = getUniformLocation("transformationMatrix");
	_locationProjectionMatrix = getUniformLocation("projectionMatrix");
	_locationViewMatrix = getUniformLocation("viewMatrix");
	_locationShineDamper = getUniformLocation("shineDamper");
	_locationReflectivity = getUniformLocation("reflectivity");
	_locationUseFakeLighting = getUniformLocation("useFakeLighting");
	_locationSkyColour = getUniformLocation("skyColour");
	_locationNumberOfRows = getUniformLocation("numberOfRows");
	_locationOffset = getUniformLocation("offset");
	_locationPlane = getUniformLocation("plane");
	_locationLightPosition = new int[_maxLights];
	_locationLightColour = new int[_maxLights];
	_locationAttenuation = new int[_maxLights];
	for (int i = 0; i < _maxLights; ++i)
	{
		_locationLightPosition[i] = getUniformLocation(("lightPosition[" + to_string(i) + "]").c_str());
		_locationLightColour[i] = getUniformLocation(("lightColour[" + to_string(i) + "]").c_str());
		_locationAttenuation[i] = getUniformLocation(("attenuation[" + to_string(i) + "]").c_str());
	}
}

void			StaticShader::loadClipPlane(glm::vec4 plane)
{
	loadVector4f(_locationPlane, plane);
}

void			StaticShader::loadNumberOfRows(int numberOfRows)
{
	loadFloat(_locationNumberOfRows, numberOfRows);
}

void			StaticShader::loadOffset(float x, float y)
{
	loadVector2f(_locationOffset, glm::vec2(x, y));
}

void			StaticShader::loadSkyColour(float r, float g, float b)
{
	loadVector3f(_locationSkyColour, glm::vec3(r, g, b));
}

void			StaticShader::loadFakeLightingVariable(bool useFake)
{
	loadBoolean(_locationUseFakeLighting, useFake);
}

void			StaticShader::loadShineVariables(float shineDamper, float reflectivity)
{
	loadFloat(_locationShineDamper, shineDamper);
	loadFloat(_locationReflectivity, reflectivity);
}

void			StaticShader::loadLights(std::vector<Light> lights)
{
	for (int i = 0; i < _maxLights; ++i)
	{
		if (i < (int)lights.size())
		{
			loadVector3f(_locationLightPosition[i], lights[i].getPosition());
			loadVector3f(_locationLightColour[i], lights[i].getColour());	
			loadVector3f(_locationAttenuation[i], lights[i].getAttenuation());	
		}
		else
		{
			loadVector3f(_locationLightPosition[i], glm::vec3(0, 0, 0));
			loadVector3f(_locationLightColour[i], glm::vec3(0, 0, 0));
			loadVector3f(_locationAttenuation[i], glm::vec3(1, 0, 0));
		}
	}
}

void			StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationTransformationMatrix, matrix);
}

void			StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationProjectionMatrix, matrix);
}

void			StaticShader::loadViewMatrix(Camera camera)
{
	glm::mat4 	viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(_locationViewMatrix, viewMatrix);
}