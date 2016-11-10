#pragma once

#include "Camera.h"
#include <chrono>
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <sdl\SDL.h>
#include "Shader.h"
#include <string>
#include <vector>
#include <Windows.h>

struct ProcessInfo
{
	float bestFrameTime;
	float worstFrameTime;
	float averageFrameTime;
	SIZE_T maxVirtualMemUsed;
	SIZE_T maxPhysicalMemUsed;
};

class Window
{
public:
	bool isClosed() { return _isClosed; }
	ProcessInfo getProcessInfo();
	int getScreenWidth() { return _screenWidth; }
	int getScreenHeight() { return _screenHeight; }
	SIZE_T* getMaxVirutalMem() { return &_maxVirtualMemLoad; }
	SIZE_T* getMaxPhysicalMem() { return &_maxPhysicalMemLoad; }
	void checkForEvents();
	void createWindow(std::string name, int width, int height);
	void error(std::string message);
	void init();
	void setShaderProgram(GLuint& shaderProgram) { _shaderProgram = shaderProgram; }
	void update();
private:
	void initSline();
	inline void updateCameraUsingSline();
	void printFrameInformation();
	inline void frameTimeCalcuations(std::chrono::steady_clock::time_point startTime);
	bool _isClosed;
	float _bestFrameTime;
	float _totalFrameTime;
	float _worstFrameTime;
	unsigned int _numberOfFrameTimeSamples;
	unsigned int _numberOfIndices;
	unsigned int _numberOfOffsetsToDraw;
	unsigned int _screenWidth;
	unsigned int _screenHeight;
	unsigned int _slineIndex;
	Camera _camera;
	glm::mat4 _perspectiveMatrix;
	std::vector<glm::vec3> _slinePosition;
	std::vector<glm::vec3> _slineViewDirection;
	GLuint _vao;
	GLuint _uniformMatrixLoaction;
	GLuint _shaderProgram;
	SDL_Window* _window;
	Shader _basicShader;
	Shader _textShader;
	SIZE_T _maxVirtualMemLoad;
	SIZE_T _maxPhysicalMemLoad;
};

