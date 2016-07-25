#pragma once

#include "textures/TerrainTexture.h"

class TerrainTexturePack
{
public:
	TerrainTexturePack(TerrainTexture backgroundTexture, TerrainTexture rTexture, TerrainTexture gTexture, TerrainTexture bTexture);
	~TerrainTexturePack();

	TerrainTexture getBackgroundTexture();
	TerrainTexture getrTexture();
	TerrainTexture getgTexture();
	TerrainTexture getbTexture();

private:
	TerrainTexture 	_backgroundTexture;
	TerrainTexture 	_rTexture;
	TerrainTexture 	_gTexture;
	TerrainTexture 	_bTexture;
};