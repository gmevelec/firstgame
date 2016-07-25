#include "models/DataModel.h"

DataModel::DataModel(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials):
_shapes(shapes),
_materials(materials)
{
}

DataModel::~DataModel()
{
}

std::vector<tinyobj::shape_t>		DataModel::getShapes() const
{
	return (_shapes);
}
std::vector<tinyobj::material_t>	DataModel::getMaterials() const
{
	return (_materials);
}

std::vector<GLfloat>				DataModel::getTangents() const
{
	return (_tangents);
}

std::vector<GLfloat>				DataModel::getBinormals() const
{
	return (_binormals);
}

void 			DataModel::computeTangentSpace(std::vector<tinyobj::shape_t> shapes) {

 for(unsigned s = 0; s < shapes.size(); s++) {
	  
	  shapes[s].mesh.normals.resize(shapes[s].mesh.positions.size());
	  _tangents.resize(shapes[s].mesh.positions.size());
	  _binormals.resize(shapes[s].mesh.positions.size());
	  shapes[s].mesh.texcoords.resize(shapes[s].mesh.positions.size() / 3 * 2);

	  for(unsigned i = 0; i < shapes[s].mesh.indices.size() / 3; i++) {
		glm::vec3 v1 = glm::vec3(
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3] * 3],
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3] * 3 + 1],
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3] * 3 + 2]);
		glm::vec3 v2 = glm::vec3(
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3 + 1] * 3],
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3 + 1] * 3 + 1],
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3 + 1] * 3 + 2]);
		glm::vec3 v3 = glm::vec3(
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3 + 2] * 3],
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3 + 2] * 3 + 1],
			shapes[s].mesh.positions[shapes[s].mesh.indices[i * 3 + 2] * 3 + 2]);

		glm::vec2 uv1 = glm::vec2(
			shapes[s].mesh.texcoords[shapes[s].mesh.indices[i * 3] * 2],
			shapes[s].mesh.texcoords[shapes[s].mesh.indices[i * 3] * 2 + 1]);
		
		glm::vec2 uv2 = glm::vec2(
			shapes[s].mesh.texcoords[shapes[s].mesh.indices[i * 3 + 1] * 2],
			shapes[s].mesh.texcoords[shapes[s].mesh.indices[i * 3 + 1] * 2 + 1]);
		glm::vec2 uv3 = glm::vec2(
			shapes[s].mesh.texcoords[shapes[s].mesh.indices[i * 3 + 2] * 2],
			shapes[s].mesh.texcoords[shapes[s].mesh.indices[i * 3 + 2] * 2 + 1]);


		glm::vec3 d1 = v2 - v1;
		glm::vec3 d2 = v3 - v1;

		glm::vec2 dUV1 = uv2 - uv1;
		glm::vec2 dUV2 = uv3 - uv1;

		float coef = 1.f / (dUV1.x * dUV2.y - dUV2.x * dUV1.y);

		glm::vec3 tangent = (d1 * dUV2.y - d2 * dUV1.y) * coef;
		glm::vec3 binormal = (d2 * dUV1.x - d1 * dUV2.x) * coef;

		glm::vec3 normal = glm::cross(d1, d2);
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3] * 3] += normal.x;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3] * 3 + 1] += normal.y;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3] * 3 + 2] += normal.z;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3 + 1] * 3] += normal.x;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3 + 1] * 3 + 1] += normal.y;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3 + 1] * 3 + 2] += normal.z;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3 + 2] * 3] += normal.x;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3 + 2] * 3 + 1] += normal.y;
		shapes[s].mesh.normals[shapes[s].mesh.indices[i * 3 + 2] * 3 + 2] += normal.z;
		
		_tangents[shapes[s].mesh.indices[i * 3] * 3] += tangent.x;
		_tangents[shapes[s].mesh.indices[i * 3] * 3 + 1] += tangent.y;
		_tangents[shapes[s].mesh.indices[i * 3] * 3 + 2] += tangent.z;
		_tangents[shapes[s].mesh.indices[i * 3 + 1] * 3] += tangent.x;
		_tangents[shapes[s].mesh.indices[i * 3 + 1] * 3 + 1] += tangent.y;
		_tangents[shapes[s].mesh.indices[i * 3 + 1] * 3 + 2] += tangent.z;
		_tangents[shapes[s].mesh.indices[i * 3 + 2] * 3] += tangent.x;
		_tangents[shapes[s].mesh.indices[i * 3 + 2] * 3 + 1] += tangent.y;
		_tangents[shapes[s].mesh.indices[i * 3 + 2] * 3 + 2] += tangent.z;

		_binormals[shapes[s].mesh.indices[i * 3] * 3] += binormal.x;
		_binormals[shapes[s].mesh.indices[i * 3] * 3 + 1] += binormal.y;
		_binormals[shapes[s].mesh.indices[i * 3] * 3 + 2] += binormal.z;
		_binormals[shapes[s].mesh.indices[i * 3 + 1] * 3] += binormal.x;
		_binormals[shapes[s].mesh.indices[i * 3 + 1] * 3 + 1] += binormal.y;
		_binormals[shapes[s].mesh.indices[i * 3 + 1] * 3 + 2] += binormal.z;
		_binormals[shapes[s].mesh.indices[i * 3 + 2] * 3] += binormal.x;
		_binormals[shapes[s].mesh.indices[i * 3 + 2] * 3 + 1] += binormal.y;
		_binormals[shapes[s].mesh.indices[i * 3 + 2] * 3 + 2] += binormal.z;
		
	}
	for(unsigned v = 0; v < shapes[s].mesh.positions.size() / 3; v++) {
		glm::vec3 n = glm::normalize(glm::vec3(
			shapes[s].mesh.normals[v * 3],
			shapes[s].mesh.normals[v * 3 + 1],
			shapes[s].mesh.normals[v * 3 + 2]));
		shapes[s].mesh.normals[v * 3] += n.x;
		shapes[s].mesh.normals[v * 3 + 1] += n.y;
		shapes[s].mesh.normals[v * 3 + 2] += n.z;

		glm::vec3 t = glm::normalize(glm::vec3(
			_tangents[v * 3],
			_tangents[v * 3 + 1],
			_tangents[v * 3 + 2]));
		_tangents[v * 3] += t.x;
		_tangents[v * 3 + 1] += t.y;
		_tangents[v * 3 + 2] += t.z;

		glm::vec3 b = glm::normalize(glm::vec3(
			_binormals[v * 3],
			_binormals[v * 3 + 1],
			_binormals[v * 3 + 2]));
		_binormals[v * 3] += b.x;
		_binormals[v * 3 + 1] += b.y;
		_binormals[v * 3 + 2] += b.z;
	 }

	}
}