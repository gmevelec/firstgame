/*
** This class contains tools of mathematics
*/

#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entities/Camera.h"

class Maths
{
public:
	Maths();
	virtual ~Maths();
	
	/*
	** This function creates a transformation matrix who allows to move, rotate and scale an entity.
	**
	** @param translation 	A vector for translate the entity.
	** @param rx			A float for rotate the entity.
	** @param ry			A float for rotate the entity.
	** @param rz			A float for rotate the entity.
	** @param scale			A float for scale the entity.
	**
	** @return	A matrix 4x4 for all transformations.
	*/
	static glm::mat4	createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);


	static glm::mat4	createTransformationMatrix(glm::vec2 translation, glm::vec2 scale);

	/*
	** This function creates a view matrix who allows to move the camera.
	**
	** @return	A matrix 4x4 for the camera.
	*/
	static glm::mat4	createViewMatrix(Camera camera);

	/*
	** @return	A random float between 0 and 1.
	*/
	static float		randomFloat();
	static int			randomInt(int max, int min = 0);

	static float 		barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
};