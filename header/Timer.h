#pragma once

#include "SDL2/SDL.h"
#include "dependencies.h"

class Timer {
	u8 started = false;
	f64 startTime;
	f64 timeout;
	f64 timePassed;

public:
	void Start(f64 seconds);
	void Stop();
	void Count();
	u8 IsStarted();
};
