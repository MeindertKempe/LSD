#pragma once

#include "component.h"
#include "glm/glm.hpp"

class DrawComponent : public Component {
public:
	DrawComponent();
	~DrawComponent();
	virtual void Draw(glm::mat4 projectionView, glm::mat4 transform) = 0;
};
