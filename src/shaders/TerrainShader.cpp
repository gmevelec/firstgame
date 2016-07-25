#include "shaders/TerrainShader.h"

TerrainShader::TerrainShader(): ShaderProgram("./Resources/shaders/terrainshader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

TerrainShader::~TerrainShader()
{
}

void	TerrainShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
	bindAttribute(2, "normal");
}

void	TerrainShader::getAllUniformLocations()
{
	_locationTransformationMatrix = getUniformLocation("transformationMatrix");
	_locationProjectionMatrix = getUniformLocation("projectionMatrix");
	_locationViewMatrix = getUniformLocation("viewMatrix");
	_locationShineDamper = getUniformLocation("shineDamper");
	_locationReflectivity = getUniformLocation("reflectivity");
	_locationSkyColour = getUniformLocation("skyColour");
	_locationBackgroundTexture = getUniformLocation("backgroundTexture");
	_locationrTexture = getUniformLocation("rTexture");
	_locationgTexture = getUniformLocation("gTexture");
	_locationbTexture = getUniformLocation("bTexture");
	_locationBlendMap = getUniformLocation("blendMap");
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

void			TerrainShader::loadClipPlane(glm::vec4 plane)
{
	loadVector4f(_locationPlane, plane);
}


void			TerrainShader::connectTextureUnits()
{
	loadInt(_locationBackgroundTexture, 0);
	loadInt(_locationrTexture, 1);
	loadInt(_locationgTexture, 2);
	loadInt(_locationbTexture, 3);
	loadInt(_locationBlendMap, 4);
}

void			TerrainShader::loadSkyColour(float r, float g, float b)
{
	loadVector3f(_locationSkyColour, glm::vec3(r, g, b));
}


void			TerrainShader::loadShineVariables(float shineDamper, float reflectivity)
{
	loadFloat(_locationShineDamper, shineDamper);
	loadFloat(_locationReflectivity, reflectivity);
}

void			TerrainShader::loadLights(std::vector<Light> lights)
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

void			TerrainShader::loadTransformationMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationTransformationMatrix, matrix);
}

void			TerrainShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationProjectionMatrix, matrix);
}

void			TerrainShader::loadViewMatrix(Camera camera)
{
	glm::mat4 	viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(_locationViewMatrix, viewMatrix);
}