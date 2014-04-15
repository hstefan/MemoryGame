#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <string>
#include <iostream>
#include "GameGrid.hpp"
#include "LevelInfo.hpp"
#include "util.hpp"

namespace graphics {

struct CardView {
	size_t imageIndex;
	SDL_Rect dstRect;
	SDL_Rect srcRect;
	size_t i;
	size_t j;
};

template <class T>
struct GridDisplay {
	GridDisplay();
	void feed(SDL_Renderer* render, T* grid, const std::vector<std::string>& idSprites, const SDL_Point& center);
	void render(SDL_Renderer* render);
	void loadTextures(SDL_Renderer* rend, const std::vector<std::string>& idSprites);
	void handleEvent(const SDL_Event& evt);
	void updateCards();
private:
	void unloadTextures();
	std::vector<CardView> _cards;
	std::vector<SDL_Texture*> _texes;
	int tw, th;
	T* _grid;
};

template <class T>
GridDisplay<T>::GridDisplay() {

}

template <class T>
void GridDisplay<T>::feed(SDL_Renderer* render, T* grid, 
	const std::vector<std::string>& idSprites, const SDL_Point& center) {
	_grid = grid;
	loadTextures(render, idSprites);
	//we'll assume every textures are of the same size (by now :P)
	SDL_Point topLeft;
	topLeft.x = static_cast<int>(center.x - (tw * _grid->width()) / 2);
	topLeft.y = static_cast<int>(center.y - (th * _grid->height()) / 2);

	SDL_Rect src;
	SDL_Rect dst;

	for (size_t i = 0; i < _grid->width(); ++i) {
		for (size_t j = 0; j < _grid->height(); ++j) {
			src.x = 0;
			src.y = 0;
			src.w = tw;
			src.h = th;
			dst.x = topLeft.x + (i * tw);
			dst.y = topLeft.y + (j * th);
			dst.w = tw;
			dst.h = th;
			_cards.push_back(CardView{ static_cast<size_t>((*_grid)(i, j)), dst, src, i, j });
		}
	}
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

template <class T>
void GridDisplay<T>::handleEvent(const SDL_Event& evt) {
	if (evt.type == SDL_MOUSEBUTTONDOWN) {
		for (auto& card : _cards) {
			if (util::insideRect(card.dstRect, evt.button.x, evt.button.y)) {
				_grid->onClick(card.i, card.j);
			}
		}
		updateCards();
	}
}

template <class T>
void  GridDisplay<T>::updateCards() {
	for (auto& card : _cards) {
		card.imageIndex = (*_grid)(card.i, card.j);
	}
}
}
