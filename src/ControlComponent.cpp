#include "SDL.h"
#include "Timer.h"
#include "control_component.h"
#include "game_object.h"

#include <iostream>

void ControlComponent::CheckKeyPress(SDL_Event e) {
	const float MOVE_AMOUNT = 3.5f;
	const float JUMP_AMOUNT = 2.0f;

	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_d) { 
			if(player->position.x != -MOVE_AMOUNT){
				player->position.x -= MOVE_AMOUNT;
			}
			cout << "Action: move right" << endl; 
		}
		
		else if (e.key.keysym.sym == SDLK_a) { 
			if(player->position.x != MOVE_AMOUNT){
				player->position.x += MOVE_AMOUNT;
			}
			cout << "Action: move left" << endl; 
		} 
		
		else if (e.key.keysym.sym == SDLK_SPACE) {
			if(player->position.y != JUMP_AMOUNT){
				player->position.y += 1.0;
			}
			cout << "Action: jump" << endl;
		} 
		
		else if (e.key.keysym.sym == SDLK_LCTRL) {
			if(player->position.y != JUMP_AMOUNT / 2){
				player->position.y -= 1.0;
			}
		}
	}
}
			
const f64 TIMER_TIME = 0.6;

ControlComponent::ControlComponent() {
	currLaneState = middleLane;
	currMoveState     = none;
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
			currMoveState = jump;
			cout << "Action: jump" << endl;
			timer.Start(TIMER_TIME);
		}

		else if (keystate[SDL_SCANCODE_LCTRL]) {
			currMoveState = crouch;
			cout << "Action: crouch" << endl;
			timer.Start(TIMER_TIME);
		}
	}
	timer.Count();
}
