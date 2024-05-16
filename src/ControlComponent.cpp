#include "SDL.h"
#include "Timer.h"
#include "control_component.h"
#include "game_object.h"

#include <iostream>

const f64 TIMER_TIME = 0.6;

ControlComponent::ControlComponent() {
	currLaneState = middleLane;
	moveState     = none;
}

void ControlComponent::Update(float elapsedTime) {
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (!timer.IsStarted()) {
		if (keystate[SDL_SCANCODE_D]) {
			if (currLaneState == middleLane) {
				cout << "Action: move right" << endl;
				currLaneState = rightLane;
				cout << "right lane" << endl;
			}

			if (currLaneState == leftLane) {
				cout << "Action: move right " << endl;
				currLaneState = middleLane;
				cout << "middle lane" << endl;
			}
			timer.Start(TIMER_TIME);
		}

		else if (keystate[SDL_SCANCODE_A]) {
			if (currLaneState == middleLane) {
				cout << "Action: move left" << endl;
				currLaneState = leftLane;
				cout << "left lane" << endl;
			}

			if (currLaneState == rightLane) {
				cout << "Action: move left" << endl;
				currLaneState = middleLane;
				cout << "middle lane" << endl;
			}
			timer.Start(TIMER_TIME);
		}

		else if (keystate[SDL_SCANCODE_SPACE]) {
			moveState = jump;
			cout << "Action: jump" << endl;
			timer.Start(TIMER_TIME);
		}

		else if (keystate[SDL_SCANCODE_LCTRL]) {
			moveState = crouch;
			cout << "Action: crouch" << endl;
			timer.Start(TIMER_TIME);
		}
	}
	timer.Count();
}
