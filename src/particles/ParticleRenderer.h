/*
** This class is used to render particles.
*/
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "particles/Particle.h"
#include "particles/ParticleShader.h"
#include "particles/ParticleTexture.h"
#include "renderEngine/Loader.h"
#include "entities/Camera.h"

struct ptCompare
{
public:
	bool operator() (const ParticleTexture& t1, const ParticleTexture& t2) const
	{
		return ((t1.getTextureID() < t2.getTextureID()) ||
			   (t1.getNumberOfRows() < t2.getNumberOfRows()));
	}
};

typedef std::map<ParticleTexture, std::vector<Particle>, ptCompare> pMap;


class ParticleRenderer
{
public:
	ParticleRenderer(Loader loader, glm::mat4 projectionMatrix);
	virtual ~ParticleRenderer();
	
	void		render(pMap& particles, Camera camera);
	void		cleanUp();

private:
	Loader 				_loader;
	GLuint 				_vbo;
	RawModel			_quad;
	ParticleShader		_shader;
	int					_maxInstances = 10000;
	int 				_instanceDataLength = 21;

	static std::vector<float>	_vertices;

	void		_updateModelViewMatrix(glm::vec3 position, float rotation, float scale, glm::mat4 viewMatrix);
	void		_prepare();
	void		_finishRendering();
	void		_bindTexture(ParticleTexture texture);
};