#include "SDL.h"
#include "control_component.h"
#include <iostream>

ControlComponent::ControlComponent() {}

void ControlComponent::CheckKeyPress(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_d) { cout << "Action: move right" << endl; }
		
		else if (e.key.keysym.sym == SDLK_a) { 
			cout << "Action: move left" << endl; 
		} 
		
		else if (e.key.keysym.sym == SDLK_SPACE) {
			cout << "Action: jump" << endl;
		} 
		
		else if (e.key.keysym.sym == SDLK_LCTRL) {
			cout << "Action: crouch" << endl;
		}
	}
}
