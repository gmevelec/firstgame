#include "particles/ParticleTexture.h"

ParticleTexture::ParticleTexture(int textureID, int numberOfRows):
_textureID(textureID),
_numberOfRows(numberOfRows)
{
}

ParticleTexture::~ParticleTexture()
{
}

int		ParticleTexture::getTextureID() const
{
	return (_textureID);
}

int		ParticleTexture::getNumberOfRows() const
{
	return (_numberOfRows);
}
