#pragma once

#include <GL/glew.h>

class ShadowFrameBuffer
{
public:
	ShadowFrameBuffer(int width, int height);
	~ShadowFrameBuffer();

	void	cleanUp();
	void	bindFrameBuffer();
	void	unbindFrameBuffer();
	GLuint	getShadowMap();

private:
	int 	_width;
	int 	_height;
	GLuint	_fbo;
	GLuint	_shadowMap;

	void	_initializeFrameBuffer();
	void	_bindFrameBuffer(int frameBuffer, int width, int height);
	GLuint 	_createFrameBuffer();
	GLuint 	_createDepthBufferAttachment(int width, int height);
};
