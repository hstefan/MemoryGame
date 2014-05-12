#include "Menu.hpp"
#include "GameState.hpp"

#include <SDL2/SDL_render.h>

using namespace ui;

Menu::Menu() 
	: _font("data/couture/COUTURE-Bold.ttf", 32), _msg(TextType::Blended, &_font), 
	_lastState(game::GameState::WAITING), _init(false) {
}

game::GameState Menu::update(game::GameState state) {
	if (!_init || _lastState != state) {
		if (state == game::GameState::WAITING) {
			_msg.updateText("CLICK TO CONTINUE",
				SDL_Color { 255, 255, 255, 255 },
				SDL_Point { 364, 290 });
		}
		_init = true;
	}
	return _lastState;
}

void Menu::render(SDL_Renderer* renderer) {
	_msg.draw(renderer);
}

void Menu::handleEvent(const SDL_Event& evt) {
	if (evt.type == SDL_MOUSEBUTTONDOWN) {
		_init = false;
		_lastState = game::GameState::RUNNING;
	}
}

void Menu::reset() {
	_lastState = game::GameState::WAITING;
}
