#pragma once

#include <vector>
#include <algorithm>
#include <chrono>

namespace game {

template <class T>
struct GameGrid {
	GameGrid(T hiddenId = T());
	virtual ~GameGrid();
	inline T& get(int i, int j);
	inline const T& get(int i, int j) const;
	void feed(size_t sx, size_t sy);
	size_t width() const;
	size_t height() const;
private:
	std::vector<T> _data;
	std::vector<bool> _revealed;
	size_t _sx, _sy;
	T _hiddenId;
};

template <class T>
GameGrid<T>::GameGrid(T hiddenId)
	: _data(), _sx(0), _sy(0), _hiddenId(hiddenId) {
	std::srand(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
}

template <class T> 
GameGrid<T>::~GameGrid() {

}

template <class T>
T& GameGrid<T>::get(int i, int j) {
	int hash = j * _sx + i;
	if (_revealed[hash])
		return _data[hash];
	else
		return _hiddenId;
}

template <class T>
const T& GameGrid<T>::get(int i, int j) const {
	int hash = j * _sx + i;
	if (_revealed[hash])
		return _data[hash];
	else
		return _hiddenId;
}

template <class T>
void GameGrid<T>::feed(size_t sx, size_t sy) {
	_data.clear();
	_sx = sx;
	_sy = sy;
	_data.reserve(sx * sy);
	std::vector<size_t> indices;
	std::vector<size_t> data;
	for (size_t i = 0; i < sx * sy; ++i) {
		indices.push_back(i);
		if (i < sx * sy) {
			data.push_back(i);
			data.push_back(i);
		}
	}
	std::random_shuffle(std::begin(indices), std::end(indices));
	
	for (size_t i = 0; i < indices.size(); ++i) {
		_data.push_back(data[indices[i]]);
	}
	_revealed.resize(_data.size(), false);
}

template <class T>
size_t GameGrid<T>::width() const {
	return _sx;
}

template <class T>
size_t GameGrid<T>::height() const {
	return _sy;
}

}