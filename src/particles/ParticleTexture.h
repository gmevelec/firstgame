/*
** This class represents the texture of a particle.
*/
#pragma once

class ParticleTexture
{
public:
	ParticleTexture(int textureID, int numberOfRows);
	virtual ~ParticleTexture();

	int		getTextureID() const;
	int		getNumberOfRows() const;

private:
	int		_textureID;
	int		_numberOfRows;	
};