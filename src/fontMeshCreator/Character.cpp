#include "fontMeshCreator/Character.h"

Character::Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize, double xOffset, double yOffset, double sizeX, double sizeY, double xAdvance):
_id(id),
_xTextureCoord(xTextureCoord),
_yTextureCoord(yTextureCoord),
_xMaxTextureCoord(xTexSize + xTextureCoord),
_yMaxTextureCoord(yTexSize + yTextureCoord),
_xOffset(xOffset),
_yOffset(yOffset),
_sizeX(sizeX),
_sizeY(sizeY),
_xAdvance(xAdvance)
{
}

Character::~Character()
{
}

int			Character::getID()
{
	return (_id);
}

double		Character::getxTextureCoord()
{
	return (_xTextureCoord);
}

double		Character::getyTextureCoord()
{
	return (_yTextureCoord);
}

double		Character::getxMaxTextureCoord()
{
	return (_xMaxTextureCoord);
}

double		Character::getyMaxTextureCoord()
{
	return (_yMaxTextureCoord);
}

double		Character::getxOffset()
{
	return (_xOffset);
}

double		Character::getyOffset()
{
	return (_yOffset);
}

double		Character::getSizeX()
{
	return (_sizeX);
}

double		Character::getSizeY()
{
	return (_sizeY);
}

double		Character::getxAdvance()
{
	return (_xAdvance);
}

