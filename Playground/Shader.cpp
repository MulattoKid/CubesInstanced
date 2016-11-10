#include <fstream>
#include <iostream>
#include "Shader.h"



Shader::Shader() : _shaderProgram(0), _vertexShader(0), _fragmentShader(0)
{}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(_shaderProgram);
}

std::string Shader::LoadShader(const std::string& filename)
{
	std::ifstream file;
	file.open((filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}

	return output;
}

GLuint Shader::CreateShader(const std::string& text, GLenum type, const std::string& filename)
{
	GLuint shader = glCreateShader(type);

	//Char* to hold text from shader file - i.e vertexShader and fragmentShader
	const char* shaderText[1];
	shaderText[0] = text.c_str();

	//Define shader source
	glShaderSource(shader, 1, shaderText, 0);

	//Compile shader
	glCompileShader(shader);

	//Check for compile errors
	GLint compileResult;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize; //Size of buffer that glGetShaderLog returns
		glGetShaderInfoLog(shader, infoLogLength, &bufferSize, buffer);
		std::cout << "In shader " << filename << ":  " << buffer << std::endl;

		delete buffer;
	}

	return shader;
}

void Shader::init(const std::string& vertexShader, const std::string& fragmentShader)
{
	//Create shader program and its shaders
	_shaderProgram = glCreateProgram();
	_vertexShader = CreateShader(LoadShader(vertexShader), GL_VERTEX_SHADER, vertexShader);
	_fragmentShader = CreateShader(LoadShader(fragmentShader), GL_FRAGMENT_SHADER, fragmentShader);

	//Attach shaders to shader program
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);

	//Link shader program
	glLinkProgram(_shaderProgram);

	//Check for linking errors
	GLint linkResult;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linkResult);
	if (linkResult != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLint bufferSize; //Size of buffer that glGetProgramLog returns
		glGetProgramInfoLog(_shaderProgram, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
	}

	//Validate program
	glValidateProgram(_shaderProgram);

	//Clean up shaders
	glDetachShader(_shaderProgram, _vertexShader);
	glDetachShader(_shaderProgram, _fragmentShader);
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
}

void Shader::bind()
{
	glUseProgram(_shaderProgram);
}