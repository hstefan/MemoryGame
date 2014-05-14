#pragma once

typedef struct _Mix_Music Mix_Music;

namespace sound {

struct SoundManager {
	SoundManager();
	~SoundManager();
	void music(bool play);
private:
	Mix_Music* _music;
};

} //namespace sound
