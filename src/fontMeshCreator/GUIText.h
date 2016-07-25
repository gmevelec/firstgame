/*
** Represents a piece of text in the game.
** 
** @author Karl
**
*/

#include <glm/glm.hpp>
#include "fontMeshCreator/FontType.h"

class GUIText
{
public:
	/*
	** Creates a new text, loads the text's quads into a VAO, and adds the text
	** to the screen.
	** 
	** @param text 			the text.
	** @param fontSize 		the font size of the text, where a font size of 1 is the default size.
	** @param font 			the font that this text should use.
	** @param position 		the position on the screen where the top left corner of the
	**						text should be rendered. The top left corner of the screen is
	**						(0, 0) and the bottom right is (1, 1).
	** @param maxLineLength	basically the width of the virtual page in terms of screen
	**           			width (1 is full screen width, 0.5 is half the width of the
	**            			screen, etc.) Text cannot go off the edge of the page, so if
	**           			the text is longer than this length it will go onto the next
	**            			line. When text is centered it is centered into the middle of
	**            			the line, based on this line length value.
	** @param centered 		whether the text should be centered or not.
	*/
	GUIText(std::string text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered);
	~GUIText();

	void		remove();
	FontType	getFont();
	void		setColour(float r, float g, float b);
	glm::vec3	getColour();
	int 		getNumberOfLines();
	glm::vec2	getPosition();
	int 		getMesh();
	void		setMeshInfo(int vao, int verticesCount);
	int 		getVertexCount();
	float		getFontSize();
	void		setNumberOfLines(int number);
	bool		isCentered();
	float		getMaxLineSize();
	std::string getTextString();

private:
	std::string 	_textString;
	float			_fontSize;
	int				_textMeshVao;
	int				_vertexCount;
	glm::vec3		_colour = glm::vec3(0, 0, 0);
	glm::vec2		_position;
	float			_lineMaxSize;
	int				_numberOfLines;
	FontType		_font;
	bool			_centerText = false;
};