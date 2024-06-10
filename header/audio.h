#pragma once
#include "dependencies.h"
#include "miniaudio.h"
//
// Created by Cam on 30/05/2024.
//

class Audio {
	ma_engine engine;

public:
	Audio();
	~Audio();
	void initEngine();
	void playBGM();
	void playCoin();
};
