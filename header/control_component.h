#pragma once

#include "SDL.h"

using namespace std;

class ControlComponent {
public:
	ControlComponent();
	void CheckKeyPress(SDL_Event e);
};
