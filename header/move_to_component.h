#pragma once

#include "component.h"
#include <glm/glm.hpp>

class MoveToComponent : public Component {
public:
	
	float speed = 0.05f;		//fixed speed for now
	glm::vec3 target = glm::vec3(0, 0, 0);

	MoveToComponent();
	~MoveToComponent();


	virtual void Update(float elapsedTime) override;
};
