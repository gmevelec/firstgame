/*
** Represents a font. It holds the font's texture atlas as well as having the
** ability to create the quad vertices for any text using this font.
** 
** @author Karl
*/

class FontType
{
public:

	/*
	** Creates a new font and loads up the data about each character from the
	** font file.
	** 
	** @param textureAtlas 	the ID of the font atlas texture.
	** @param fontFile		the font file containing information about each character in the texture atlas.
	*/
	FontType(int textureAtlas, File fontFile);
	~FontType();

	int				getTextureAtlas();
	TextMeshData	loadText(GUIText test);

private:
	int 				_textureAtlas;
	TextMeshCreator		_loader;	
};