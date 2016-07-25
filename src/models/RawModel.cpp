#include "models/RawModel.h"
#include <iostream>

RawModel::RawModel(GLuint vaoID, int vertexCount)
{
	_vaoID = vaoID;
	_vertexCount = vertexCount;
}

RawModel::~RawModel()
{

}

GLuint	RawModel::getVaoID() const
{
	return (_vaoID);
}

int		RawModel::getVertexCount() const
{
	return (_vertexCount);
}
