#pragma once

#include "component.h"

class SpinComponent : public Component {
	float speed;

public:
	SpinComponent(float speed);
	~SpinComponent();

	virtual void Update(float elapsedTime) override;
};
