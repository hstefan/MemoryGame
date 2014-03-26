#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include "RandomGrid.hpp"
#include <fstream>
#include <string>

namespace graphics {

struct CardView {
	size_t imageIndex;
	SDL_Rect dstRect;
	SDL_Rect srcRect;
};

template <class T>
struct GridDisplay {
	GridDisplay();
	void feed(SDL_Renderer* render, const T& grid, const std::vector<std::string>& idSprites, const SDL_Point& center);
	void feed(SDL_Renderer* render, const T& grid, const char* descFile, const SDL_Point& center);
	void render(SDL_Renderer* render);
	void loadTextures(SDL_Renderer* rend, const std::vector<std::string>& idSprites);
private:
	void unloadTextures();
	std::vector<CardView> _cards;
	std::vector<SDL_Texture*> _texes;
	int tw, th;
};

template <class T>
GridDisplay<T>::GridDisplay() {

}

template <class T>
void GridDisplay<T>::feed(SDL_Renderer* render, const T& grid, 
	const std::vector<std::string>& idSprites, const SDL_Point& center) {
	loadTextures(render, idSprites);
	//we'll assume every textures are of the same size (by now :P)
	SDL_Point topLeft;
	/*topLeft.x = static_cast<int>(center.x - tw / 2 - (grid.width() % 2 * tw / 2));
	topLeft.y = static_cast<int>(center.y - th / 2 - (grid.height() % 2 * th / 2));*/

	topLeft.x = static_cast<int>(center.x - (tw * grid.width()) / 2);
	topLeft.y = static_cast<int>(center.y - (th * grid.height()) / 2);

	SDL_Rect src;
	SDL_Rect dst;

	for (size_t i = 0; i < grid.width(); ++i) {
		for (size_t j = 0; j < grid.height(); ++j) {
			src.x = 0;
			src.y = 0;
			src.w = tw;
			src.h = th;
			dst.x = topLeft.x + (i * tw);
			dst.y = topLeft.y + (j * th);
			dst.w = tw;
			dst.h = th;
			_cards.push_back(CardView{ grid.get(i, j), dst, src });
		}
	}
}

template <class T>
void GridDisplay<T>::feed(SDL_Renderer* render, const T& grid, const char* descFile, const SDL_Point& center) {
	std::vector<std::string> files;
	std::fstream f(descFile);
	if (f.is_open()) {
		std::string tmp;
		while (std::getline(f, tmp)) {
			files.push_back(tmp);
		}
	}
	feed(render, grid, files, center);
}

template <class T>
void GridDisplay<T>::loadTextures(SDL_Renderer* rend, const std::vector<std::string>& idSprites) {
	unloadTextures();
	SDL_Surface* surf;
	for (auto& spr : idSprites) {
		surf = IMG_Load(spr.c_str());
		tw = surf->w;
		th = surf->h;
		_texes.push_back(SDL_CreateTextureFromSurface(rend, surf));
		SDL_FreeSurface(surf);
	}
}

template <class T>
void GridDisplay<T>::render(SDL_Renderer* render) {
	for (auto& card : _cards) {
		SDL_RenderCopy(render, _texes[card.imageIndex % _texes.size()], &card.srcRect, &card.dstRect);
	}
}

template <class T>
void GridDisplay<T>::unloadTextures() {
	for (auto tex : _texes) {
		SDL_DestroyTexture(tex);
	}
	_texes.clear();
}

}