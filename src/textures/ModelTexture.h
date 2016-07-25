/*
** This class represent a ModelTexture. 
*/

#pragma once

#include <GL/glew.h>

class ModelTexture
{
public:

	/*
	** Creates a ModelTexure with a textureID.
	*/
	ModelTexture(GLuint id);
	virtual ~ModelTexture();

	GLuint	getTextureID() const;
	GLuint	getNormalMap() const;
	float	getShineDamper() const;
	float	getReflectivity() const;
	bool	getTransparancy() const;
	bool	getUseFakeLighting() const;
	int		getNumberOfRows() const;
	
	void	setShineDamper(float shineDamper);
	void	setReflectivity(float reflectivity);
	void	setTransparancy(bool value);
	void	setUseFakeLighting(bool value);
	void	setNumberOfRows(int numberOfRows);
	void	setNormalMap(GLuint normalMap);


private:
	GLuint	_textureID;
	GLuint	_normalMap;
	float	_shineDamper;
	float	_reflectivity;
	bool	_transparancy = false;
	bool	_useFakeLighting = false;
	int		_numberOfRows = 1;

};