#pragma once

#include "shaders/AShaderProgram.h"

class ShadowShader : public ShaderProgram
{
public:
	ShadowShader();
	~ShadowShader();


	void	loadMvpMatrix(glm::mat4 mvpMatrix);

protected:
	void	getAllUniformLocations();
	void	bindAttributes();
	
private:
	int		_locationMvpMatrix;
};
