/*
** This class represents a terrain.
*/

#pragma once

#include "models/RawModel.h"
#include "renderEngine/Loader.h"
#include "textures/TerrainTexturePack.h"
#include "textures/Bitmap.h"

#include <glm/glm.hpp>

class Terrain
{
public:
	/*
	** Creates a new terrain.
	**
	** @gridX	the X coord in the world of the terrain.
	** @gridZ	the Z coord in the world of the terrain.
	** @loader	Use to load terrain.
	** @texture	The texture of the terrain.
	*/
	Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, const std::string& heightMap);
	virtual ~Terrain();

	constexpr static float 	SIZE = 160;
	float max_height = 40.0;
	float max_pixel_color = 256 * 256 * 256;

	float				getX();
	float				getZ();
	RawModel			getModel();
	TerrainTexturePack	getTexturePack();
	TerrainTexture 		getBlendMap();
	float				getHeightOfTerrain(float worldX, float worldZ);
	int					getVertexCount();

	static Terrain 		getTerrain(std::vector<Terrain> terrains, float worldX, float worldZ);



private:
	float							_x;
	float							_z;
	RawModel						_model;
	TerrainTexturePack				_texturePack;
	TerrainTexture 					_blendMap;
	int								_vertexCount;
	float**					 		_heights;

	/*
	** Generate a new terrain.
	*/
	RawModel		_generateTerrain(Loader loader, const std::string& heightMap);
	float			_getHeight(int x, int y, tdogl::Bitmap image);
	glm::vec3		_calculateNormal(int x, int y, tdogl::Bitmap image);


};