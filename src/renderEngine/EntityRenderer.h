/*
** This class is used to render an Entity.
*/

#pragma once

#include "engineTester/MainGame.h"
#include "models/RawModel.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include "shaders/StaticShader.h"
#include "tools/Maths.h"

#include <glm/mat4x4.hpp>
#include <vector>
#include <map>

struct tmCompare
{
public:
	bool operator() (const TexturedModel& t1, const TexturedModel& t2) const
	{
		return ((t1.getRawModel().getVaoID() < t2.getRawModel().getVaoID()) ||
			   (t1.getTextureConst().getTextureID() < t2.getTextureConst().getTextureID()));
	}
};

typedef std::map<TexturedModel, std::vector<Entity>, tmCompare> tMap;

class EntityRenderer
{
public:
	EntityRenderer(StaticShader shader, glm::mat4 projectionMatrix);
	virtual ~EntityRenderer();

	void		render(tMap entities);

private:

	StaticShader	_shader;

	void		prepareTexturedModel(TexturedModel model);
	void		unbindTexturedModel();
	void		prepareInstance(Entity entity);
};
