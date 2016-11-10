#pragma once

#include <glm\glm.hpp>

glm::vec3 bezier(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2)
{
	glm::vec3 toReturn;

	toReturn.x = (powf(1 - t, 2.0f) * p0.x) + (2 * t * (1 - t) * p1.x) + (powf(t, 2.0f) * p2.x);
	toReturn.y = (powf(1 - t, 2.0f) * p0.y) + (2 * t * (1 - t) * p1.y) + (powf(t, 2.0f) * p2.y);
	toReturn.z = (powf(1 - t, 2.0f) * p0.z) + (2 * t * (1 - t) * p1.z) + (powf(t, 2.0f) * p2.z);

	return toReturn;
}