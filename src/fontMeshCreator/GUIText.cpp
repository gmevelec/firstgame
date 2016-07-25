#include "fontMeshCreator/GUIText.h"

GUIText::GUIText(std::string text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered):
_textString(text),
_fontSize(fontSize),
_font(font),
_position(position),
_lineMaxSize(maxLineLength),
_centerText(centered)
{
}

GUIText::~GUIText()
{
}

void		GUIText::remove()
{
}

FontType	GUIText::getFont()
{
	return (_font);
}

void		GUIText::setColour(float r, float g, float b)
{
	_colour = glm::vec3(r, g, b);
}

glm::vec3	GUIText::getColour()
{
	return (_colour);
}

int 		GUIText::getNumberOfLines()
{
	return (_numberOfLines);
}

glm::vec2	GUIText::getPosition()
{
	return (_position);
}

int 		GUIText::getMesh()
{
	return (_textMeshVao);
}

void		GUIText::setMeshInfo(int vao, int verticesCount)
{
	_textMeshVao = vao;
	_vertexCount - verticesCount;
}

int 		GUIText::getVertexCount()
{
	return (_vertexCount);
}

float		GUIText::getFontSize()
{
	return (_fontSize);
}

void		GUIText::setNumberOfLines(int number)
{
	_numberOfLines = number;
}

bool		GUIText::isCentered()
{
	return (_centerText);
}

float		GUIText::getMaxLineSize()
{
	return (_lineMaxSize);
}

std::string GUIText::getTextString()
{
	return (_textString);
}


