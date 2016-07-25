#include "textures/Texture.h"
#include <stdexcept>

using namespace tdogl;

GLenum Texture::TextureFormatForBitmapFormat(Bitmap::Format format)
{
	switch (format)
	{
		case Bitmap::Format_Grayscale: return (GL_LUMINANCE);
		case Bitmap::Format_GrayscaleAlpha: return (GL_LUMINANCE_ALPHA);
		case Bitmap::Format_RGB: return (GL_RGB);
		case Bitmap::Format_RGBA: return (GL_RGBA);
		default: 
			throw std::runtime_error("Unrecognised Bitmap::Format");
	}
}

Texture::Texture(const Bitmap& bitmap, GLint minMagFilter, GLint wrapMode) : 
	_originalWidth((GLfloat)bitmap.width()),
	_originalHeight((GLfloat)bitmap.height())
{
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,
				0,
				TextureFormatForBitmapFormat(bitmap.format()),
				(GLsizei)bitmap.width(),
				(GLsizei)bitmap.height(),
				0,
				TextureFormatForBitmapFormat(bitmap.format()),
				GL_UNSIGNED_BYTE,
				bitmap.pixelBuffer()
				);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	// glDeleteTextures(1, &_textureID);
}

GLuint 		Texture::getTextureID() const
{
	return (_textureID);
}

GLfloat		Texture::originalWidth() const
{
	return (_originalWidth);
}

GLfloat 	Texture::originalHeight() const
{
	return (_originalHeight);
}