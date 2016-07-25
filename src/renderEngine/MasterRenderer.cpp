#include "renderEngine/MasterRenderer.h"
#include "tools/Logger.h"
#include <algorithm>

float MasterRenderer::_RED = 0.01f;
float MasterRenderer::_GREEN = 0.01f;
float MasterRenderer::_BLUE = 0.01f;

float MasterRenderer::_FOV = 70.0f;
float MasterRenderer::_NEAR_PLANE = 0.1f;
float MasterRenderer::_FAR_PLANE = 10000.0f;


MasterRenderer::MasterRenderer(Loader loader, Camera& camera):
_projectionMatrix(glm::perspective(_FOV, _aspectRatio, _NEAR_PLANE, _FAR_PLANE)),
_entityRenderer(EntityRenderer(_staticShader, _projectionMatrix)),
_terrainRenderer(TerrainRenderer(_terrainShader, _projectionMatrix)),
_skyboxRenderer(loader, _projectionMatrix),
_normalMapRenderer(_projectionMatrix),
_shadowMapRenderer(ShadowMapMasterRenderer(camera))
{
	enableCulling();
	glEnable(GL_DEPTH_TEST);
}

MasterRenderer::~MasterRenderer()
{

}

void		MasterRenderer::enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void		MasterRenderer::disableCulling()
{
	glDisable(GL_CULL_FACE);
}

void		MasterRenderer::renderScene(std::vector<Entity> entities, std::vector<Entity> normalEntities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera, glm::vec4 clipPlane)
{
	for (Terrain terrain: terrains)
	{
		processTerrain(terrain);
	}
	for (Entity entity: entities)
	{
		processEntity(entity);
	}
	for (Entity entity: normalEntities)
	{
		processNormalMapEntity(entity);
	}
	render(lights, camera, clipPlane);
}

void		MasterRenderer::render(std::vector<Light> lights, Camera camera, glm::vec4 clipPlane)
{
	prepare();
	
	_terrainShader.start();
	_terrainShader.loadClipPlane(clipPlane);
	_terrainShader.loadSkyColour(_RED, _GREEN, _BLUE);
	_terrainShader.loadLights(lights);
	_terrainShader.loadViewMatrix(camera);
	_terrainRenderer.render(_terrains);
	_terrainShader.stop();

	_staticShader.start();
	_staticShader.loadClipPlane(clipPlane);
	_staticShader.loadSkyColour(_RED, _GREEN, _BLUE);
	_staticShader.loadLights(lights);
	_staticShader.loadViewMatrix(camera);
	_entityRenderer.render(_entities);
	_staticShader.stop();

	_normalMapRenderer.render(_normalMapEntities, clipPlane, lights, camera);
	_skyboxRenderer.render(camera, _RED, _GREEN, _BLUE);
	
	_terrains.clear();
	_entities.clear();
	_normalMapEntities.clear();
}

void			MasterRenderer::cleanUp()
{
	_staticShader.cleanUp();
	_terrainShader.cleanUp();
	_normalMapRenderer.cleanUp();
	_shadowMapRenderer.cleanUp();
}

void			MasterRenderer::processTerrain(Terrain terrain)
{
	_terrains.push_back(terrain);
}


void			MasterRenderer::processEntity(Entity entity)
{
	TexturedModel entityModel = entity.getModel();
	_entities.insert(tMap::value_type(entityModel, std::vector<Entity>()));
	_entities[entityModel].push_back(entity);
}

void			MasterRenderer::processNormalMapEntity(Entity entity)
{
	TexturedModel entityModel = entity.getModel();
	_normalMapEntities.insert(tMap::value_type(entityModel, std::vector<Entity>()));
	_normalMapEntities[entityModel].push_back(entity);
}

void			MasterRenderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(_RED, _GREEN, _BLUE, 1);
}

void			MasterRenderer::renderShadowMap(std::vector<Entity> entities, Light sun)
{
	for (Entity entity: entities)
	{
		processEntity(entity);
	}
	_shadowMapRenderer.render(_entities, sun);
	_entities.clear();
}


int 			MasterRenderer::getShadowMapTexture()
{
	return (_shadowMapRenderer.getShadowMap());
}

SkyboxRenderer 	MasterRenderer::getSkybox()
{
	return (_skyboxRenderer);
}

glm::mat4		MasterRenderer::getProjectionMatrix()
{
	return (_projectionMatrix);
}