#include "TerrainTexture.h"

TerrainTexture::TerrainTexture(int textureID):
_textureID(textureID)
{
}

TerrainTexture::~TerrainTexture()
{
}

int		TerrainTexture::getTextureID()
{
	return (_textureID);
}