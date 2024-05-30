#include "audio.h"
#include "bass.h"

Audio::Audio() {}
Audio::~Audio() {}

void Audio::initEngine() {
	BASS_Init(-1, 48000, 0, nullptr, nullptr);
}

void Audio::playBGM() {
	HSAMPLE sample1 = BASS_SampleLoad(FALSE, "resource/audio/BGM.wav", 0, 0, 1, BASS_SAMPLE_FLOAT);
	HCHANNEL channel1 = BASS_SampleGetChannel(sample1, FALSE);
	BASS_ChannelPlay(channel1, FALSE);
}

void Audio::playCoin() {
	HSAMPLE sample2 = BASS_SampleLoad(FALSE, "resource/audio/coin.wav", 0, 0, 1, BASS_SAMPLE_FLOAT);
	HCHANNEL channel2 = BASS_SampleGetChannel(sample2, FALSE);
	BASS_ChannelPlay(channel2, FALSE);
}
