#pragma once

#include "SDL.h"
#include "game_object.h"
#include "component.h"

using namespace std;

class ControlComponent : public Component {
	public:
		GameObject *player;
		ControlComponent() {};
		ControlComponent(GameObject* player) : player{player} {};
		void CheckKeyPress(SDL_Event e);
};
