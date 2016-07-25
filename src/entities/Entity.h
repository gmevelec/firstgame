/*
** This class represents an entity in the game and allow to manipulate it.
*/

#pragma once

#include "models/TexturedModel.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Entity
{
public:
	/*
	** Creates an entity from a TexturedModel.
	**
	** @param model 	The TexturedModel to use for the entity.
	** @param position 	The vector representing the position XYZ for the entity.
	** @param rotation 	The vector representing the rotation XYZ for the entity.
	** @param scale 	A float reprensenting the scale of the entity.
	*/
	Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale);
	Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale, int index);
	virtual ~Entity();


	float			getTextureXOffset();

	float			getTextureYOffset();

	/*
	** Increase position of the entity.
	**
	** @param position	A vector containing values for increase position on the XYZ axe. Decrease if < 0.
	*/
	void			increasePosition(glm::vec3 position);

	/*
	** Increase rotation of the entity.
	**
	** @param rotation	A vector containing values for increase rotation on the XYZ axe. Decrease if < 0.
	*/
	void			increaseRotation(glm::vec3 rotation);

	/*
	** All getters and setters.
	*/
	TexturedModel	getModel();
	glm::vec3		getPosition();
	glm::vec3		getRotation();
	float			getScale();

	void			setModel(TexturedModel model);
	void			setPosition(glm::vec3 position);
	void			setRotation(glm::vec3 rotation);
	void			setScale(float scale);
	
private:
	TexturedModel	_model;
	glm::vec3		_position;
	glm::vec3		_rotation;
	float			_scale;
	int 			_textureIndex = 0;
};