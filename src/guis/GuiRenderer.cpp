#include "GuiRenderer.h"
#include <iostream>

GuiRenderer::GuiRenderer(Loader loader):
_quad(loader.loadToVAO(_position, 2))
{
}

GuiRenderer::~GuiRenderer()
{
}

void		GuiRenderer::render(std::vector<GuiTexture> guis)
{
	_shader.start();
	glBindVertexArray(_quad.getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiTexture& gui : guis)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui.getTextureID());
		glm::mat4 matrix = Maths::createTransformationMatrix(gui.getPosition(), gui.getScale());
		_shader.loadTransformationMatrix(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, _quad.getVertexCount());
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	_shader.stop();
}

void 		GuiRenderer::cleanUp()
{
	_shader.cleanUp();
}