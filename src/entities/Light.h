/*
** This class represents a Light.
*/

#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 colour);
	Light(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation);
	~Light();

	glm::vec3	getPosition();
	glm::vec3	getColour();
	glm::vec3	getAttenuation();
	void		setPosition(glm::vec3 position);
	void		setColour(glm::vec3 colour);
	void		setAttenuation(glm::vec3 attenuation);
	void		increaseColour(float time);
	void		decreaseColour(float time);

private:
	glm::vec3	_position;
	glm::vec3	_colour;
	glm::vec3	_attenuation = glm::vec3(1, 0, 0);
};