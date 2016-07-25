/*
** This class is used for define a particle's behavior.
*/
#pragma once

#include <glm/glm.hpp>
#include "particles/ParticleTexture.h"

class ParticleSystem
{
public:
	/*
	** Create tjhe system to manage particles.
	*/
	ParticleSystem(ParticleTexture texture, float pps, float speed, float gravityComplient, float lifeLength, float averageScale);
	virtual ~ParticleSystem();

	void		generateParticles(glm::vec3 systemCenter);
	void 		setDirection(glm::vec3 direction, float deviation);
	void		randomizeRotation();
	void		setSpeedError(float error);
	void		setLifeError(float error);
	void		setScaleError(float error);

private:
	ParticleTexture	_texture;
	float	_pps;
	float	_averageSpeed;
	float	_gravityComplient;
	float	_averageLifeLength;
	float	_averageScale;

	float	_speedError = 0;
	float	_lifeError = 0;
	float	_scaleError = 0;
	bool	_randomRotation = false;

	glm::vec3	_direction;
	float		_directionDeviation = 0;


	void		_emitParticle(glm::vec3 center);
	float		_generateValue(float average, float errorMargin);
	float 		_generateRotation();
	glm::vec3	_generateRandomUnitVectorWithinCone(glm::vec3 coneDirection, float angle);
	glm::vec3	_generateRandomUnitVector();
};