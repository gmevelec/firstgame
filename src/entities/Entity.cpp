#include "entities/Entity.h"

Entity::Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale):
_model(model),
_position(position),
_rotation(rotation),
_scale(scale)
{

}

Entity::Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale, int index):
_model(model),
_position(position),
_rotation(rotation),
_scale(scale),
_textureIndex(index)
{

}

Entity::~Entity()
{
	
}

float			Entity::getTextureXOffset()
{
	int column = _textureIndex % _model.getTexture().getNumberOfRows();
	return ((float)column / (float)_model.getTexture().getNumberOfRows());
}

float			Entity::getTextureYOffset()
{
	int row = _textureIndex / _model.getTexture().getNumberOfRows();
	return ((float)row / (float)_model.getTexture().getNumberOfRows());
}

void			Entity::increasePosition(glm::vec3 position)
{
	_position += position;
}

void			Entity::increaseRotation(glm::vec3 rotation)
{
	_rotation += rotation;
}

TexturedModel	Entity::getModel()
{
	return (_model);
}

glm::vec3		Entity::getPosition()
{
	return (_position);
}

glm::vec3		Entity::getRotation()
{
	return (_rotation);
}

float			Entity::getScale()
{
	return (_scale);
}

void			Entity::setModel(TexturedModel model)
{
	_model = model;
}

void			Entity::setPosition(glm::vec3 position)
{
	_position = position;
}

void			Entity::setRotation(glm::vec3 rotation)
{
	_rotation = rotation;
}

void			Entity::setScale(float scale)
{
	_scale = scale;
}