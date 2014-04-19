#pragma once

#include <string>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

struct SDL_Renderer;
struct SDL_Texture;

namespace ui {

struct Font {
	Font(const char* path, size_t px);
	~Font();
	TTF_Font* ttf_font;
	const size_t px;
};

struct SolidText {
	SolidText(Font* font);
	~SolidText();
	void draw(SDL_Renderer* renderer);
	void updateText(const std::string& text, const SDL_Color& color, const SDL_Point& point);
private:
	SDL_Texture* _texture;
	Font* _font;
	SDL_Rect _dstRect;
	SDL_Rect _srcRect;
	std::string _text;
};

}//namespace ui
