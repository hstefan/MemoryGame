#include "util.hpp"
#include <SDL2/SDL_rect.h>

bool util::insideRect(const SDL_Rect& rect, int x, int y) {
	return x >= rect.x && y >= rect.y && x < rect.x + rect.w && y < rect.y + rect.h;
}