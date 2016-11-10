#include "Camera.h"
#include <iostream>

Camera::Camera() : _position(0.0f, 0.0f, 2.0f), _viewDirection(0.0f, 0.0f, -1.0f), _upVector(0.0f, 1.0f, 0.0f), _movementSpeed(0.25f), _rotate(false)
{}

Camera::Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 upVector, float movementSpeed)
{
	_position = position;
	_viewDirection = viewDirection;
	_upVector = upVector;
	_movementSpeed = movementSpeed;
	_rotate = false;
}

Camera::~Camera()
{}

void Camera::disableRotation()
{
	_rotate = !_rotate;
}

void Camera::updatePosition(KeyToken key)
{
	switch (key)
	{
		case KEY_W:
			_position += _movementSpeed * _viewDirection;
			break;
		
		case KEY_S:
			_position += -_movementSpeed * _viewDirection;
			break;

		case KEY_A:
			_position += -_movementSpeed * glm::cross(_viewDirection, _upVector);
			break;

		case KEY_D:
			_position += _movementSpeed * glm::cross(_viewDirection, _upVector);
			break;

		case KEY_R:
			_position += _movementSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
			break;

		case KEY_F:
			_position += -_movementSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
			break;
	}
}

void Camera::updateViewDirection(SDL_Event e, int screenWidth, int screenHeight)
{
	if (_rotate)
	{
		glm::mat4 rotator = glm::rotate(glm::radians(e.motion.xrel * _movementSpeed), glm::vec3(0.0f, -1.0f, 0.0f)) * //X rotation
			glm::rotate(glm::radians(e.motion.yrel * _movementSpeed), glm::vec3(-1.0f, 0.0f, 0.0f)); //Y rotation

		_viewDirection = glm::mat3(rotator) * _viewDirection;
	}
}

void Camera::setPosition(glm::vec3 newPos)
{
	_position = newPos;
}

void Camera::setViewDirection(glm::vec3 newViewDir)
{
	_viewDirection = newViewDir;
}

glm::mat4 Camera::worldToViewMatrix()
{
	return glm::lookAt(_position, _position + _viewDirection, _upVector);
}