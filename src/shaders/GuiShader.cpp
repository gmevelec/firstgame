#include "shaders/GuiShader.h"

GuiShader::GuiShader(): ShaderProgram("./Resources/shaders/guishader")
{
	bindAttributes();
	glLinkProgram(_programID);
	glValidateProgram(_programID);
	getAllUniformLocations();
}

GuiShader::~GuiShader()
{
}

void	GuiShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void	GuiShader::getAllUniformLocations()
{
	_locationTransformationMatrix = getUniformLocation("transformationMatrix");
}

void			GuiShader::loadTransformationMatrix(glm::mat4 matrix)
{
	loadMatrix(_locationTransformationMatrix, matrix);
}
