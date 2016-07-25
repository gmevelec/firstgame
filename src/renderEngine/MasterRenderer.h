/*
** This class is used for render all the game.
*/

#pragma once

#include "engineTester/MainGame.h"
#include "shaders/StaticShader.h"
#include "renderEngine/EntityRenderer.h"
#include "renderEngine/TerrainRenderer.h"
#include "models/TexturedModel.h"
#include "entities/Entity.h"
#include "entities/Light.h"
#include "entities/Camera.h"
#include "terrains/Terrain.h"
#include "skybox/SkyboxRenderer.h"
#include "normalmapping/NormalMappingRenderer.h"
#include "shadows/ShadowMapMasterRenderer.h"

#include <map>
#include <glm/mat4x4.hpp>

class MasterRenderer
{
public:
	MasterRenderer(Loader loader, Camera& camera);
	~MasterRenderer();

	void		cleanUp();
	void		renderScene(std::vector<Entity> entities, std::vector<Entity> normalEntities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera, glm::vec4 clipPlane);
	void		render(std::vector<Light> lights, Camera camera, glm::vec4 clipPlane);
	void		processEntity(Entity entity);
	void		processNormalMapEntity(Entity entity);
	void		processTerrain(Terrain terrain);

	void		prepare();

	static void	enableCulling();
	static void	disableCulling();


	void			renderShadowMap(std::vector<Entity> entities, Light sun);

	int 			getShadowMapTexture();
	SkyboxRenderer 	getSkybox();
	glm::mat4 		getProjectionMatrix();

	static float		_FOV;
	static float		_NEAR_PLANE;
	static float		_FAR_PLANE;
	float		_aspectRatio = (float)MainGame::screenWidth / (float)MainGame::screenHeight;
	static float _RED;
	static float _GREEN;
	static float _BLUE;

private:
	glm::mat4 	_projectionMatrix;
	
	std::vector<Terrain> _terrains;

	StaticShader 			_staticShader;
	EntityRenderer 			_entityRenderer;
	TerrainShader			_terrainShader;
	TerrainRenderer			_terrainRenderer;
	SkyboxRenderer			_skyboxRenderer;
	NormalMappingRenderer	_normalMapRenderer;
	ShadowMapMasterRenderer	_shadowMapRenderer;
	
	std::map<TexturedModel, std::vector<Entity>, tmCompare> _entities;
	std::map<TexturedModel, std::vector<Entity>, tmCompare> _normalMapEntities;


};