#pragma once

#include "component.h"
#include <glm/glm.hpp>

class MoveToComponent : public Component {
public:
	float speed = 0.05f; // fixed speed for now
	glm::vec3 target;

	MoveToComponent(glm::vec3 *position);
	~MoveToComponent();
	virtual void Update(float elapsedTime) override;
};
