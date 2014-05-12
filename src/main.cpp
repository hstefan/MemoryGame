#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Game.hpp"

int main(int, char**) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	game::Game g;
	g.run();

	SDL_Quit();
	return 0;
}
