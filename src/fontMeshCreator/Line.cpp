#include "fontMeshCreator/Line.h"

Line::Line(double spaceWidth, double fontSize, double maxLength):
_spaceSize(spaceWidth * fontSize),
_maxLength(maxLength)
{
}

Line::~Line()
{
}

bool				Line::attemptToAddWord(Word word)
{
	double additionalLength = word.getWordWidth();
	additionalLength += !_words.empty() ? _spaceSize : 0;
	if (_currentLineLength + additionalLength < _maxLength)
	{
		_words.push_back(word);
		_currentLineLength += additionalLength;
		return (true)
	}
	return (false);
}

double 				Line::getMaxLength()
{
	return (_maxLength);
}

double				Line::getLineLength()
{
	return (_currentLineLength);
}

std::vector<Word> 	Line::getWords()
{
	return (_words);
}

