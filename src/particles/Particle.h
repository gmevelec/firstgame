/*
** This class represents a Particle.
*/
#pragma once

#include <glm/glm.hpp>
#include "particles/ParticleTexture.h"
#include "entities/Camera.h"

class Particle
{
public:
	/*
	** Create a Particle with a texture, and position, a velocity, a gravity effect, a life length, a rotation and a scale.
	** After being created, the particle is added to the map of particles.
	**
	** @param ParticleTexture		The texture to apply to the particle.
	** @param position 				The position of the particle.
	** @param velocity 				The velocity of the particle.
	** @param gravityEffect 		The power of the gravity on the particle.
	** @param lifeLenght 			The life during the particle stay alive.
	** @param rotation 				The rotation of the particle.
	** @param scale 				The scale of the particle.
	*/
	Particle(ParticleTexture texture, glm::vec3 position, glm::vec3 velocity, float gravityEffet, float lifeLength, float rotation, float scale);
	virtual~Particle();

	glm::vec3		getPosition();
	float			getRotation();
	float			getScale();
	ParticleTexture getTexture();
	glm::vec2		getTexOffset1();
	glm::vec2		getTexOffset2();
	float			getBlendFactor();
	float			getDistance();

	bool			update(Camera camera);

private:
	ParticleTexture	_texture;
	glm::vec3		_position;
	glm::vec3		_velocity;
	float			_gravityEffect;
	float			_lifeLength;
	float			_rotation;
	float			_scale;
	float			_elapsedTime = 0;
	float			_distance;

	glm::vec2		_texOffset1 = glm::vec2();
	glm::vec2		_texOffset2 = glm::vec2();
	float			_blendFactor;

	void			_updateTextureCoordInfo();
	void			_setTextureOffset(glm::vec2& offset, int index);
};