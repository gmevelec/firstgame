#include "fontMeshCreator/TextMeshData.h"

TextMeshData::TextMeshData(std::vector<float> vertexPositions, std::vector<float> textureCoords):
_vertexPositions(vertexPositions),
_textureCoords(textureCoords)
{
}

TextMeshData::~TextMeshData()
{
}


std::vector<float>		TextMeshData::getVertexPositions()
{
	return (_vertexPositions);
}

std::vector<float>		TextMeshData::getTextureCoords()
{
	return (_textureCoords);
}

int						TextMeshData::getVertexCount()
{
	return (_vertexPositions.size() / 2);
}

