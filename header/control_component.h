#pragma once

#include "SDL.h"
#include "game_object.h"
#include "component.h"
#include "component.h"
#include "Timer.h"
#include "dependencies.h"

using namespace std;

class ControlComponent : public Component {
	public:
		GameObject *player;
		ControlComponent() {};
		ControlComponent(GameObject* player) : player{player} {};
		void CheckKeyPress(SDL_Event e);

		enum laneState { leftLane, middleLane, rightLane };
		enum moves { jump, crouch, none };

		laneState currLaneState;
		moves currMoveState;
		Timer timer;
		ControlComponent();
		virtual void Update(float elapsedTime) override;
};
