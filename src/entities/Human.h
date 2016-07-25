#pragma once

#include "entities/NPC.h"

class Human: public NPC
{
public:
	Human(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale, std::string name, std::string task);
	virtual ~Human();

	void			move(std::vector<Terrain> terrains);
	void			jump();
	std::string		getTask();

	static float	gravity;

private:
	std::string 	_task;
	float	_runSpeed = 20;
	float	_turnSpeed = 160;
	float 	_jumpPower = 30;
	float 	_upwardsSpeed = 0;
	bool	_isInAir = false;
};