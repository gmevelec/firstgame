#include "water/WaterFrameBuffer.h"
#include "engineTester/MainGame.h"

WaterFrameBuffer::WaterFrameBuffer()
{
	_initializeReflectionFrameBuffer();
	_initializeRefractionFrameBuffer();
}

WaterFrameBuffer::~WaterFrameBuffer()
{
}

void	WaterFrameBuffer::cleanUp()
{
	glDeleteFramebuffers(1, &_reflectionFrameBuffer);
	glDeleteTextures(1, &_reflectionTexture);
	glDeleteRenderbuffers(1, &_reflectionDepthBuffer);
	glDeleteFramebuffers(1, &_refractionFrameBuffer);
	glDeleteTextures(1, &_refractionTexture);
	glDeleteTextures(1, &_refractionDepthTexture);
}
	
void	WaterFrameBuffer::bindReflectionFrameBuffer()
{
	_bindFrameBuffer(_reflectionFrameBuffer, _reflectionWidth, _reflectionHeight);
}

void	WaterFrameBuffer::bindRefractionFrameBuffer()
{
	_bindFrameBuffer(_refractionFrameBuffer, _refractionWidth, _refractionHeight);
}

void	WaterFrameBuffer::unbindCurrentFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, MainGame::screenWidth, MainGame::screenHeight);
}

GLuint		WaterFrameBuffer::getReflectionTexture()
{
	return (_reflectionTexture);
}

GLuint		WaterFrameBuffer::getRefractionTexture()
{
	return (_refractionTexture);
}

GLuint		WaterFrameBuffer::getRefractionDepthTexture()
{
	return (_refractionDepthTexture);
}

void	WaterFrameBuffer::_initializeReflectionFrameBuffer()
{
	_reflectionFrameBuffer = _createFrameBuffer();
	_reflectionTexture = _createTextureAttachment(_reflectionWidth, _reflectionHeight);
	_reflectionDepthBuffer = _createDepthBufferAttachment(_reflectionWidth, _reflectionHeight);
	unbindCurrentFrameBuffer();
}

void	WaterFrameBuffer::_initializeRefractionFrameBuffer()
{
	_refractionFrameBuffer = _createFrameBuffer();
	_refractionTexture = _createTextureAttachment(_refractionWidth, _refractionHeight);
	_refractionDepthTexture = _createDepthTextureAttachment(_refractionWidth, _refractionHeight);
	unbindCurrentFrameBuffer();
}

void	WaterFrameBuffer::_bindFrameBuffer(GLuint frameBuffer, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

GLuint 	WaterFrameBuffer::_createFrameBuffer()
{
	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return (frameBuffer);
}

GLuint 	WaterFrameBuffer::_createTextureAttachment(int width, int height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	return (texture);
}

GLuint 	WaterFrameBuffer::_createDepthTextureAttachment(int width, int height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	return (texture);
}

GLuint 	WaterFrameBuffer::_createDepthBufferAttachment(int width, int height)
{
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	return (depthBuffer);
}
