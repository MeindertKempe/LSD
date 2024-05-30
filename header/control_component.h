#pragma once

#include "SDL.h"
#include "game_object.h"
#include "component.h"

using namespace std;

enum Lane{
	Mid = 0,
	Right = 1,
	Left = 2
};

class ControlComponent : public Component {
	public:
		u32 lane = Mid;
		GameObject *player;
		ControlComponent() {};
		ControlComponent(GameObject* player) : player{player} {};
		void CheckKeyPress(SDL_Event e);
};
