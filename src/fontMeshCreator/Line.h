class Line
{
public:
	Line(double spaceWidth, double fontSize, double maxLength);
	~Line();

	bool				attemptToAddWord(Word word);
	double 				getMaxLength();
	double				getLineLength();
	std::vector<Word> 	getWords();
	
private:
	double				_maxLength;
	double				_spaceSize;
	std::vector<Word>	words;
	double				_currentLineLength = 0;
};