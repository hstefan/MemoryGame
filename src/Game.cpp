#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"
#include "util.hpp"
#include "GameGrid.hpp"
#include "LevelInfo.hpp"
#include "GameState.hpp"

using namespace game;

SDL_Renderer* Game::Renderer = nullptr;

Game::Game()
	: _window(nullptr), _renderer(nullptr), _display(), _grid(0), _state(GameState::WAITING) {
	_window = SDL_CreateWindow("Tales of Matching Bunnies",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_OPENGL);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	Game::Renderer = _renderer;
	sound::SoundManager::instance().init();
	LevelInfo info("Bunnies", "data/bunnies/bunnies.txt");
	_grid.feed(info.width, info.height);
	_display.feed(_renderer, &_grid, info.sprites, SDL_Point{ WIDTH/2, HEIGHT/2 });
}

Game::~Game() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void Game::run() {
	sound::SoundManager::instance().music(true);
	bool running = true;
	SDL_Event evt;
	while (running) {
		auto starting_time = SDL_GetTicks();
		while (SDL_PollEvent(&evt)) {
			if (!handleEvent(evt)) {
				running = false;
			}
		}
		update();
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
	if (_state == GameState::RUNNING) {
		_display.render(_renderer);
	} else {
		_menu.render(_renderer);
	}
}

void Game::update() {
	//update game objects
	if (_state == GameState::RUNNING) {
		_grid.update();
		if (_grid.finished()) {
			_state = GameState::WAITING;
		}
		_menu.reset();
	} else {
		_state = _menu.update(_state);
		if (_state == GameState::RUNNING) //transition to "running" state
		{
			_grid.shuffle();
			_grid.resetRevealed();
			_display.updateCards();
		}
	}
}

bool Game::handleEvent(const SDL_Event& evt) {
	bool ret = true;
	if (_state == GameState::RUNNING) {
		_display.handleEvent(evt);
	} else {
		_menu.handleEvent(evt);
	}
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

GameState Game::state() const {
	return _state;
}
