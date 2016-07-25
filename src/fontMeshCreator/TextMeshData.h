class TextMeshData
{
public:
	TextMeshData(std::vector<float> vertexPositions, std::vector<float> textureCoords);
	~TextMeshData();

	std::vector<float>		getVertexPositions();
	std::vector<float>		getTextureCoords();
	int						getVertexCount();

private:
	std::vector<float>		_vertexPositions;	
	std::vector<float>		_textureCoords;	
};