#include "entities/NPC.h"

NPC::NPC(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale, std::string name):
Entity(model, position, rotation, scale),
_name(name)
{
}

NPC::~NPC()
{
}
