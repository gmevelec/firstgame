/*
** This class is used to manage particles.
*/
#pragma once

#include "particles/Particle.h"
#include "particles/ParticleRenderer.h"
#include "renderEngine/Loader.h"
#include "entities/Camera.h"
#include <glm/glm.hpp>
#include <map>

class ParticleMaster
{
private:
	static pMap	particles;
	ParticleRenderer		renderer;
	
public:
	ParticleMaster(Loader loader, glm::mat4 projectionMatrix);
	void			update(Camera camera);
	void			renderParticles(Camera camera);
	void			cleanUp();
	static void		addParticle(Particle particle);
};