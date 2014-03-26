#pragma once

#include "GridDisplay.hpp"

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

namespace game {

struct Game {
	static const int WIDTH = 1024;
	static const int HEIGHT = 768;
	static const int FPS = 60;
	Game();
	~Game();
	void run();
	void preRender();
	void render();
	void update();
private:
	bool handleEvent(const SDL_Event& evt);

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	graphics::GridDisplay<RandomGrid<int>> _display;
};

}