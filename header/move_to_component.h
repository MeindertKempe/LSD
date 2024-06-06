#pragma once

#include "component.h"
#include <glm/glm.hpp>

class MoveToComponent : public Component {
public:
	
	f32 speed = 0.05f;		//fixed speed for now
	glm::vec3 target;

	MoveToComponent(glm::vec3* position);
	~MoveToComponent();


	virtual void Update(f32 elapsedTime) override;
};
