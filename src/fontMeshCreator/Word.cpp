#include "fontMeshCreator/Word.h"

Word::Word(double fontSize):
_fontSize(fontSize)
{
}

Word::~Word()
{
}

void					Word::addCharacter(Character char)
{
	_charaters.push_back(char);
	_width += char.getxAdvance() * fontSize;
}

std::vector<Character> 	Word::getCharacters()
{
	return (_charaters);
}

double					Word::getWordWidth()
{
	return (_width);
}

