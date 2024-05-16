#pragma once

#include "component.h"
#include "Timer.h"
#include "dependencies.h"

using namespace std;

class ControlComponent : public Component {
public:
	enum laneState { leftLane, middleLane, rightLane };
	enum moveState { jump, crouch, none };

	laneState currLaneState;
	moveState moveState;

	Timer timer;

	ControlComponent();

	virtual void Update(float elapsedTime) override;
};
