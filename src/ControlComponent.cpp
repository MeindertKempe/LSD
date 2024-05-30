#include "SDL.h"
#include "control_component.h"
#include <iostream>

void ControlComponent::CheckKeyPress(SDL_Event e) {
	const float MOVE_AMOUNT = 3.5f;
	const float MOVE_SPEED = 0.1f;

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
			player->position = glm::vec3(0.0, 2.0, 0.0);

			cout << "Action: jump" << endl;
		} 
		
		else if (e.key.keysym.sym == SDLK_LCTRL) {
			player->position = glm::vec3(0.0, 1.0, 0.0);
			cout << "Action: crouch" << endl;
		}
	}
}
