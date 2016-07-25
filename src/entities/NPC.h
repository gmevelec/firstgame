#pragma once

#include "entities/Entity.h"
#include "terrains/Terrain.h"
#include <string>
#include <vector>

class NPC : public Entity
{
public:
	NPC(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale, std::string name);
	virtual ~NPC();

	virtual void	move(std::vector<Terrain> terrains) = 0;
	std::string		getName();

protected:
	std::string 	_name;

};