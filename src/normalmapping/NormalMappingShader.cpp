#include "normalmapping/NormalMappingShader.h"

NormalMappingShader::NormalMappingShader(): ShaderProgram("./Resources/shaders/normalmapshader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

NormalMappingShader::~NormalMappingShader()
{
}

void	NormalMappingShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoordinates");
	bindAttribute(2, "normal");
	bindAttribute(3, "tangent");
}

void	NormalMappingShader::getAllUniformLocations()
{
	_locationTransformationMatrix = getUniformLocation("transformationMatrix");
	_locationProjectionMatrix = getUniformLocation("projectionMatrix");
	_locationViewMatrix = getUniformLocation("viewMatrix");
	_locationShineDamper = getUniformLocation("shineDamper");
	_locationReflectivity = getUniformLocation("reflectivity");
	_locationSkyColour = getUniformLocation("skyColour");
	_locationNumberOfRows = getUniformLocation("numberOfRows");
	_locationOffset = getUniformLocation("offset");
	_locationPlane = getUniformLocation("plane");
	_locationModelTexture = getUniformLocation("modelTexture");
	_locationNormalMap = getUniformLocation("normalMap");
	_locationLightPositionEyeSpace = new int[_maxLights];
	_locationLightColour = new int[_maxLights];
	_locationAttenuation = new int[_maxLights];
	for (int i = 0; i < _maxLights; ++i)
	{
		_locationLightPositionEyeSpace[i] = getUniformLocation(("lightPositionEyeSpace[" + to_string(i) + "]").c_str());
		_locationLightColour[i] = getUniformLocation(("lightColour[" + to_string(i) + "]").c_str());
		_locationAttenuation[i] = getUniformLocation(("attenuation[" + to_string(i) + "]").c_str());
	}
}

void			NormalMappingShader::connectTextureUnits()
{
	loadInt(_locationModelTexture, 0);
	loadInt(_locationNormalMap, 1);
}

void			NormalMappingShader::loadClipPlane(glm::vec4 plane)
{
	loadVector4f(_locationPlane, plane);
}

void			NormalMappingShader::loadNumberOfRows(int numberOfRows)
{
	loadFloat(_locationNumberOfRows, numberOfRows);
}

void			NormalMappingShader::loadOffset(float x, float y)
{
	loadVector2f(_locationOffset, glm::vec2(x, y));
}

void			NormalMappingShader::loadSkyColour(float r, float g, float b)
{
	loadVector3f(_locationSkyColour, glm::vec3(r, g, b));
}

void			NormalMappingShader::loadShineVariables(float shineDamper, float reflectivity)
{
	loadFloat(_locationShineDamper, shineDamper);
	loadFloat(_locationReflectivity, reflectivity);
}

void			NormalMappingShader::loadLights(std::vector<Light> lights, glm::mat4 viewMatrix)
{
	for (int i = 0; i < _maxLights; ++i)
	{
		if (i < (int)lights.size())
		{
			loadVector3f(_locationLightPositionEyeSpace[i], _getEyeSpacePosition(lights[i], viewMatrix));
			loadVector3f(_locationLightColour[i], lights[i].getColour());	
			loadVector3f(_locationAttenuation[i], lights[i].getAttenuation());	
		}
		else
		{
			loadVector3f(_locationLightPositionEyeSpace[i], glm::vec3(0, 0, 0));
			loadVector3f(_locationLightColour[i], glm::vec3(0, 0, 0));
			loadVector3f(_locationAttenuation[i], glm::vec3(1, 0, 0));
		}
	}
}

void			NormalMappingShader::loadTransformationMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationTransformationMatrix, matrix);
}

void			NormalMappingShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationProjectionMatrix, matrix);
}

void			NormalMappingShader::loadViewMatrix(glm::mat4 viewMatrix)
{
	loadMatrix(_locationViewMatrix, viewMatrix);
}

glm::vec3 		NormalMappingShader::_getEyeSpacePosition(Light light, glm::mat4 viewMatrix)
{
	glm::vec3 position = light.getPosition();
	glm::vec4 eyeSpacePos(position.x ,position.y, position.z, 1.0f);
	eyeSpacePos = viewMatrix * eyeSpacePos;
	return (glm::vec3(eyeSpacePos.x, eyeSpacePos.y, eyeSpacePos.z));
}