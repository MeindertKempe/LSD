#pragma once

#include "component.h"

class SpinComponent : public Component
{
	f32 speed;
public:
	SpinComponent(f32 speed);
	~SpinComponent();

	virtual void Update(f32 elapsedTime) override;
};

