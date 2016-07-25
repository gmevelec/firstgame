#include "tools/Maths.h"

glm::mat4	Maths::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, translation);
	matrix = glm::rotate(matrix, (float) glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, (float) glm::radians(rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, (float) glm::radians(rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
	return (matrix);
}

glm::mat4	Maths::createTransformationMatrix(glm::vec2 translation, glm::vec2 scale)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(translation.x, translation.y, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 1.0f));
	return (matrix);
}


glm::mat4	Maths::createViewMatrix(Camera camera)
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::rotate(matrix, (float)glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, (float)glm::radians(camera.getYaw()), glm::vec3(0, 1, 0));
	glm::vec3 cameraPos = camera.getPosition();
	glm::vec3 negativeCameraPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
	matrix = glm::translate(matrix, negativeCameraPos);
	return (matrix);
}

float		Maths::randomFloat()
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

float 		Maths::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return (l1 * p1.y + l2 * p2.y + l3 * p3.y);
}

int			Maths::randomInt(int max, int min)
{
	return (rand() % max + min);
}