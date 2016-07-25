#include "entities/Light.h"
#include <iostream>

Light::Light(glm::vec3 position, glm::vec3 colour):
_position(position),
_colour(colour)
{
}

Light::Light(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation):
_position(position),
_colour(colour),
_attenuation(attenuation)
{
}

Light::~Light()
{

}

glm::vec3	Light::getPosition()
{
	return (_position);
}

glm::vec3	Light::getColour()
{
	return (_colour);
}

glm::vec3	Light::getAttenuation()
{
	return (_attenuation);
}

void		Light::setPosition(glm::vec3 position)
{
	_position = position;
}

void		Light::setColour(glm::vec3 colour)
{
	_colour = colour;
}

void		Light::setAttenuation(glm::vec3 attenuation)
{
	_attenuation = attenuation;
}

void		Light::increaseColour(float time)
{
	float lightValueChange = (time) / 3000;
	if (lightValueChange < 0.3)
	{
		lightValueChange = 0.3;
	}
	glm::vec3 value = glm::vec3(lightValueChange, lightValueChange, lightValueChange);
	setColour(value);
}

void		Light::decreaseColour(float time)
{
	float lightValueChange = (time) / 3000;
	if (lightValueChange < 0.3)
	{
		lightValueChange = 0.3;
	}
	glm::vec3 value = glm::vec3(lightValueChange, lightValueChange, lightValueChange);
	setColour(value);
}
