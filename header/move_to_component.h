#pragma once

#include <glm/glm.hpp>

class MoveToComponent {
public:
	float speed = 0.05f;		//fixed speed for now
	glm::vec3 target;

	MoveToComponent();

	virtual void update(float elapsedTime);
};
