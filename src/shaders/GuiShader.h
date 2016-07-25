#include "shaders/AShaderProgram.h"

class GuiShader : public ShaderProgram
{
public:
	GuiShader();
	~GuiShader();

	void	loadTransformationMatrix(glm::mat4 matrix);
	
protected:
	void	bindAttributes();
	void	getAllUniformLocations();


private:
	GLint	_locationTransformationMatrix;
	
};