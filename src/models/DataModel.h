/*
** This class represents a model just after being loaded.
*/
#pragma once

#include "tinyobjloader/tiny_obj_loader.h"
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class DataModel
{
public:
	DataModel(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials);
	~DataModel();

	std::vector<tinyobj::shape_t>		getShapes() const;
	std::vector<tinyobj::material_t>	getMaterials() const;
	void								computeTangentSpace(std::vector<tinyobj::shape_t> shapes);
	std::vector<GLfloat>				getTangents() const;
	std::vector<GLfloat>				getBinormals() const;
private:
	std::vector<tinyobj::shape_t>		_shapes;
	std::vector<tinyobj::material_t>	_materials;
	std::vector<GLfloat>				_tangents;
	std::vector<GLfloat>				_binormals;
};