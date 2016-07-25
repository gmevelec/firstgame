#include "particles/Particle.h"
#include "entities/Player.h"
#include "engineTester/MainGame.h"
#include "particles/ParticleMaster.h"

#include <math.h>
#include <glm/gtx/norm.hpp>

Particle::Particle(ParticleTexture texture, glm::vec3 position, glm::vec3 velocity, float gravityEffet, float lifeLength, float rotation, float scale):
_texture(texture),
_position(position),
_velocity(velocity),
_gravityEffect(gravityEffet),
_lifeLength(lifeLength),
_rotation(rotation),
_scale(scale)
{
	ParticleMaster::addParticle(*this);
}

Particle::~Particle()
{
}

glm::vec3	Particle::getPosition()
{
	return (_position);
}

float		Particle::getRotation()
{
	return (_rotation);
}

float		Particle::getScale()
{
	return (_scale);
}

ParticleTexture 	Particle::getTexture()
{
	return (_texture);
}

glm::vec2			Particle::getTexOffset1()
{
	return (_texOffset1);
}

glm::vec2			Particle::getTexOffset2()
{
	return (_texOffset2);
}

float				Particle::getBlendFactor()
{
	return (_blendFactor);
}

float				Particle::getDistance()
{
	return (_distance);
}

bool		Particle::update(Camera camera)
{
	_velocity.y += Player::gravity * _gravityEffect * MainGame::delta;
	glm::vec3 change(_velocity);
	change = change * MainGame::delta;
	_position = _position + change;
	glm::vec3 tmp = camera.getPosition() - _position;
	_distance = glm::length2(tmp);
	_updateTextureCoordInfo();
	_elapsedTime += MainGame::delta;
	return (_elapsedTime < _lifeLength);
}

void		Particle::_updateTextureCoordInfo()
{
	float lifeFactor = _elapsedTime / _lifeLength;
	int stageCount = _texture.getNumberOfRows() * _texture.getNumberOfRows();
	float atlasProgression = lifeFactor * stageCount;
	int index1 = (int)floor(atlasProgression);
	int index2  = index1 < stageCount - 1 ? index1 + 1 : index1;
	_blendFactor = fmod(atlasProgression, 1);
	_setTextureOffset(_texOffset1, index1);
	_setTextureOffset(_texOffset2, index2);
}

void		Particle::_setTextureOffset(glm::vec2& offset, int index)
{
	int column = index % _texture.getNumberOfRows();
	int row = index / _texture.getNumberOfRows();
	offset.x = (float)column / _texture.getNumberOfRows();
	offset.y = (float)row / _texture.getNumberOfRows();
}