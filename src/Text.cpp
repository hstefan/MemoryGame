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

Text::Text(TextType type, Font* font)
	: type(type), _texture(nullptr), _font(font), _dstRect(), _srcRect(), _text() {
	
}

Text::~Text() {
	if (_texture != nullptr)
		SDL_DestroyTexture(_texture);
}

void Text::updateText(const std::string& text, const SDL_Color& color, const SDL_Point& point) {
	if (_text !=  text) {
		_text = text;
		if (_texture != nullptr)
			SDL_DestroyTexture(_texture);
		SDL_Surface* surf = nullptr;
		if (type == TextType::Solid) {
			surf = TTF_RenderUTF8_Solid(_font->ttf_font, text.c_str(), color);
		} else if (type == TextType::Blended) {
			surf = TTF_RenderUTF8_Blended(_font->ttf_font, text.c_str(), color);
		}
		if (surf != nullptr) {
			_texture = SDL_CreateTextureFromSurface(game::Game::Renderer, surf);
			_srcRect = { 0, 0, surf->w, surf->h };
			_dstRect = { point.x, point.y, surf->w, surf->h };
			SDL_FreeSurface(surf);
		}
	}
}

void Text::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, _texture, &_srcRect, &_dstRect);
}

} //namespace ui
