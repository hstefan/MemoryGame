#include <SDL2/SDL.h>
#include "Game.hpp"

int main(int, char**) {
	game::Game g;
	g.run();

	SDL_Quit();
	return 0;
}
