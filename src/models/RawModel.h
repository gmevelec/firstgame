/*
** This class is used to manipulate a 3D model.
*/

#pragma once
#include <GL/glew.h>

class RawModel
{
public:
	RawModel(GLuint vaoID, int vertexCount);
	virtual ~RawModel();

	GLuint	getVaoID() const;
	int		getVertexCount() const;

private:
	GLuint	_vaoID;
	int		_vertexCount;
};