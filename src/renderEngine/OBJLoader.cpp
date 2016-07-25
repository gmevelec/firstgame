#include "renderEngine/OBJLoader.h"
#include "tools/Logger.h"

#include <iostream>
#include <stdio.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"

DataModel		OBJLoader::loadOBJModel(const std::string& fileName)
{
	LOG(INFO, "OBJLoader", "Loading OBJ file: " + fileName);

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, fileName.c_str());

	if (!err.empty())
		LOG(WARNING, "OBJLoader", err);
	if (!ret)
		throw std::runtime_error(("Can't load file") + fileName);

	for (size_t i = 0; i < shapes.size(); i++) {
		assert((shapes[i].mesh.indices.size() % 3) == 0);
		assert((shapes[i].mesh.positions.size() % 3) == 0);
	}
	return (DataModel(shapes, materials));
}
