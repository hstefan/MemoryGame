#include <SDL2/SDL.h>

#include "Game.hpp"
#include "util.hpp"
#include "GameGrid.hpp"
#include "LevelInfo.hpp"

using namespace game;

Game::Game() 
	: _window(nullptr), _renderer(nullptr), _display() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Memory Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_OPENGL);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	
	LevelInfo info("Bunnies", "data/bunnies/bunnies.txt");
	GameGrid<int> grid;
	grid.feed(info.width, info.height);
	_display.feed(_renderer, grid, info.sprites, SDL_Point{ WIDTH/2, HEIGHT/2 });
}

Game::~Game() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void Game::run() {
	bool running = true;
	SDL_Event evt;
	while (running) {
		auto starting_time = SDL_GetTicks();
		while (SDL_PollEvent(&evt)) {
			if (!handleEvent(evt)) {
				running = false;
			}
		}
		preRender();
		render();
		SDL_RenderPresent(_renderer);

		auto elapsed_time = SDL_GetTicks() - starting_time;
		SDL_Delay(util::clamp(1000U / FPS - elapsed_time, 0U, 1000U / FPS));
	}
}

void Game::preRender() {
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 1);
	SDL_RenderClear(_renderer);
}

void Game::render() {
	//draw stuff
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	_display.render(_renderer);
}

void Game::update() {
	//update game objects
}

bool Game::handleEvent(const SDL_Event& evt) {
	bool ret = true;
	switch (evt.type) {
	case SDL_KEYDOWN:
		if (evt.key.keysym.sym == SDLK_ESCAPE)
			ret = false;
		break;
	case SDL_QUIT:
		ret = false;
		break;
	}
	return ret;
}