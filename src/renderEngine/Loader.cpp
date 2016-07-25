#include "renderEngine/Loader.h"
#include <GL/glew.h>
#include <iostream>

#include "tools/Logger.h"

#include <SOIL/SOIL.h>

Loader::Loader()
{
}

Loader::~Loader()
{
}

RawModel		Loader::loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLuint> indices)
{
	GLuint vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	unbindVAO();
	return (RawModel(vaoID, indices.size()));
}

RawModel		Loader::loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLfloat> tangents, std::vector<GLuint> indices)
{
	GLuint vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	storeDataInAttributeList(3, 3, tangents);
	unbindVAO();
	return (RawModel(vaoID, indices.size()));
}

RawModel		Loader::loadToVAO(std::vector<GLfloat> positions, int dimensions)
{
	int vaoID = createVAO();
	storeDataInAttributeList(0, dimensions, positions);
	unbindVAO();
	return (RawModel(vaoID, positions.size() / dimensions));
}

GLuint 			Loader::createVAO()
{
	GLuint vaoID;

	glGenVertexArrays(1, &vaoID);
	_vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return (vaoID);
}

void 			Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void 			Loader::storeDataInAttributeList(int attributeNumber, int coordSize, std::vector<GLfloat> data)
{
	GLuint 	vboID;
	GLfloat *buffer;

	glGenBuffers(1, &vboID);
	_vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	buffer = &(data[0]);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint			Loader::loadTexture(const std::string& filePath)
{
	GLuint	textureID;

	// int 			width, height, channels;
	// unsigned char*	image;

	// image = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
	// glGenTextures(1, &textureID);
	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, textureID);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexImage2D(GL_TEXTURE_2D,
	// 			0,
	// 			GL_RGBA,
	// 			width,
	// 			height,
	// 			0,
	// 			GL_RGBA,
	// 			GL_UNSIGNED_BYTE,
	// 			image
	// 			);
	// glBindTexture(GL_TEXTURE_2D, 0);

	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(filePath);
	bmp.flipVertically();
	tdogl::Texture texture(bmp);
	textureID = texture.getTextureID();
	glTexImage2D(GL_TEXTURE_2D,
				0,
				tdogl::Texture::TextureFormatForBitmapFormat(bmp.format()),
				(GLsizei)bmp.width(),
				(GLsizei)bmp.height(),
				0,
				tdogl::Texture::TextureFormatForBitmapFormat(bmp.format()),
				GL_UNSIGNED_BYTE,
				bmp.pixelBuffer()
				);
	glBindTexture(GL_TEXTURE_2D, 0);


	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2);
	// SOIL_free_image_data(image);
	_textures.push_back(textureID);
	return (textureID);
}

GLuint			Loader::loadTextureWithoutFlip(const std::string& filePath)
{
	GLuint	textureID;

	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(filePath);
	tdogl::Texture texture(bmp);
	textureID = texture.getTextureID();
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2);
	_textures.push_back(textureID);
	return (textureID);
}

GLuint			Loader::loadGuiTexture(const std::string& filePath)
{
	GLuint	textureID;

	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(filePath);
	tdogl::Texture texture(bmp);
	textureID = texture.getTextureID();
	_textures.push_back(textureID);
	return (textureID);
}

GLuint 			Loader::loadCubeMap(std::vector<std::string> textureFiles)
{
	GLuint 			textureID;
	int 			width, height;
	unsigned char*	image;

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (int i = 0; i < (int)textureFiles.size(); ++i)
	{
		image = SOIL_load_image(textureFiles[i].c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0,
					GL_RGBA,
					width,
					height,
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					image
					);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	_textures.push_back(textureID);
	return (textureID);
}

void 			Loader::cleanUp()
{
	for (std::vector<GLuint>::iterator vao = _vaos.begin(); vao != _vaos.end(); ++vao)
	{
		glDeleteVertexArrays(1, &(*vao));
	}
	for (std::vector<GLuint>::iterator vbo = _vbos.begin(); vbo != _vbos.end(); ++vbo)
	{
		glDeleteBuffers(1, &(*vbo));
	}
	for (std::vector<GLuint>::iterator texture = _textures.begin(); texture != _textures.end(); ++texture)
	{
		glDeleteBuffers(1, &(*texture));
	}
}

void 			Loader::bindIndicesBuffer(std::vector<GLuint> data)
{
	GLuint	vboID;
	GLuint 	*buffer;

	glGenBuffers(1, &vboID);
	_vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	buffer = &(data[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), buffer, GL_STATIC_DRAW);
}