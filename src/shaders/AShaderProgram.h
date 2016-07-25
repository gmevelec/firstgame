/*
** This class is used to load shader, and use program for openGL.
*/

#pragma once

#include <iostream>
#include <GL/glew.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "entities/Camera.h"
#include "entities/Light.h"
#include "tools/Maths.h"


class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();

	void	start();
	void	stop();

	/*
	** This function stop the program, detach and delete all of the shaders.
	*/
	void	cleanUp();

	/*
	** @param filePath		A string containing the path for the shader to load.
	** @param shaderType	The type of the shader to load. (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER ...).
	*/
	int		loadShader(const std::string& filePath, GLenum shaderType);

protected:
	/*
	** This function bind all attributes for shaders.
	*/
	virtual void	bindAttributes() = 0;
	void			bindAttribute(int attribute, const GLchar* variableName);

	virtual void	getAllUniformLocations() = 0;
	GLint			getUniformLocation(const GLchar* uniformName);

	void			loadFloat(GLuint location, float value);
	void			loadVector4f(GLuint location, glm::vec4 vector);
	void			loadVector3f(GLuint location, glm::vec3 vector);
	void			loadVector2f(GLuint location, glm::vec2 vector);
	void			loadMatrix(GLuint location, glm::mat4 mat);
	void			loadBoolean(GLuint location, bool value);
	void			loadInt(GLuint location, int value);

	int		_programID;

private:
	int		_vertexShaderID;
	int		_fragmentShaderID;
};
