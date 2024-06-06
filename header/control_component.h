#pragma once

#include "SDL.h"
#include "game_object.h"
#include "component.h"
#include "component.h"
#include "timer.h"
#include "dependencies.h"

using namespace std;

class ControlComponent : public Component {
	public:
		GameObject *player;
		
		i32 JUMP = 0;
		i32 CROUCH = 0;
		ControlComponent();
		ControlComponent(GameObject* player) : player{player} {};

		// enum laneState { leftLane, middleLane, rightLane };
		// enum moves { jump, crouch, none };

		// laneState currLaneState;
		// moves currMoveState;
		Timer jumpTimer;
		Timer crouchTimer;

		void Update(SDL_Event e);
};
