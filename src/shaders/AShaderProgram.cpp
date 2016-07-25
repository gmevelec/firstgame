#include "shaders/AShaderProgram.h"
#include <fstream>
#include <string>
#include <sstream>
#include "tools/Logger.h"

ShaderProgram::ShaderProgram(const std::string& fileName)
{
	_vertexShaderID = loadShader(fileName + ".vs", GL_VERTEX_SHADER);
	_fragmentShaderID = loadShader(fileName + ".fs", GL_FRAGMENT_SHADER);

	_programID = glCreateProgram();
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
}

ShaderProgram::~ShaderProgram()
{
}

void			ShaderProgram::start()
{
	glUseProgram(_programID);
}

void			ShaderProgram::stop()
{
	glUseProgram(0);
}

void			ShaderProgram::cleanUp()
{
	stop();
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	glDeleteProgram(_programID);
}

void			ShaderProgram::bindAttribute(int attribute, const GLchar* variableName)
{
	glBindAttribLocation(_programID, attribute, variableName);
}

GLint 			ShaderProgram::getUniformLocation(const GLchar* uniformName)
{
	return (glGetUniformLocation(_programID, uniformName));
}

void			ShaderProgram::loadInt(GLuint location, int value)
{
	glUniform1i(location, value);
}

void			ShaderProgram::loadFloat(GLuint location, float value)
{
	glUniform1f(location, value);
}

void			ShaderProgram::loadVector4f(GLuint location, glm::vec4 vector)
{
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void			ShaderProgram::loadVector3f(GLuint location, glm::vec3 vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void			ShaderProgram::loadVector2f(GLuint location, glm::vec2 vector)
{
	glUniform2f(location, vector.x, vector.y);
}

void			ShaderProgram::loadMatrix(GLuint location, glm::mat4 mat)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void			ShaderProgram::loadBoolean(GLuint location, bool value)
{
	float toLoad = 0;
	if (value)
		toLoad = 1;
	glUniform1f(location, toLoad);
}

int				ShaderProgram::loadShader(const std::string& filePath, GLenum shaderType)
{
	LOG(INFO, "ShaderProgram*", "Loading shader file: " + filePath);

	// Open file.
	std::ifstream t(filePath);
	if (!t.good())
		throw std::runtime_error(std::string("Failed to open file: ") + filePath);

	std::string code((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	int		shaderID = glCreateShader(shaderType);
	if (shaderID == 0)
		throw std::runtime_error("glCreateShader failed.");

	const char *buffer = code.c_str();

	glShaderSource(shaderID, 1, &buffer, NULL);

	// Compile.
	glCompileShader(shaderID);

	// Throw exception if compile error occurred.
	GLint	status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::string msg("Compile failure in shader:\n");

		GLint 	infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char 	*strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, strInfoLog);
		msg += strInfoLog;
		delete [] strInfoLog;
		glDeleteShader(shaderID);
		shaderID = 0;
		throw std::runtime_error(msg);
	}
	return (shaderID);
}
