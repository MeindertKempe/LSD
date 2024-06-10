#include "SDL.h"
#include "control_component.h"
#include "game_object.h"
#include "timer.h"

#include <iostream>

const f64 TIMER_TIME = 0.6;

ControlComponent::ControlComponent() {}

void ControlComponent::Update(SDL_Event e) {
	const float MOVE_AMOUNT = 3.7f;
	const float JUMP_AMOUNT = 2.0f;

	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_d) {
			player->position.x = -MOVE_AMOUNT; 

		}

		else if (e.key.keysym.sym == SDLK_a) {
			player->position.x = MOVE_AMOUNT; 
		}

		else if (e.key.keysym.sym == SDLK_s) {
			player->position.x = 0;
		
		}

		else if (e.key.keysym.sym == SDLK_SPACE) {
			if (!jumpTimer.IsStarted() && (!crouchTimer.IsStarted()) &&
			    (player->position.y <= JUMP_AMOUNT)) {
				jumpTimer.Start(0.5);
				player->position.y += JUMP_AMOUNT;
				JUMPPING            = 1;
			}
		}

		else if (e.key.keysym.sym == SDLK_LCTRL) {
			if (!crouchTimer.IsStarted() && (!jumpTimer.IsStarted()) &&
			    (player->position.y == JUMP_AMOUNT / 2)) {
				crouchTimer.Start(0.5);
				player->position.y -= JUMP_AMOUNT / 2;
				CROUCHING           = 1;
			}
		}
	}

	if ((!jumpTimer.IsStarted()) && JUMP && (!crouchTimer.IsStarted())) {
		player->position.y = JUMP_AMOUNT;
		JUMPPING           = 0;
	}

	if ((!crouchTimer.IsStarted()) && CROUCH && (!jumpTimer.IsStarted())) {
		player->position.y = JUMP_AMOUNT / 2;
		CROUCHING          = 0;
	}

	jumpTimer.Count();
	crouchTimer.Count();
}

void ControlComponent::UpdateAction(enum action action) {
	const float MOVE_AMOUNT = 3.7f;
	const float JUMP_AMOUNT = 2.0f;

	switch (action) {
		case ControlComponent::RIGHT: 
			player->position.x = -MOVE_AMOUNT; 
			break;
		case ControlComponent::LEFT: 
			player->position.x = MOVE_AMOUNT; 
			break;
		case ControlComponent::MIDDLE:	
			player->position.x = 0;
			break;

		case ControlComponent::JUMP:
			if (!jumpTimer.IsStarted() && (!crouchTimer.IsStarted()) &&
			    (player->position.y <= JUMP_AMOUNT)) {
				jumpTimer.Start(0.5);
				player->position.y += JUMP_AMOUNT;
				JUMPPING            = 1;
			}
			break;
		case ControlComponent::CROUCH:
			if (!crouchTimer.IsStarted() && (!jumpTimer.IsStarted()) &&
			    (player->position.y == JUMP_AMOUNT / 2)) {
				crouchTimer.Start(0.5);
				player->position.y -= JUMP_AMOUNT / 2;
				CROUCHING           = 1;
			}
			break;
		default: break;
	}

	if ((!jumpTimer.IsStarted()) && JUMP && (!crouchTimer.IsStarted())) {
		player->position.y = JUMP_AMOUNT;
		JUMPPING                = 0;
	}

	if ((!crouchTimer.IsStarted()) && CROUCH && (!jumpTimer.IsStarted())) {
		player->position.y = JUMP_AMOUNT / 2;
		CROUCHING              = 0;
	}

	jumpTimer.Count();
	crouchTimer.Count();
}
