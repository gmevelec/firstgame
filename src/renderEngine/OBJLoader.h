/*
** This class is used to load obj models.
** It uses the tinyobjloader from syoyo: https://github.com/syoyo/tinyobjloader
*/

#pragma once

#include "renderEngine/Loader.h"
#include "models/DataModel.h"

#include <vector>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	/*
	** This function load a obj file and return a RawModel.
	**
	** @param fileName	The obj file to load.
	** @param loader 	An instance of loader class for the function loadToVAO().
	**
	** @return	A RawModel created from the objfile.
	*/
	// static RawModel		loadOBJModel(const std::string& fileName, Loader loader);	
	static DataModel	loadOBJModel(const std::string& fileName);	
};