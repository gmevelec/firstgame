/*
** This class is used to create the water's FBO.
*/
#pragma once

#include <GL/glew.h>

class WaterFrameBuffer
{
public:
	WaterFrameBuffer();
	~WaterFrameBuffer();

	void	cleanUp();
	
	void	bindReflectionFrameBuffer();
	void	bindRefractionFrameBuffer();
	void	unbindCurrentFrameBuffer();

	GLuint		getReflectionTexture();
	GLuint		getRefractionTexture();
	GLuint		getRefractionDepthTexture();

private:

	int 	_reflectionWidth = 320;
	int 	_reflectionHeight = 180;

	int 	_refractionWidth = 1280;
	int 	_refractionHeight = 720;


	GLuint		_reflectionFrameBuffer;
	GLuint		_reflectionTexture;
	GLuint		_reflectionDepthBuffer;	

	GLuint		_refractionFrameBuffer;
	GLuint		_refractionTexture;
	GLuint		_refractionDepthTexture;

	void	_initializeReflectionFrameBuffer();
	void	_initializeRefractionFrameBuffer();
	void	_bindFrameBuffer(GLuint frameBuffer, int width, int height);
	GLuint 	_createFrameBuffer();

	GLuint 	_createTextureAttachment(int width, int height);
	GLuint 	_createDepthTextureAttachment(int width, int height);
	GLuint 	_createDepthBufferAttachment(int width, int height);
};