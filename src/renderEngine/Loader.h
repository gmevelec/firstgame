/*
** This class is used to load a 3D model.
*/

#pragma once

#include "models/RawModel.h"
#include "textures/Bitmap.h"
#include "textures/Texture.h"
#include <vector>

class Loader
{
public:
	Loader();
	virtual ~Loader();

	/*
	** @param positions		Vector of GLfloat containing positions of the 3D model.
	** @param indices 		Vector of GLuint containing indices of the 3D model.
	**
	** @return	A RawModel bind with a VAO and the size of indices.
	**
	** This function takes positions and indices of a 3D model, create a VAO,
	** bind the indices buffer generate a VBO and return a RawModel.
	*/
	// RawModel	loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> texturecoords, std::vector<GLfloat> normals, std::vector<GLuint> indices);
	RawModel	loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLuint> indices);
	RawModel	loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLfloat> tangents, std::vector<GLuint> indices);

	RawModel	loadToVAO(std::vector<GLfloat> positions, int dimensions);

	/*
	** @return	VAO ID for the RawModel.
	**
	** This function creates, store, bind and return a new VAO.
	*/
	GLuint		createVAO();

	/*
	** @param attributeNumber	The attribute used in the function glVertexAttribPointer().
	** @param positions			Vector of GLfloat containing positions of the 3D model.
	**
	** This function generates a new VBO, store and bind it.
	** Then, it creates a new data store for the buffer object and specify the location
	** and data format of the array to use when rendering.
	*/
	void		storeDataInAttributeList(int attributeNumber, int coordSize, std::vector<GLfloat> positions);

	void		unbindVAO();


	GLuint		loadTexture(const std::string& filePath);
	GLuint		loadTextureWithoutFlip(const std::string& filePath);
	GLuint		loadGuiTexture(const std::string& filePath);
	GLuint 		loadCubeMap(std::vector<std::string> textureFiles);

	/*
	** This function delete all VAOS and VBOS.
	*/
	void		cleanUp();

private:
	std::vector<GLuint> _vaos;
	std::vector<GLuint> _vbos;
	std::vector<GLuint> _textures;

	void		bindIndicesBuffer(std::vector<GLuint> data);
};