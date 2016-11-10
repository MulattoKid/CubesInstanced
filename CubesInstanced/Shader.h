#pragma once

#include <gl\glew.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	void init(const std::string& vertexShader, const std::string& fragmentShader);
	void bind();
	GLuint& GetShaderProgram() { return _shaderProgram; }
private:
	std::string LoadShader(const std::string& filename);
	GLuint CreateShader(const std::string& text, GLenum type, const std::string& filename);

	GLuint _shaderProgram;
	GLuint _vertexShader;
	GLuint _fragmentShader;
};

