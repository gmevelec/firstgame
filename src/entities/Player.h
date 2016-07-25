/*
** This class represents the player.
*/

#pragma once

#include "entities/Entity.h"
#include "engineTester/MainGame.h"
#include "tools/Logger.h"
#include "terrains/Terrain.h"
#include <map>

class Player : public Entity
{
public:
	/*
	** @param model 		The TexturedModel who represents the player.
	** @param position 		The position where the player spawns.
	** 	
	*/
	Player(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale);
	~Player();

	static float	gravity;

	void		move(std::vector<Terrain> terrains);
	void		jump();

private:
	float	_runSpeed = 20;
	float	_turnSpeed = 160;
	float 	_jumpPower = 30;
	float 	_upwardsSpeed = 0;
	bool	_isInAir = false;
};
