#pragma once

#include "component.h"
#include "glm/vec3.hpp"

class BoundingBoxComponent : public Component {
public:
	glm::vec3 origin, size;
	BoundingBoxComponent(GameObject *gameObject, glm::vec3 origin, glm::vec3 size)
	    : origin{ origin }, size{ size } {
		this->gameObject = gameObject;
	};
	bool collide(BoundingBoxComponent &other);
};
