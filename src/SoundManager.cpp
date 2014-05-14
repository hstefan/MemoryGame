#include "SoundManager.hpp"

#include <SDL2/SDL_mixer.h>
#include <iostream>

using namespace sound;

SoundManager::SoundManager()
	: _music(nullptr) {
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
}

SoundManager::~SoundManager() {	
	if (_music != nullptr) {
		Mix_FreeMusic(_music);
	}
}

void SoundManager::music(bool play) {
	if (play) {
		if (_music != nullptr) {
			Mix_PlayMusic(_music, -1);
		}
	} else {
		if (_music != nullptr) {
			Mix_PauseMusic();
		}
	}
}
