#include "particles/ParticleSystem.h"
#include "engineTester/MainGame.h"
#include "particles/Particle.h"
#include "tools/Maths.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/gtx/vector_query.hpp>

ParticleSystem::ParticleSystem(ParticleTexture texture, float pps, float speed, float gravityComplient, float lifeLength, float averageScale):
_texture(texture),
_pps(pps),
_averageSpeed(speed),
_gravityComplient(gravityComplient),
_averageLifeLength(lifeLength),
_averageScale(averageScale)
{
}

ParticleSystem::~ParticleSystem()
{
}

void 		ParticleSystem::setDirection(glm::vec3 direction, float deviation)
{
	_direction = direction;
	_directionDeviation = (float)(deviation * M_PI);
}

void		ParticleSystem::randomizeRotation()
{
	_randomRotation = true;
}

void		ParticleSystem::setSpeedError(float error)
{
	_speedError = error * _averageSpeed;
}

void		ParticleSystem::setLifeError(float error)
{
	_lifeError = error * _averageLifeLength;
}

void		ParticleSystem::setScaleError(float error)
{
	_scaleError = error * _averageScale;
}

void		ParticleSystem::generateParticles(glm::vec3 systemCenter)
{
	float 	delta = MainGame::delta;
	float 	particlesToCreate = _pps * delta;
	int 	count = (int)floor(particlesToCreate);
	float	partialParticle = fmod(particlesToCreate, 1);

	for (int i = 0; i < count; ++i)
	{
		_emitParticle(systemCenter);
	}
	if (Maths::randomFloat() < partialParticle)
	{
		_emitParticle(systemCenter);
	}
}

void		ParticleSystem::_emitParticle(glm::vec3 center)
{
	glm::vec3 velocity;
	if (!glm::isNull(_direction, 0.0f))
	{
		velocity = _generateRandomUnitVectorWithinCone(_direction, _directionDeviation);
	}
	else
	{
		velocity = _generateRandomUnitVector();
	}
	velocity = glm::normalize(velocity);
	velocity *= _generateValue(_averageSpeed, _speedError);
	float scale = _generateValue(_averageScale, _scaleError);
	float lifeLength = _generateValue(_averageLifeLength, _lifeError);
	Particle(_texture, glm::vec3(center), velocity, _gravityComplient, lifeLength, _generateRotation(), scale);
}

float		ParticleSystem::_generateValue(float average, float errorMargin)
{
	float offset = (Maths::randomFloat() - 0.5f) * 2.0f * errorMargin;
	return (average + offset);
}

float 		ParticleSystem::_generateRotation()
{
	if (_randomRotation)
	{
		return (Maths::randomFloat() * 360.0f);
	}
	else
	{
		return (0);
	}
}

glm::vec3	ParticleSystem::_generateRandomUnitVectorWithinCone(glm::vec3 coneDirection, float angle)
{
	float cosAngle = (float)cos(angle);
	float theta = (float)(Maths::randomFloat() * 2.0f * M_PI);
	float z = cosAngle + (Maths::randomFloat() * (1 - cosAngle));
	float rootOneMinusZSquared = (float)sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared * cos(theta));
	float y = (float)(rootOneMinusZSquared * sin(theta));

	glm::vec4 direction(x, y, z, 1);
	if (coneDirection.x != 0 || coneDirection.y != 0 || (coneDirection.z != 1 && coneDirection.z != -1))
	{
		glm::vec3 rotateAxis = glm::cross(coneDirection, glm::vec3(0, 0, 1));
		rotateAxis = glm::normalize(rotateAxis);
		float rotateAngle = (float)acos(glm::dot(coneDirection, glm::vec3(0, 0, 1)));
		glm::mat4 rotationMatrix;
		rotationMatrix = glm::rotate(rotationMatrix, -rotateAngle, rotateAxis);
		direction = rotationMatrix * direction;
	}
	else if (coneDirection.z == -1)
	{
		direction.z *= -1;
	}
	return (glm::vec3(direction.x, direction.y, direction.z));
}

glm::vec3	ParticleSystem::_generateRandomUnitVector()
{
	float theta = (float)(Maths::randomFloat() * 2.0f * M_PI);
	float z = (Maths::randomFloat() * 2.0f) - 1;
	float rootOneMinusZSquared = (float)sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared * cos(theta));
	float y = (float)(rootOneMinusZSquared * sin(theta));
	return (glm::vec3(x, y, z));
}