#pragma once

#include "SDL.h"
#include <iostream>

using namespace std;

class ControlComponent {
public:
	ControlComponent();
	void CheckKeyPress(SDL_Event e);
};
