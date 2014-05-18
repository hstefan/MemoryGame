#include "SoundManager.hpp"

#include <SDL2/SDL_mixer.h>
#include <iostream>

using namespace sound;

SoundManager& SoundManager::instance() {
	static SoundManager inst;
	return inst;
}

SoundManager::SoundManager()
	: _music(nullptr), _flipFx(nullptr) {
}

void SoundManager::init() {
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		std::cout << "Failed to initialize audio" << std::endl;
	} else {
		std::cout << "Audio initialized" << std::endl;
	}

	_music = Mix_LoadMUS("data/ambient.ogg");
	_flipFx = Mix_LoadWAV("data/whip.wav");

}
SoundManager::~SoundManager() {	
	if (_music) {
		Mix_FreeMusic(_music);
	}
	if (_flipFx) {
		Mix_FreeChunk(_flipFx);
	}
}

void SoundManager::music(bool play) {
	if (play) {
		Mix_PlayMusic(_music, -1);
	} else {
		Mix_PauseMusic();
	}
}

void SoundManager::oneFlip() {
	Mix_PlayChannel(-1,  _flipFx, 0);
}
