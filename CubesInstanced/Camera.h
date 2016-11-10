#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <sdl\SDL.h>

enum KeyToken
{
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_R,
	KEY_F
};

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 upVector, float movementSpeed);
	~Camera();
	void updatePosition(KeyToken key);
	void updateViewDirection(SDL_Event e, int screenWidth, int screenHeight);
	void setPosition(glm::vec3 newPos); //Set new camera position explicitly
	void setViewDirection(glm::vec3 newViewDir); //Set view direction explicitly
	void disableRotation();
	glm::mat4 worldToViewMatrix();
private:
	bool _rotate;
	glm::vec3 _position;
	glm::vec3 _viewDirection;
	glm::vec3 _upVector;
	float _movementSpeed;
};

