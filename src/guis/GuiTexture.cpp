#include "guis/GuiTexture.h"

GuiTexture::GuiTexture(int textureID, glm::vec2 position, glm::vec2 scale):
_textureID(textureID),
_position(position),
_scale(scale)
{

}

GuiTexture::~GuiTexture()
{
}

int			GuiTexture::getTextureID()
{
	return (_textureID);
}

glm::vec2	GuiTexture::getPosition()
{
	return (_position);
}

glm::vec2	GuiTexture::getScale()
{
	return (_scale);
}
