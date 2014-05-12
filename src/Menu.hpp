#pragma once

#include "Text.hpp"

struct SDL_Renderer;
union SDL_Event;

namespace game {
enum class GameState;
} //namespace game

namespace ui {

struct Menu {
	explicit Menu();
	game::GameState update(game::GameState state);
	void render(SDL_Renderer* renderer);
	void handleEvent(const SDL_Event& evt);
	void reset();
private:
	Font _font;
	Text _msg;
	game::GameState _lastState;
	bool _init;
};

} //namespace ui
