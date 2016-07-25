#include "textures/ModelTexture.h"
#include <iostream>

ModelTexture::ModelTexture(GLuint id)
{
	_textureID = id;
	_shineDamper = 1;
	_reflectivity = 0;
}

ModelTexture::~ModelTexture()
{
	
}

GLuint		ModelTexture::getTextureID() const
{
	return (_textureID);
}

GLuint		ModelTexture::getNormalMap() const
{
	return (_normalMap);
}

float		ModelTexture::getShineDamper() const
{
	return (_shineDamper);
}

float		ModelTexture::getReflectivity() const
{
	return (_reflectivity);
}

bool		ModelTexture::getTransparancy() const
{
	return (_transparancy);
}

bool		ModelTexture::getUseFakeLighting() const
{
	return (_useFakeLighting);
}

int			ModelTexture::getNumberOfRows() const
{
	return (_numberOfRows);
}



void		ModelTexture::setShineDamper(float shineDamper)
{
	_shineDamper = shineDamper;
}

void		ModelTexture::setReflectivity(float reflectivity)
{
	_reflectivity = reflectivity;
}

void		ModelTexture::setTransparancy(bool value)
{
	_transparancy = value;
}

void		ModelTexture::setUseFakeLighting(bool value)
{
	_useFakeLighting = value;
}

void		ModelTexture::setNumberOfRows(int numberOfRows)
{
	_numberOfRows = numberOfRows;
}

void		ModelTexture::setNormalMap(GLuint normalMap)
{
	_normalMap = normalMap;
}