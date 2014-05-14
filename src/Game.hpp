#pragma once

#include "GridDisplay.hpp"
#include "GameGrid.hpp"
#include "Menu.hpp"
#include "SoundManager.hpp"

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

namespace game {

enum class GameState;

struct Game {
	typedef GameGrid<int> GameGridType;
	static SDL_Renderer* Renderer;
	static const int WIDTH = 1024;
	static const int HEIGHT = 768;
	static const int FPS = 60;
	Game();
	~Game();
	void run();
	void preRender();
	void render();
	void update();
	GameState state() const;
private:
	bool handleEvent(const SDL_Event& evt);

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	graphics::GridDisplay<GameGridType> _display;
	GameGridType _grid;
	GameState _state;
	ui::Menu _menu;
	sound::SoundManager _soundMan;
};

}
