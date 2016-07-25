#include "terrains/Terrain.h"
#include "tools/Logger.h"
#include "tools/Maths.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

Terrain::Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, const std::string& heightMap) :
_model(_generateTerrain(loader, heightMap)),
_texturePack(texturePack),
_blendMap(blendMap)
{
	_x = gridX * SIZE;
	_z = gridZ * SIZE;
}

Terrain::~Terrain()
{

}

Terrain 		Terrain::getTerrain(std::vector<Terrain> terrains, float worldX, float worldZ)
{
	for(Terrain& terrain : terrains)
	{
		float terrainX = worldX - terrain.getX();
		float terrainZ = worldZ - terrain.getZ();
		float gridSquareSize = Terrain::SIZE / ((float) terrain.getVertexCount() - 1.0f);
		int gridX = (int) floor(terrainX / gridSquareSize);
		int gridZ = (int) floor(terrainZ / gridSquareSize);
		if(!(gridX < 0 || gridX >= terrain.getVertexCount() - 1 || gridZ < 0 || gridZ >= terrain.getVertexCount() - 1))
			return (terrain);
	}
}

float			Terrain::getHeightOfTerrain(float worldX, float worldZ)
{
	float terrainX = worldX - _x;
	float terrainZ = worldZ - _z;
	float gridSquareSize = SIZE / ((float)(_vertexCount) -1);
	int gridX = (int) floor(terrainX / gridSquareSize);
	int gridZ = (int) floor(terrainZ / gridSquareSize);
	if (gridX >= _vertexCount - 1 || gridZ >= _vertexCount - 1 || gridX < 0 || gridZ < 0)
	{
		return (0);
	}
	float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
	float answer;
	if (xCoord <= (1 - zCoord))
	{
		answer = Maths::barryCentric(glm::vec3(0, _heights[gridX][gridZ], 0), glm::vec3(1, _heights[gridX + 1][gridZ], 0),
									glm::vec3(0, _heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	else
	{
		answer = Maths::barryCentric(glm::vec3(1, _heights[gridX + 1][gridZ], 0), glm::vec3(1, _heights[gridX + 1][gridZ + 1], 1),
									glm::vec3(0, _heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	return (answer);
}

RawModel		Terrain::_generateTerrain(Loader loader, const std::string& heightMap)
{
	tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(heightMap);
	_vertexCount = bmp.height();
	int count = _vertexCount * _vertexCount;
	_heights = new float*[_vertexCount];
	for (int i = 0; i < _vertexCount; ++i)
	{
		_heights[i] = new float[_vertexCount];
	}

	std::vector<GLfloat> vertices(count * 3);
	std::vector<GLfloat> normals(count * 3);
	std::vector<GLfloat> textureCoords(count * 2);
	std::vector<GLuint> indices(6 * (_vertexCount - 1) * (_vertexCount - 1));


	int		vertexPointer = 0;
	for (int i = 0; i < _vertexCount; ++i)
	{
		for (int j = 0; j < _vertexCount; ++j)
		{
			float height = _getHeight(j, i, bmp);
			_heights[j][i] = height;
			vertices[vertexPointer * 3] = (float)j / ((float)_vertexCount - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = height;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)_vertexCount - 1) * SIZE;
			glm::vec3 normal = _calculateNormal(j, i, bmp);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
			textureCoords[vertexPointer * 2] = (float)j / ((float)_vertexCount - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)_vertexCount - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < _vertexCount - 1; ++gz)
	{
		for (int gx = 0; gx < _vertexCount - 1; ++gx)
		{
			int topLeft = (gz * _vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * _vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.loadToVAO(vertices, textureCoords, normals, indices);
}

glm::vec3		Terrain::_calculateNormal(int x, int y, tdogl::Bitmap image)
{
	float heightL = _getHeight(x - 1, y, image);
	float heightR = _getHeight(x + 1, y, image);
	float heightD = _getHeight(x, y - 1, image);
	float heightU = _getHeight(x, y + 1, image);
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	glm::normalize(normal);
	return (normal);
}

float			Terrain::_getHeight(int x, int y, tdogl::Bitmap image)
{
	if (x < 0 || x >= (int)image.height() || y < 0 || y >= (int)image.height())
		return (0);
	unsigned char* pixel = image.getPixel(x, y);
	int color = ((((int)pixel[2] & 0xFF) << 16)) + ((((int)pixel[1] &0xFF) << 8)) + ((((int)pixel[0])&0xFF));
	float height = color;
	// height += max_pixel_color / 2.0f;
	height /= max_pixel_color / 2.0f;
	height -= 1;
	height *= max_height;
	return (height);
}

float			Terrain::getX()
{
	return (_x);
}

float			Terrain::getZ()
{
	return (_z);
}

RawModel		Terrain::getModel()
{
	return (_model);
}

TerrainTexturePack	Terrain::getTexturePack()
{
	return (_texturePack);
}

TerrainTexture 		Terrain::getBlendMap()
{
	return (_blendMap);
}

int					Terrain::getVertexCount()
{
	return (_vertexCount);
}