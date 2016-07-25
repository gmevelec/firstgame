/*
** This class represents a TexturedModel.
*/

#pragma once

#include "models/RawModel.h"
#include "textures/ModelTexture.h"

class TexturedModel
{
public:

	/*
	** Creates a TexturedModel with a model and a texture.
	**
	** @param model 	The RawModel for represents the model.
	** @param texture 	The ModelTexture to apply on the model.
	*/
	TexturedModel(RawModel model, ModelTexture texture);
	
	virtual ~TexturedModel();

	RawModel 		getRawModel() const;
	ModelTexture	getTextureConst() const;
	ModelTexture&	getTexture();

private:
	RawModel		_rawModel;
	ModelTexture	_texture;
};
