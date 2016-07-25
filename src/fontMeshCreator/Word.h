class Word
{
public:
	Word(double fontSize);
	~Word();

	void					addCharacter(Character char);
	std::vector<Character> 	getCharacters();
	double					getWordWidth();
	
private:

	std::vector<Character> 	_characters;
	double					_width = 0;
	double					_fontSize;
};