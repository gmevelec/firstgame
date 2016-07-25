#include "water/WaterTile.h"

float WaterTile::tile_size = 100;

WaterTile::WaterTile(float centerX, float centerZ, float height):
_x(centerX),
_z(centerZ),
_height(height)
{
}
WaterTile::~WaterTile()
{
}

float	WaterTile::getHeight()
{
	return (_height);
}
float	WaterTile::getX()
{
	return (_x);
}
float	WaterTile::getZ()
{
	return (_z);
}