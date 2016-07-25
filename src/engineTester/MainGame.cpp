#include "engineTester/MainGame.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "renderEngine/Loader.h"
#include "renderEngine/OBJLoader.h"
#include "renderEngine/MasterRenderer.h"
#include "models/TexturedModel.h"
#include "models/DataModel.h"
#include "textures/ModelTexture.h"
#include "textures/TerrainTexturePack.h"
#include "tools/Logger.h"
#include "tools/Maths.h"
#include "entities/Light.h"
#include "entities/Camera.h"
#include "entities/Player.h"
#include "entities/Human.h"
#include "terrains/Terrain.h"
#include "guis/GuiRenderer.h"
#include "tools/MousePicker.h"

#include "water/WaterRenderer.h"
#include "water/WaterShader.h"
#include "water/WaterTile.h"
#include "water/WaterFrameBuffer.h"

#include "particles/ParticleMaster.h"
#include "particles/ParticleSystem.h"
#include "particles/Particle.h"

int MainGame::screenWidth = 1024;
int MainGame::screenHeight = 780;
long MainGame::lastFrameTime = 0;
float MainGame::delta = 0;

MainGame::MainGame()
{
	_window = nullptr;
	_gameState = GameState::PLAY;
	MainGame::lastFrameTime = SDL_GetTicks();
}

MainGame::~MainGame()
{
	SDL_Quit();
}

void		MainGame::run()
{
	_initSystems();
	_im->add(_kbm);
	_kbm->add(_mm);
	_gameLoop();
}

void		MainGame::_initSystems()
{
	LOG(INFO, type(this), "Initializing SDL");

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL_Init failed.");

	// Set Opengl version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create window.
	_window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MainGame::screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (_window == nullptr)
		throw std::runtime_error("SDL_CreateWindow failed.");

	LOG(INFO, type(this), "Creating OpenGL context");
	// Initialize context.
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
		throw std::runtime_error("SDL_GL_CreateContext failed.");

	// Initialize glew.
	glewExperimental = GL_TRUE; 
	GLenum res = glewInit();
	if (res != GLEW_OK)
		throw std::runtime_error("glewInit failed.");

	// Print out some info about the graphics drivers.
	LOG(INFO, type(this), std::string("OpenGL version: ") + reinterpret_cast< char const * >(glGetString(GL_VERSION)));
	LOG(INFO, type(this), std::string("GLSL version: ") + reinterpret_cast< char const * >(glGetString(GL_SHADING_LANGUAGE_VERSION)));
	LOG(INFO, type(this), std::string("Vendor: ") + reinterpret_cast< char const * >(glGetString(GL_VENDOR)));
	LOG(INFO, type(this), std::string("Renderer: ") + reinterpret_cast< char const * >(glGetString(GL_RENDERER)));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.38, 0.58, 1, 1);

	LOG(FINE, type(this), "SDL and OpenGL has been correctly initialized");
}

void		print_mat(tinyobj::material_t mat)
{
	std::cout << "ambient = " << mat.ambient[0] << mat.ambient[1] << mat.ambient[2] << std::endl;
	std::cout << "diffuse = " << mat. diffuse[0] << mat.diffuse[1] << mat.diffuse[2] << std::endl;
	std::cout << "specular = " << mat.specular[0] << mat.specular[1] << mat.specular[2] << std::endl;
	std::cout << "shininess = " << mat.shininess << std::endl;
	std::cout << "ambient_texname = " << mat.ambient_texname << std::endl;
	std::cout << "diffuse_texname = " << mat.diffuse_texname << std::endl;
	std::cout << "specular_texname = " << mat.specular_texname << std::endl;
	std::cout << "specular_highlight_texname = " << mat.specular_highlight_texname << std::endl;
	std::cout << "bump_texname = " << mat.bump_texname << std::endl;
	std::cout << "displacement_texname = " << mat.displacement_texname << std::endl;
	std::cout << "alpha_texname = " << mat.alpha_texname << std::endl;
	std::cout << std::endl;
}

void		MainGame::_gameLoop()
{
	srand (static_cast<unsigned>(time(0)));
	Loader 			loader;

	std::vector<Player>	players;
	DataModel playerModel = OBJLoader::loadOBJModel("Resources/models/person/person.obj");
	// DataModel playerModel = OBJLoader::loadOBJModel("Resources/models/human/doorman/doorman.obj");
	// // // print_mat(dataModel.getMaterials()[0]);
	for (size_t i = 0; i < playerModel.getShapes().size(); ++i)
	{
		RawModel model = loader.loadToVAO(playerModel.getShapes()[i].mesh.positions, playerModel.getShapes()[i].mesh.texcoords, playerModel.getShapes()[i].mesh.normals, playerModel.getShapes()[i].mesh.indices);
		ModelTexture texture(loader.loadTexture("Resources/models/person/playerTexture.png"));
		texture.setShineDamper(1);
		texture.setReflectivity(0);
		TexturedModel texturedModel(model, texture);
		players.push_back(Player(texturedModel, glm::vec3(100, 0, -45), glm::vec3(0, 180, 0), 0.6));
		// Player player(texturedModel, glm::vec3(22, 5, -50), glm::vec3(0, 100, 0), 0.6);
	}

	std::vector<Human>	humans;

	DataModel humanModel = OBJLoader::loadOBJModel("Resources/models/human/Girl/girl2.obj");

	for (size_t i = 0; i < humanModel.getShapes().size(); ++i)
	{
		std::cout << humanModel.getMaterials()[i].diffuse_texname << std::endl;
		RawModel humanmodel = loader.loadToVAO(humanModel.getShapes()[i].mesh.positions, humanModel.getShapes()[i].mesh.texcoords, humanModel.getShapes()[i].mesh.normals, humanModel.getShapes()[i].mesh.indices);
		ModelTexture humanTexture(loader.loadTexture("./Resources/models/human/Girl/Texture/" + humanModel.getMaterials()[i].diffuse_texname));
		humanTexture.setShineDamper(10);
		humanTexture.setReflectivity(1);
		TexturedModel humanTexturedModel(humanmodel, humanTexture);
		humans.push_back(Human(humanTexturedModel, glm::vec3(35, 5, -50), glm::vec3(-90, 0, 0), 1, "toto", "manger des chips"));
	}

	// DataModel dataModel = OBJLoader::loadOBJModel("Resources/models/Dragon/Dargon_posing.obj");

	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel dragonmodel = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	for (size_t f = 0; f < dataModel.getShapes()[i].mesh.indices.size() / 3; ++f)
	// 	{
	// 		if (dataModel.getShapes()[i].mesh.material_ids[f] != dataModel.getShapes()[i].mesh.material_ids[f - 1])
	// 		{
	// 			ModelTexture dragonTexture(loader.loadTexture("Resources/models/Dragon/" + dataModel.getMaterials()[dataModel.getShapes()[i].mesh.material_ids[f]].diffuse_texname));
	// 			dragonTexture.setShineDamper(1);
	// 			dragonTexture.setReflectivity(0);
	// 			TexturedModel dragonTexturedModel(dragonmodel, dragonTexture);
	// 			entities.push_back(Entity(dragonTexturedModel, glm::vec3(35, 5, -50), glm::vec3(0, 0, 0), 1));
	// 		}	
	// 	}
	// }


	// 	for (size_t j = 0; j < dataModel.getShapes()[i].mesh.material_ids.size(); ++j)
	// 	{
	// 		if (humanModel.getShapes()[i].mesh.material_ids[j] != humanModel.getShapes()[i].mesh.material_ids[j - 1])
	// 		{
	// 			// std::cout << "old >> " << humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[j - 1]].diffuse_texname << std::endl;
	// 			// std::cout << "new >> " << humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[j]].diffuse_texname << std::endl;
	// 			humanTexture = ModelTexture(loader.loadTexture("Resources/models/human/Girl/Texture/" + humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[j]].diffuse_texname));
	// 			humanTexture.setShineDamper(1);
	// 			humanTexture.setReflectivity(0);
	// 			humanTexturedModel = TexturedModel(humanmodel, humanTexture);
	// 			std::cout << "new >> " << humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[j]].diffuse_texname << std::endl;
	// 			humans.push_back(Human(humanTexturedModel, glm::vec3(35, 5, -50), glm::vec3(-90, 0, 0), 1, "toto", "manger des chips"));
	// 		}	
	// 	}

		// // if (humanModel.getMaterials()[i].diffuse_texname.size())
		// // {
		// // }
		// // else
		// // {
		// 	ModelTexture humanTexture(loader.loadTexture("Resources/white.png"));
		// 	humanTexture.setShineDamper(1);
		// 	humanTexture.setReflectivity(0);
		// 	TexturedModel humanTexturedModel(humanmodel, humanTexture);
		// 	humans.push_back(Human(humanTexturedModel, glm::vec3(35, 5, -50), glm::vec3(-90, 0, 0), 1, "toto", "manger des chips"));
		// // }
	

	Camera camera(&players[0]);

	MasterRenderer	renderer(loader, camera);

	ParticleMaster particleMaster(loader, renderer.getProjectionMatrix());

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	std::vector<Terrain> terrains;
	std::vector<Entity> entities;
	std::vector<Entity> normalMapEntities;
	std::vector<Light> lights;

	TerrainTexture 		backgroundTexture(loader.loadTexture("Resources/terrain/grassy.png"));
	TerrainTexture 		rTexture(loader.loadTexture("Resources/terrain/dirt.png"));
	TerrainTexture 		gTexture(loader.loadTexture("Resources/terrain/pinkFlowers.png"));
	TerrainTexture 		bTexture(loader.loadTexture("Resources/terrain/path.png"));

	TerrainTexturePack	texturePack(backgroundTexture, rTexture, gTexture, bTexture);
	TerrainTexture 		blendMap(loader.loadTexture("Resources/terrain/blendMap2.png"));

	// terrains.push_back(Terrain(0, 0, loader, texturePack, blendMap, "/nfs/2013/g/gmevelec/Downloads/test1.png"));
	// terrains.push_back(Terrain(0, -1, loader, texturePack, blendMap, "/nfs/2013/g/gmevelec/Downloads/test2.png"));
	// terrains.push_back(Terrain(0, 0, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));
	// terrains.push_back(Terrain(0, 1, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));
	terrains.push_back(Terrain(0, -1, loader, texturePack, blendMap, "Resources/terrain/heightmap2.png"));
	// terrains.push_back(Terrain(0, -1, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));

	// terrains.push_back(Terrain(1, 0, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));
	// terrains.push_back(Terrain(1, 1, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));
	// terrains.push_back(Terrain(1, -1, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));

	// terrains.push_back(Terrain(-1, 0, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));
	// terrains.push_back(Terrain(-1, 1, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));
	// terrains.push_back(Terrain(-1, -1, loader, texturePack, blendMap, "Resources/terrain/heightmap.png"));

	// DataModel dataModel = OBJLoader::loadOBJModel("Resources/models/rungholt/rungholt.obj");
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	// std::cout << dataModel.getShapes().size() << std::endl;
	// 	// print_mat(dataModel.getMaterials()[i]);

	// 	RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	ModelTexture texture(loader.loadTexture("Resources/models/rungholt/" + dataModel.getMaterials()[i].diffuse_texname));
	// 	// ModelTexture texture(loader.loadTexture("Resources/white.png"));
	// 	texture.setShineDamper(dataModel.getMaterials()[i].shininess);
	// 	texture.setReflectivity(dataModel.getMaterials()[i].ior);
	// 	TexturedModel texturedModel(model, texture);
	// 	entities.push_back(Entity(texturedModel, glm::vec3(-50, 10, -50), glm::vec3(0, 100, 0), 1));
	// }



	// DataModel dataModel = OBJLoader::loadOBJModel("Resources/models/Dragon/Dargon_posing.obj");

	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel dragonmodel = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	ModelTexture dragonTexture(loader.loadTexture("Resources/models/Dragon/" + dataModel.getMaterials()[dataModel.getShapes()[i].mesh.material_ids[0]].diffuse_texname));
	// 	// ModelTexture humanTexture(loader.loadTexture("Resources/models/human/Girl/Texture/" + humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[0]].diffuse_texname));
	// 	dragonTexture.setShineDamper(1);
	// 	dragonTexture.setReflectivity(0);
	// 	TexturedModel dragonTexturedModel(dragonmodel, dragonTexture);
	// 	entities.push_back(Entity(dragonTexturedModel, glm::vec3(35, 5, -50), glm::vec3(-90, 0, 0), 4));
	// 	for (size_t j = 0; j < dataModel.getShapes()[i].mesh.material_ids.size(); ++j)
	// 	{
	// 		if (dataModel.getShapes()[i].mesh.material_ids[j] != dataModel.getShapes()[i].mesh.material_ids[j - 1])
	// 		{
	// 			// std::cout << "old >> " << humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[j - 1]].diffuse_texname << std::endl;
	// 			// std::cout << "new >> " << humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[j]].diffuse_texname << std::endl;
	// 			dragonTexture = ModelTexture(loader.loadTexture("Resources/models/Dragon/" + dataModel.getMaterials()[dataModel.getShapes()[i].mesh.material_ids[j]].diffuse_texname));
	// 			dragonTexture.setShineDamper(1);
	// 			dragonTexture.setReflectivity(0);
	// 			dragonTexturedModel = TexturedModel(dragonmodel, dragonTexture);
	// 			// std::cout << "new >> " << humanModel.getMaterials()[humanModel.getShapes()[i].mesh.material_ids[j]].diffuse_texname << std::endl;
	// 			entities.push_back(Entity(dragonTexturedModel, glm::vec3(35, 5, -50), glm::vec3(-90, 0, 0), 1));
	// 		}	
	// 	}
	// }


	// DataModel dataModel = OBJLoader::loadOBJModel("Resources/models/Dragon/Dargon_posing.obj");
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// RawModel dragonmodel = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);

		// ModelTexture texture(loader.loadTexture("Resources/models/Dragon/" + dataModel.getMaterials()[i].diffuse_texname));
	// 	texture.setShineDamper(dataModel.getMaterials()[i].shininess);
	// 	texture.setReflectivity(dataModel.getMaterials()[i].ior);
	// 	TexturedModel texturedModel(model, texture);
	// 	entities.push_back(Entity(texturedModel, glm::vec3(0, 0, -25), glm::vec3(0, 0, 0), 5));
	// }
	// DataModel dataModel = OBJLoader::loadOBJModel("Resources/models/Paris/Paris2010_0.obj");
	// // print_mat(dataModel.getMaterials()[50]);
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	// if (dataModel.getMaterials()[i].diffuse_texname.c_str() != NULL)
	// 	std::cout << 	dataModel.getMaterials()[i].diffuse_texname << std::endl;
	// 	ModelTexture texture(loader.loadTexture("Resources/models/Paris/" + dataModel.getMaterials()[i].diffuse_texname));
	// 	// else
	// 	// ModelTexture texture(loader.loadTexture("Resources/white.png"));
	// 	texture.setShineDamper(dataModel.getMaterials()[i].shininess);
	// 	texture.setReflectivity(dataModel.getMaterials()[i].ior);
	// 	TexturedModel texturedModel(model, texture);
	// 	entities.push_back(Entity(texturedModel, glm::vec3(0, -70, 0), glm::vec3(0, 0, 0), 1));
	// }

	DataModel dataModel = OBJLoader::loadOBJModel("Resources/models/tree/pine.obj");

	for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	{
		RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
		ModelTexture texture(loader.loadTexture("Resources/models/tree/pine.png"));
		texture.setShineDamper(10);
		texture.setReflectivity(1);
		TexturedModel texturedModel(model, texture);
		entities.push_back(Entity(texturedModel, glm::vec3(73, 5.48, -33), glm::vec3(0, 0, 0), 1.5));
		entities.push_back(Entity(texturedModel, glm::vec3(94, 2.24, -58), glm::vec3(0, 0, 0), 1.5));
		entities.push_back(Entity(texturedModel, glm::vec3(128, 2.41, -77), glm::vec3(0, 0, 0), 1.5));
		entities.push_back(Entity(texturedModel, glm::vec3(128, 3.16, -89.6), glm::vec3(0, 0, 0), 1.5));
		// for (int j = 0; j < 100; ++j)
		// {
		// 	float x = Maths::randomFloat() * 800 - 400;
		// 	float z = Maths::randomFloat() * -600;
		// 	float y = Terrain::getTerrain(terrains, x, z).getHeightOfTerrain(x, z);
		// 	entities.push_back(Entity(texturedModel, glm::vec3(x, y, z), glm::vec3(0, 0, 0), 1));
		// }
	}

	// dataModel = OBJLoader::loadOBJModel("Resources/models/tree/lowPolyTree.obj");
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	ModelTexture texture(loader.loadTexture("Resources/models/tree/lowPolyTree.png"));
	// 	texture.setShineDamper(10);
	// 	texture.setReflectivity(1);
	// 	TexturedModel texturedModel(model, texture);
	// 	for (int j = 0; j < 500; ++j)
	// 	{
	// 		float x = Maths::randomFloat() * 800 - 400;
	// 		float z = Maths::randomFloat() * -600;
	// 		float y = Terrain::getTerrain(terrains, x, z).getHeightOfTerrain(x, z);
	// 		entities.push_back(Entity(texturedModel, glm::vec3(x, y, z), glm::vec3(0, 0, 0), 0.3));
	// 	}
	// }

	// dataModel = OBJLoader::loadOBJModel("Resources/models/grass/grassModel.obj");
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	ModelTexture texture(loader.loadTexture("Resources/models/grass/grassTexture.png"));
	// 	texture.setShineDamper(10);
	// 	texture.setReflectivity(1);
	// 	texture.setUseFakeLighting(true);
	// 	TexturedModel texturedModel(model, texture);
	// 	for (int j = 0; j < 500; ++j)
	// 	{
	// 		float x = Maths::randomFloat() * 800 - 400;
	// 		float z = Maths::randomFloat() * -600;
	// 		float y = Terrain::getTerrain(terrains, x, z).getHeightOfTerrain(x, z);
	// 		entities.push_back(Entity(texturedModel, glm::vec3(x, y, z), glm::vec3(0, 0, 0), 1));
	// 	}
	// }

	// dataModel = OBJLoader::loadOBJModel("Resources/models/grass/grassModel.obj");
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	ModelTexture texture(loader.loadTexture("Resources/models/flower/flower.png"));
	// 	texture.setShineDamper(10);
	// 	texture.setReflectivity(1);
	// 	texture.setUseFakeLighting(true);
	// 	TexturedModel texturedModel(model, texture);
	// 	for (int j = 0; j < 500; ++j)
	// 	{
	// 		float x = Maths::randomFloat() * 800 - 400;
	// 		float z = Maths::randomFloat() * -600;
	// 		float y = Terrain::getTerrain(terrains, x, z).getHeightOfTerrain(x, z);
	// 		entities.push_back(Entity(texturedModel, glm::vec3(x, y, z), glm::vec3(0, 0, 0), 1));
	// 	}
	// }

	// dataModel = OBJLoader::loadOBJModel("Resources/models/fern/fern.obj");
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	ModelTexture texture(loader.loadTexture("Resources/models/fern/fernatlases.png"));
	// 	texture.setShineDamper(10);
	// 	texture.setReflectivity(1);
	// 	texture.setNumberOfRows(2);
	// 	TexturedModel texturedModel(model, texture);
	// 	for (int j = 0; j < 500; ++j)
	// 	{
	// 		float x = Maths::randomFloat() * 800 - 400;
	// 		float z = Maths::randomFloat() * -600;
	// 		float y = Terrain::getTerrain(terrains, x, z).getHeightOfTerrain(x, z);
	// 		int i = Maths::randomInt(4);
	// 		entities.push_back(Entity(texturedModel, glm::vec3(x, y, z), glm::vec3(0, 0, 0), 0.6, i));
	// 	}
	// }

	lights.push_back(Light(glm::vec3(1000000, 1500000, -100000), glm::vec3(1.3, 1.3, 1.3)));
	// lights.push_back(Light(glm::vec3(185, Terrain::getTerrain(terrains, 185, -293).getHeightOfTerrain(185, -293) + 13, -293), glm::vec3(2, 0, 0), glm::vec3(1, 0.01, 0.002)));
	// lights.push_back(Light(glm::vec3(370, Terrain::getTerrain(terrains, 370, -300).getHeightOfTerrain(370, -300) + 13, -300), glm::vec3(0, 2, 2), glm::vec3(1, 0.01, 0.002)));
	// lights.push_back(Light(glm::vec3(293, Terrain::getTerrain(terrains, 293, -305).getHeightOfTerrain(293, -305) + 13, -305), glm::vec3(2, 2, 0), glm::vec3(1, 0.01, 0.002)));

	// dataModel = OBJLoader::loadOBJModel("Resources/models/lamp/lamp.obj");
	// for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	// {
	// 	RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
	// 	ModelTexture texture(loader.loadTexture("Resources/models/lamp/lamp.png"));
	// 	texture.setUseFakeLighting(true);
	// 	TexturedModel texturedModel(model, texture);
	// 	entities.push_back(Entity(texturedModel, glm::vec3(185, Terrain::getTerrain(terrains, 185, -293).getHeightOfTerrain(185, -293), -293), glm::vec3(0, 0, 0), 1));
	// 	entities.push_back(Entity(texturedModel, glm::vec3(370, Terrain::getTerrain(terrains, 370, -300).getHeightOfTerrain(370, -300), -300), glm::vec3(0, 0, 0), 1));
	// 	entities.push_back(Entity(texturedModel, glm::vec3(293, Terrain::getTerrain(terrains, 293, -305).getHeightOfTerrain(293, -305), -305), glm::vec3(0, 0, 0), 1));
	// }





	// LOG(DEBUG, type(this), "coucou toi");

	dataModel = OBJLoader::loadOBJModel("Resources/models/box/box.obj");
	for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	{
		RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getShapes()[i].mesh.indices);
		ModelTexture texture(loader.loadTexture("Resources/models/box/box.png"));
		texture.setShineDamper(10);
		texture.setReflectivity(1);
		TexturedModel texturedModel(model, texture);
		entities.push_back(Entity(texturedModel, glm::vec3(75, -14, -86), glm::vec3(0, 0, 0), 5));
		// entities.push_back(Entity(texturedModel, glm::vec3(130, Terrain::getTerrain(terrains, 130, -60).getHeightOfTerrain(130, -60), -60), glm::vec3(0, 0, 0), 5));
		// entities.push_back(Entity(texturedModel, glm::vec3(130, Terrain::getTerrain(terrains, 130, -120).getHeightOfTerrain(130, -120), -120), glm::vec3(0, 0, 0), 5));
		// entities.push_back(Entity(texturedModel, glm::vec3(130, Terrain::getTerrain(terrains, 130, -180).getHeightOfTerrain(130, -180), -180), glm::vec3(0, 0, 0), 5));
	}

	dataModel = OBJLoader::loadOBJModel("Resources/models/barrel/barrel.obj");
	for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	{
		dataModel.computeTangentSpace(dataModel.getShapes());
		RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getTangents(), dataModel.getShapes()[i].mesh.indices);
		ModelTexture texture(loader.loadTexture("Resources/models/barrel/barrel.png"));
		texture.setNormalMap(loader.loadTexture("Resources/models/barrel/barrelNormal.png"));
		texture.setShineDamper(10);
		texture.setReflectivity(0.5);
		TexturedModel texturedModel(model, texture);
		normalMapEntities.push_back(Entity(texturedModel, glm::vec3(75, 10, -75), glm::vec3(0, 0, 0), 1));
	}

	dataModel = OBJLoader::loadOBJModel("Resources/models/crate/crate.obj");
	for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	{
		dataModel.computeTangentSpace(dataModel.getShapes());
		RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getTangents(), dataModel.getShapes()[i].mesh.indices);
		ModelTexture texture(loader.loadTexture("Resources/models/crate/crate.png"));
		texture.setNormalMap(loader.loadTexture("Resources/models/crate/crateNormal.png"));
		texture.setShineDamper(10);
		texture.setReflectivity(0.5);
		TexturedModel texturedModel(model, texture);
		normalMapEntities.push_back(Entity(texturedModel, glm::vec3(85, 10, -75), glm::vec3(0, 0, 0), 0.04));
	}

	dataModel = OBJLoader::loadOBJModel("Resources/models/boulder/boulder.obj");
	for (size_t i = 0; i < dataModel.getShapes().size(); ++i)
	{
		dataModel.computeTangentSpace(dataModel.getShapes());
		RawModel model = loader.loadToVAO(dataModel.getShapes()[i].mesh.positions, dataModel.getShapes()[i].mesh.texcoords, dataModel.getShapes()[i].mesh.normals, dataModel.getTangents(), dataModel.getShapes()[i].mesh.indices);
		ModelTexture texture(loader.loadTexture("Resources/models/boulder/boulder.png"));
		texture.setNormalMap(loader.loadTexture("Resources/models/boulder/boulderNormal.png"));
		texture.setShineDamper(10);
		texture.setReflectivity(0.5);
		TexturedModel texturedModel(model, texture);
		normalMapEntities.push_back(Entity(texturedModel, glm::vec3(65, 10, -75), glm::vec3(0, 0, 0), 1));
	}




	std::vector<GuiTexture> guis;
	// GuiTexture gui(loader.loadGuiTexture("Resources/guis/health.png"), glm::vec2(-0.75, 0.9), glm::vec2(0.25, 0.3));
	// guis.push_back(gui);

	GuiTexture shadowMap(renderer.getShadowMapTexture(), glm::vec2(0.5f, 0.5f), glm::vec2(0.5f, 0.5f));
	// guis.push_back(shadowMap);

	GuiRenderer guiRenderer(loader);

	MousePicker picker(camera, renderer.getProjectionMatrix());

	WaterFrameBuffer fbos;

	WaterShader waterShader;
	WaterRenderer waterRenderer(loader, waterShader, renderer.getProjectionMatrix(), fbos);
	std::vector<WaterTile> waters;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			waters.push_back(WaterTile(i * 160, -j * 160, 0));
		}
	}

	ParticleTexture particleFire(loader.loadTextureWithoutFlip("Resources/particleTextures/fire.png"), 8);
	ParticleTexture particleCosmic(loader.loadTextureWithoutFlip("Resources/particleTextures/cosmic.png"), 4);

	ParticleSystem system(particleFire, 10, 2, 0.01f, 4, 10.0f);
	system.setDirection(glm::vec3(0, 1, 0), 0);
	system.setLifeError(0.1f);
	system.setSpeedError(0.25f);
	system.setScaleError(1.0f);
	system.randomizeRotation();

	// ParticleSystem system2(particleCosmic, 40, 5, 0.1f, 1, 1.6f);
	// // system2.setDirection(glm::vec3(0, 1, 0), 0.1f);
	// system2.setLifeError(0.1f);
	// system2.setSpeedError(0.25f);
	// system2.setScaleError(0.5f);


	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	LOG(FINE, type(this), std::string("Finished loading. Spent ") + to_string(duration) + "ms");

	while (_gameState != GameState::EXIT)
	{
		_updateDayLight(&renderer, lights);
		camera.move();
		for (Player& player: players)
		{
			player.move(terrains);
		}

		// for (Human& human: humans)
		// {
		// 	human.move(terrains);
		// }
		picker.update();

		if (MouseManager::mouseStatus.isLeftButtonPressed == 1)
		{
			ParticleSystem proj(particleCosmic, 10, 50, 0.0f, 4, 2.0f);
			proj.setDirection(glm::vec3(picker.getCurrentRay().x, picker.getCurrentRay().y, picker.getCurrentRay().z), 0);
			proj.setLifeError(0.1f);
			proj.setSpeedError(0.25f);
			proj.setScaleError(1.0f);
			proj.generateParticles(glm::vec3(players[0].getPosition().x, players[0].getPosition().y + 5, players[0].getPosition().z));
		}
		particleMaster.update(camera);

		// renderer.renderShadowMap(entities, lights[0]);

		glEnable(GL_CLIP_DISTANCE0);

		for (Entity& entity: normalMapEntities)
		{
			entity.increaseRotation(glm::vec3(0, 1, 0));
		}

		fbos.bindReflectionFrameBuffer();
		float distance = 2 * (camera.getPosition().y - waters[0].getHeight());
		camera.setPosition(glm::vec3(camera.getPosition().x, camera.getPosition().y - distance, camera.getPosition().z));
		camera.invertPitch();
		for (Player player: players)
		{
			renderer.processEntity(player);
			
		}
		for (Human human: humans)
		{
			renderer.processEntity(human);
		}
		renderer.renderScene(entities, normalMapEntities, terrains, lights, camera, glm::vec4(0, 1, 0, -waters[0].getHeight() + 1.0f));
		camera.setPosition(glm::vec3(camera.getPosition().x, camera.getPosition().y + distance, camera.getPosition().z));
		camera.invertPitch();

		fbos.bindRefractionFrameBuffer();
		for (Player player: players)
		{
			renderer.processEntity(player);
			
		}
		for (Human human: humans)
		{
			renderer.processEntity(human);
		}
		renderer.renderScene(entities, normalMapEntities, terrains, lights, camera, glm::vec4(0, -1, 0, waters[0].getHeight()));

		glDisable(GL_CLIP_DISTANCE0);
		fbos.unbindCurrentFrameBuffer();

		for (Player player: players)
		{
			renderer.processEntity(player);
			
		}
		for (Human human: humans)
		{
			renderer.processEntity(human);
		}
		renderer.renderScene(entities, normalMapEntities, terrains, lights, camera, glm::vec4(0, -1, 0, 100000));
		waterRenderer.render(waters, camera, lights[0]);

		particleMaster.renderParticles(camera);

		guiRenderer.render(guis);

		_processInput();
		_updateFrame();
		SDL_GL_SwapWindow(_window);
	}

	particleMaster.cleanUp();
	fbos.cleanUp();
	waterShader.cleanUp();
	guiRenderer.cleanUp();
	renderer.cleanUp();
	loader.cleanUp();
}

void		MainGame::_updateDayLight(MasterRenderer* renderer, std::vector<Light>& lights)
{
	if (renderer->getSkybox().getTime() >= 0 && renderer->getSkybox().getTime() < 5000)
	{
		lights[0].setColour(glm::vec3(0.3f, 0.3f, 0.3f));
		renderer->_RED = 0.01f;
		renderer->_GREEN = 0.01f;
		renderer->_BLUE = 0.01f;
	}
	else if (renderer->getSkybox().getTime() >= 5000 && renderer->getSkybox().getTime() < 8000)
	{
		float time = renderer->getSkybox().getTime() - 5000;
		lights[0].increaseColour(time);
		renderer->_RED = (time * 0.5444) / 3000;
		renderer->_GREEN = (time * 0.62) / 3000;
		renderer->_BLUE = (time * 0.69) / 3000;
	}
	else if (renderer->getSkybox().getTime() >= 8000 && renderer->getSkybox().getTime() < 21000)
	{
		lights[0].setColour(glm::vec3(1, 1, 1));
		renderer->_RED = 0.5444f;
		renderer->_GREEN = 0.62f;
		renderer->_BLUE = 0.69f;
	}
	else
	{
		float time = 3000 - (renderer->getSkybox().getTime() - 21000);
		lights[0].decreaseColour(time);
		renderer->_RED = (time * 0.5444) / 3000;
		renderer->_GREEN = (time * 0.62) / 3000;
		renderer->_BLUE = (time * 0.69) / 3000;
	}
}


void		MainGame::_updateFrame()
{
	long currentFrameTime = SDL_GetTicks();
	delta = (currentFrameTime - MainGame::lastFrameTime) / 1000.0f;
	lastFrameTime = currentFrameTime;
}

void		MainGame::_processInput()
{
	SDL_Event 		sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_QUIT)
		{
			_gameState = GameState::EXIT;
		}
		else
		{
			_im->addEventToQueue(sdlEvent);
			_im->handleEvents();
		}
	}}