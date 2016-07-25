#include "textures/TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(TerrainTexture backgroundTexture, TerrainTexture rTexture, TerrainTexture gTexture, TerrainTexture bTexture):
_backgroundTexture(backgroundTexture),
_rTexture(rTexture),
_gTexture(gTexture),
_bTexture(bTexture)
{

}

TerrainTexturePack::~TerrainTexturePack()
{
}

TerrainTexture 	TerrainTexturePack::getBackgroundTexture()
{
	return (_backgroundTexture);
}
TerrainTexture 	TerrainTexturePack::getrTexture()
{
	return (_rTexture);
}
TerrainTexture 	TerrainTexturePack::getgTexture()
{
	return (_gTexture);
}
TerrainTexture 	TerrainTexturePack::getbTexture()
{
	return (_bTexture);
}
