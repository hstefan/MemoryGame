#pragma once

typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

namespace sound {

struct SoundManager {
	static SoundManager& instance();
	~SoundManager();
	void init();
	void music(bool play);
	void oneFlip();
private:
	SoundManager();
	SoundManager(const SoundManager& soundManager);
	SoundManager& operator=(SoundManager& smanager);

	Mix_Music* _music;
	Mix_Chunk* _flipFx;
};

} //namespace sound
