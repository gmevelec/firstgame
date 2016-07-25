/*
** This class represents a Gui texture.
*/
#include <glm/glm.hpp>

class GuiTexture
{
public:
	GuiTexture(int textureID, glm::vec2 position, glm::vec2 scale);
	~GuiTexture();

	int			getTextureID();
	glm::vec2	getPosition();
	glm::vec2	getScale();

private:
	int			_textureID;
	glm::vec2	_position;
	glm::vec2	_scale;
};