#include "shadows/ShadowFrameBuffer.h"
#include "engineTester/MainGame.h"

ShadowFrameBuffer::ShadowFrameBuffer(int width, int height):
_width(width),
_height(height)
{
	_initializeFrameBuffer();
}

ShadowFrameBuffer::~ShadowFrameBuffer()
{
}

void	ShadowFrameBuffer::cleanUp()
{
	glDeleteFramebuffers(1, &_fbo);
	glDeleteTextures(1, &_shadowMap);
}

void	ShadowFrameBuffer::bindFrameBuffer()
{
	_bindFrameBuffer(_fbo, _width, _height);
}

void	ShadowFrameBuffer::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, MainGame::screenWidth, MainGame::screenHeight);
}

GLuint		ShadowFrameBuffer::getShadowMap()
{
	return (_shadowMap);
}

void	ShadowFrameBuffer::_initializeFrameBuffer()
{
	_fbo = _createFrameBuffer();
	_shadowMap = _createDepthBufferAttachment(_width, _height);
	unbindFrameBuffer();
}

void	ShadowFrameBuffer::_bindFrameBuffer(int frameBuffer, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

GLuint 	ShadowFrameBuffer::_createFrameBuffer()
{
	GLuint frameBuffer;
	
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_NONE);
	return (frameBuffer);
}

GLuint 	ShadowFrameBuffer::_createDepthBufferAttachment(int width, int height)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	return (texture);
}
