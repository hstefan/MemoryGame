#include "Text.hpp"
#include "Game.hpp"

#include <SDL2/SDL_render.h>
#include <iostream>

namespace ui {

Font::Font(const char* path, size_t px) 
	: ttf_font(nullptr), px(px) {
	ttf_font = TTF_OpenFont(path, px);
	if (ttf_font == nullptr)
		std::cout << "Failed to read " << path << std::endl << TTF_GetError() << std::endl;
}

Font::~Font() {
	if (ttf_font != nullptr)
		TTF_CloseFont(ttf_font);
}

SolidText::SolidText(Font* font)
	: _texture(nullptr), _font(font) {
	
}

SolidText::~SolidText() {
	if (_texture != nullptr)
		SDL_DestroyTexture(_texture);
}

void SolidText::updateText(const std::string& text, const SDL_Color& color, const SDL_Point& point) {
	if (_text !=  text) {
		_text = text;
		if (_texture != nullptr)
			SDL_DestroyTexture(_texture);
		auto surf = TTF_RenderText_Solid(_font->ttf_font, text.c_str(), color);
		if (surf != nullptr) {
			_texture = SDL_CreateTextureFromSurface(game::Game::Renderer, surf);
			_srcRect = { 0, 0, surf->w, surf->h };
			_dstRect = { point.x, point.y, surf->w, surf->h };
			SDL_FreeSurface(surf);
		}
	}
}

void SolidText::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, _texture, &_srcRect, &_dstRect);
}

} //namespace ui
