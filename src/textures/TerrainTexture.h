#pragma once

class TerrainTexture
{
public:
	TerrainTexture(int textureID);
	~TerrainTexture();

	int		getTextureID();

private:
	int		_textureID;	
};