#include "SDL.h"
#include "control_component.h"
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
			cout << "Action: crouch" << endl;
		}
	}
}
