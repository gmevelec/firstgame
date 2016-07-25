#include "models/TexturedModel.h"
#include <iostream>

TexturedModel::TexturedModel(RawModel model, ModelTexture texture):
_rawModel(model),
_texture(texture)
{
}

TexturedModel::~TexturedModel()
{

}

RawModel 		TexturedModel::getRawModel() const
{
	return (_rawModel);
}

ModelTexture	TexturedModel::getTextureConst() const
{
	return (_texture);
}

ModelTexture&	TexturedModel::getTexture()
{
	return (_texture);
}
