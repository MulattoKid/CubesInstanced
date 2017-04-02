#include "Bezier.h"
#include <iostream>
#include <typeinfo>
#include "Window.h"

#define FONT_SIZE 36

void Window::error(std::string message)
{
	std::cout << message << std::endl;
	std::cout << "Press any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}

void Window::createWindow(std::string name, int width, int height)
{
	//Set width and height of window
	_screenWidth = width;
	_screenHeight = height;

	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Set attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_ShowCursor(SDL_DISABLE); //Hide cursor
	//SDL_SetRelativeMouseMode(SDL_TRUE); //Cursor doesn't hit end of screen

	//Create window
	_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	//Error checking
	if (_window == nullptr)
		error("Failed to create SDL window");

	//Fullscreen UNSTABLE - CAREFUL
	//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN); 

	SDL_GLContext context = SDL_GL_CreateContext(_window);
	if (context = nullptr)
		error("Failed to create SDL context");

	//Init glew
	GLenum glError = glewInit();
	//Error checking
	if (glError != GLEW_OK)
		error("Glew was not initialized correctly");

	//Print OpenGL version
	printf("***  OpenGL Version: %s  ***\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_isClosed = false;
	
	init();
}

void Window::initSline()
{
	/*SLINE POSITION*/
	std::vector<glm::vec3>  slinePositionPoints;
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 0.0f, 10.0f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 10.0f, 7.5f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 5.0f, 0.0f));

	slinePositionPoints.emplace_back(glm::vec3(5.0f, 3.75f, -5.0f));
	slinePositionPoints.emplace_back(glm::vec3(10.0f, 2.5f, 0.0f));

	slinePositionPoints.emplace_back(glm::vec3(5.0f, 1.25f, 5.0f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	slinePositionPoints.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	slinePositionPoints.emplace_back(glm::vec3(0.0f, 25.0f, 0.0f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 150.0f, 0.0f));

	slinePositionPoints.emplace_back(glm::vec3(-5.0f, 145.0f, 0.0f));
	slinePositionPoints.emplace_back(glm::vec3(-10.0f, 140.0f, 0.0f));

	slinePositionPoints.emplace_back(glm::vec3(0.0f, 100.0f, 50.0f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 75.0f, 25.0f));

	slinePositionPoints.emplace_back(glm::vec3(0.0f, 35.5f, 12.5f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, -5.0f, 0.0f));

	slinePositionPoints.emplace_back(glm::vec3(0.0f, -2.5f, -5.0f));
	slinePositionPoints.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

	/*SLINE VIEW DIRECTION*/
	std::vector<glm::vec3> slineViewDirectionPoints;
	slineViewDirectionPoints.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));
	slineViewDirectionPoints.emplace_back(glm::vec3(0.5f, 0.0f, -0.5f));
	slineViewDirectionPoints.emplace_back(glm::vec3(0.7f, 0.0f, -0.3f));

	slineViewDirectionPoints.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
	slineViewDirectionPoints.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

	slineViewDirectionPoints.emplace_back(glm::vec3(-0.5f, 0.0f, 0.5f));
	slineViewDirectionPoints.emplace_back(glm::vec3(-1.0f, 0.0f, 0.0f));

	slineViewDirectionPoints.emplace_back(glm::vec3(-0.8f, -0.2f, 0.0f));
	slineViewDirectionPoints.emplace_back(glm::vec3(0.0f, -0.8f, 0.0f));

	slineViewDirectionPoints.emplace_back(glm::vec3(-0.01f, -1.0f, 0.0f));
	slineViewDirectionPoints.emplace_back(glm::vec3(-0.01f, -1.0f, 0.0f));

	slineViewDirectionPoints.emplace_back(glm::vec3(-0.01f, -1.0f, 0.0f));
	slineViewDirectionPoints.emplace_back(glm::vec3(-0.01f, -1.0f, 0.0f));

	slineViewDirectionPoints.emplace_back(glm::vec3(-0.25f, -0.25f, -0.25f));
	slineViewDirectionPoints.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f));

	slineViewDirectionPoints.emplace_back(glm::vec3(-0.25f, -0.25f, -0.75f));
	slineViewDirectionPoints.emplace_back(glm::vec3(0.0f, 0.0f, -1.0f));

	slineViewDirectionPoints.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
	slineViewDirectionPoints.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

	int index = 0;
	while (index < slinePositionPoints.size() - 2)
	{
		for (float t = 0.0f; t < 1.0f; t += 0.002f)
		{
			_slinePosition.emplace_back(bezier(t, slinePositionPoints.at(index), slinePositionPoints.at(index + 1), slinePositionPoints.at(index + 2)));
			_slineViewDirection.emplace_back(bezier(t, slineViewDirectionPoints.at(index), slineViewDirectionPoints.at(index + 1), slineViewDirectionPoints.at(index + 2)));
		}
		index += 2;
	}

	_slineIndex = 0;
}

void Window::init()
{
	_basicShader.init("basic.vert", "basic.frag");
	initSline();

	_bestFrameTime = 100.0f;
	_totalFrameTime = 0.0f;
	_worstFrameTime = 0.0f;
	_numberOfFrameTimeSamples = 0;
	_maxVirtualMemLoad = 0;
	_maxPhysicalMemLoad = 0;

	_perspectiveMatrix = glm::perspective(glm::radians(70.0f), (float)_screenWidth / _screenHeight, 0.1f, 1000.0f);
	_uniformMatrixLoaction = glGetUniformLocation(_basicShader.GetShaderProgram(), "mvp");

	//Buffer data
	GLfloat vertices[] = {
		+0.1f, +0.1f, +0.1f,	+0.0f, +0.9f, +0.9f,  // vertex 0
		-0.1f, +0.1f, +0.1f,	+0.0f, +0.9f, +0.9f,  // vertex 1
		+0.1f, -0.1f, +0.1f,	+0.0f, +0.9f, +0.9f,  // vertex 2
		-0.1f, -0.1f, +0.1f,	+0.0f, +0.9f, +0.9f,  // vertex 3
		
		+0.1f, +0.1f, +0.1f,	+0.1f, +0.1f, +1.0f,  // vertex 0
		+0.1f, -0.1f, +0.1f,	+0.1f, +0.1f, +1.0f,  // vertex 1
		+0.1f, +0.1f, -0.1f,	+0.1f, +0.1f, +1.0f,  // vertex 2
		+0.1f, -0.1f, -0.1f,	+0.1f, +0.1f, +1.0f,  // vertex 3

		+0.1f, +0.1f, +0.1f,	+0.1f, +0.1f, +0.1f,  // vertex 0
		+0.1f, +0.1f, -0.1f,	+0.1f, +0.1f, +0.1f,  // vertex 1
		-0.1f, +0.1f, +0.1f,	+0.1f, +0.1f, +0.1f,  // vertex 2
		-0.1f, +0.1f, -0.1f,	+0.1f, +0.1f, +0.1f,  // vertex 3

		+0.1f, +0.1f, -0.1f,	+1.0f, +0.1f, +0.1f,  // vertex 0
		+0.1f, -0.1f, -0.1f,	+1.0f, +0.1f, +0.1f,  // vertex 1
		-0.1f, +0.1f, -0.1f,	+1.0f, +0.1f, +0.1f,  // vertex 2
		-0.1f, -0.1f, -0.1f,	+1.0f, +0.1f, +0.1f,  // vertex 3

		-0.1f, +0.1f, +0.1f,	+0.1f, +1.0f, +0.1f,  // vertex 0
		-0.1f, +0.1f, -0.1f,	+0.1f, +1.0f, +0.1f,  // vertex 1
		-0.1f, -0.1f, +0.1f,	+0.1f, +1.0f, +0.1f,  // vertex 2
		-0.1f, -0.1f, -0.1f,	+0.1f, +1.0f, +0.1f,  // vertex 3
							  
		+0.1f, -0.1f, +0.1f,	+0.7f, +0.7f, +0.7f,  // vertex 0
		-0.1f, -0.1f, +0.1f,	+0.7f, +0.7f, +0.7f,  // vertex 1
		+0.1f, -0.1f, -0.1f,	+0.7f, +0.7f, +0.7f,  // vertex 2
		-0.1f, -0.1f, -0.1f,	+0.7f, +0.7f, +0.7f   // vertex 3
	};
	unsigned short numberOfVertices = 144;

	unsigned int counter = 0;
	std::vector<GLfloat> offsets;
	const int start = -65 / 2;
	const int end = 65 / 2;
	unsigned int numberOfOffsets = 0;
	_numberOfOffsetsToDraw = 0;

	for (int x = start; x <= end; x++)
	{
		for (int y = start; y <= end; y++)
		{
			for (int z = start; z <= end; z++)
			{
				offsets.emplace_back((float)x * 5.0f);
				offsets.emplace_back((float)y * 5.0f);
				offsets.emplace_back((float)z * 5.0f);
				numberOfOffsets += 3;
				_numberOfOffsetsToDraw++;
				counter++;
			}
		}
	}
	std::cout << counter << std::endl;

	GLushort indices[] = {
		// face 0:
		0,1,2,
		2,1,3,
		// face 1:
		4,5,6,
		6,5,7,
		// face 2:
		8,9,10,
		10,9,11,
		// face 3:
		12,13,14,
		14,13,15,
		// face 4:
		16,17,18,
		18,17,19,
		// face 5:
		20,21,22,
		22,21,23,
	};
	_numberOfIndices = 36;

	//Vertices
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));

	//Offsets
	GLuint offsetBuffer;
	glGenBuffers(1, &offsetBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, offsetBuffer);
	glBufferData(GL_ARRAY_BUFFER, numberOfOffsets * sizeof(GLfloat), &offsets[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
	glVertexAttribDivisor(2, 1);

	//Indices
	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberOfIndices * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);
}

void Window::updateCameraUsingSline()
{
	_camera.setPosition(_slinePosition.at(_slineIndex));
	_camera.setViewDirection(_slineViewDirection.at(_slineIndex));
	if (_slineIndex < _slinePosition.size() - 1)
		_slineIndex++;
	else
		printFrameInformation();
}

void Window::printFrameInformation()
{
	std::cout << "Average frame time: " << _totalFrameTime / _numberOfFrameTimeSamples << std::endl;
	std::cout << "Best frame time: " << _bestFrameTime << std::endl;
	std::cout << "Worst frame time: " << _worstFrameTime << std::endl;
}

void Window::frameTimeCalcuations(std::chrono::steady_clock::time_point startTime)
{
	glFinish();
	//Calculate frame time
	auto endTime = std::chrono::high_resolution_clock::now();
	float frameTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	if (frameTime < _bestFrameTime)
		_bestFrameTime = frameTime;
	else if (frameTime > _worstFrameTime)
		_worstFrameTime = frameTime;
	_totalFrameTime += frameTime;
	_numberOfFrameTimeSamples++;
	//std::cout << "Frame time: " << frameTime << std::endl;
}

void Window::update()
{
	//Update camera position using sline
	updateCameraUsingSline();

	//Calculate world to perspective matrix
	glm::mat4 worldToPerspectiveMatrix = _perspectiveMatrix * _camera.worldToViewMatrix();
	glUniformMatrix4fv(_uniformMatrixLoaction, 1, GL_FALSE, &worldToPerspectiveMatrix[0][0]);

	//Time stamp
	auto startTime = std::chrono::high_resolution_clock::now();

	//Clear background color
	glClearColor(0.0f, 0.1f, 0.15f, 0.0f);
	//Clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw
	_basicShader.bind();
	glBindVertexArray(_vao);
	glDrawElementsInstanced(GL_TRIANGLES, _numberOfIndices, GL_UNSIGNED_SHORT, 0, _numberOfOffsetsToDraw);

	//COMMENT OUT BEFORE DISPLAYING FOR PERFORMANCE GAIN
	frameTimeCalcuations(startTime);

	//Swap frame buffer
	SDL_GL_SwapWindow(_window);
	checkForEvents();
}

void Window::checkForEvents()
{
	//OS event
	SDL_Event e;
	//Look for any OS events - mouse and keyboard
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			//Close program
			case SDL_QUIT:
				printFrameInformation();
				_isClosed = true;
				break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						printFrameInformation();
						_isClosed = true;
						break;

					case SDLK_w:
						_camera.updatePosition(KEY_W);
						break;

					case SDLK_s:
						_camera.updatePosition(KEY_S);
						break;

					case SDLK_a:
						_camera.updatePosition(KEY_A);
						break;

					case SDLK_d:
						_camera.updatePosition(KEY_D);
						break;

					case SDLK_r:
						_camera.updatePosition(KEY_R);
						break;

					case SDLK_f:
						_camera.updatePosition(KEY_F);
						break;

					case SDLK_LCTRL:
						_camera.disableRotation();
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				_camera.updateViewDirection(e, _screenWidth, _screenHeight);
				break;
		}

	}
}

ProcessInfo Window::getProcessInfo()
{
	return ProcessInfo{ _bestFrameTime, _worstFrameTime, _totalFrameTime / _numberOfFrameTimeSamples, _maxVirtualMemLoad, _maxPhysicalMemLoad };
}