#pragma once

#include <string>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#include <utility>

struct SDL_Renderer;
struct SDL_Texture;

namespace ui {

enum class TextType {
	Solid,
	Blended,
};

struct Font {
	Font(const char* path, size_t px);
	~Font();
	TTF_Font* ttf_font;
	const size_t px;
};

struct Text {
	Text(TextType type, Font* font);
	~Text();
	void draw(SDL_Renderer* renderer);
	void updateText(const std::string& text, const SDL_Color& color, const SDL_Point& point);
	const TextType type;
	std::pair<int, int> size();
	std::string text() const;
private:
	SDL_Texture* _texture;
	Font* _font;
	SDL_Rect _dstRect;
	SDL_Rect _srcRect;
	std::string _text;
};

}//namespace ui
