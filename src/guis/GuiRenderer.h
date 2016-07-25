/*
** This class is used to render a GUI.
*/
#include "renderEngine/Loader.h"
#include "models/RawModel.h"
#include "guis/GuiTexture.h"
#include "shaders/GuiShader.h"


class GuiRenderer
{
public:
	GuiRenderer(Loader loader);
	~GuiRenderer();

	void	render(std::vector<GuiTexture> guis);
	void	cleanUp();

private:
	std::vector<GLfloat>	_position = { -1, 1, -1, -1, 1, 1, 1, -1};
	RawModel				_quad;
	GuiShader				_shader;
};