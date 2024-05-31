#define MINIAUDIO_IMPLEMENTATION
#include "audio.h"
#include <iostream>

Audio::Audio() {}
Audio::~Audio() {}

void Audio::initEngine() {
	ma_result result;
	result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
       std::cout << "failed to start audio /n";
    }
}

void Audio::playBGM() {
	ma_engine_play_sound(&engine, "resources/audio/BGM.wav", NULL);
}

void Audio::playCoin() {
	ma_engine_play_sound(&engine, "resources/audio/coin.wav", NULL);
}
