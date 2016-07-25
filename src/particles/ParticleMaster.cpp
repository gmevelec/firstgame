#include "particles/ParticleMaster.h"
#include "particles/InsertionSort.h"

pMap ParticleMaster::particles;

ParticleMaster::ParticleMaster(Loader loader, glm::mat4 projectionMatrix):
renderer(ParticleRenderer(loader, projectionMatrix))
{
}

void	ParticleMaster::update(Camera camera)
{
	pMap::iterator itMap = particles.begin();
	while (itMap != particles.end())
	{
		std::vector<Particle>::iterator it = (itMap->second).begin();
		while (it != itMap->second.end())
		{
			Particle& p = *it;
			bool stillAlive = p.update(camera);
			if (!stillAlive)
			{
				it = itMap->second.erase(it);
			}
			else
			{
				++it;
			}
		}
		InsertionSort::sortHighToLow(itMap->second);
		++itMap;
	}
}

void	ParticleMaster::renderParticles(Camera camera)
{
	renderer.render(particles, camera);
}

void	ParticleMaster::cleanUp()
{
	renderer.cleanUp();
}

void	ParticleMaster::addParticle(Particle particle)
{
	ParticleTexture particleTexture	= particle.getTexture();
	particles.insert(pMap::value_type(particleTexture, std::vector<Particle>()));
	particles[particleTexture].push_back(particle);
}
