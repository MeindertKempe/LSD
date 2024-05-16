#pragma once

#include "component.h"
#include "Timer.h"
#include "dependencies.h"

using namespace std;

class ControlComponent : public Component {
public:
	enum laneState { leftLane, middleLane, rightLane };
	enum moves { jump, crouch, none };

	laneState currLaneState;
	moves currMoveState;

	Timer timer;

	ControlComponent();

	virtual void Update(float elapsedTime) override;
};
