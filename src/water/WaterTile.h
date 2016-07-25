/*
** This class represents the waterTile.
*/
#pragma once

class WaterTile
{
public:
	WaterTile(float centerX, float centerZ, float height);
	~WaterTile();

	static float	tile_size;

	float	getHeight();
	float	getX();
	float	getZ();

private:
	float	_x;
	float	_z;
	float	_height;
};