#pragma once

#include <vector>
#include <algorithm>
#include <chrono>
#include <tuple>
#include <numeric>
#include "util.hpp"

namespace game {

template <class T>
struct GameGrid {
	GameGrid(T hiddenId = T());
	virtual ~GameGrid();
	inline T& operator() (int i, int j);
	inline const T& operator() (int i, int j) const;
	void feed(size_t sx, size_t sy);
	size_t width() const;
	size_t height() const;
	void setReveal(size_t i, size_t j, bool revealed);
	void onClick(size_t i, size_t j);
	void update();
	bool compareEqual(const std::tuple<size_t, size_t>& a, const std::tuple<size_t, size_t>& b);
	bool compareEqual(size_t ia, size_t ja, size_t ib, size_t jb);
private:
	inline size_t hash(size_t i, size_t j) const;
	std::vector<T> _data;
	std::vector<bool> _revealed;
	std::vector<std::tuple<size_t, size_t>> _revealBuff;
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
size_t GameGrid<T>::hash(size_t i, size_t j) const {
	return j * _sx + i;
}

template <class T>
T& GameGrid<T>::operator()(int i, int j) {
	if (_revealed[hash(i, j)])
		return _data[hash(i, j)];
	else
		return _hiddenId;
}

template <class T>
const T& GameGrid<T>::operator()(int i, int j) const {
	if (_revealed[hash(i, j)])
		return _data[hash(i, j)];
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
	indices.resize(sx * sy, 0);
	std::iota(RANGE(indices), 0);
	
	std::vector<size_t> data;

	for (size_t i = 0; i < sx * sy; ++i) {
		data.push_back(i + 1);
		data.push_back(i + 1);
	}
	std::random_shuffle(RANGE(indices));
	
	for (auto i : indices) {
		_data.push_back(data[i]);
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

template <class T>
void GameGrid<T>::setReveal(size_t i, size_t j, bool revealed) {
	_revealed[hash(i, j)] = revealed;
}

template <class T>
void GameGrid<T>::onClick(size_t i, size_t j) {
	auto cardOnBuff = std::any_of(RANGE(_revealBuff),
		[&](const std::tuple<size_t, size_t>& elem)
		{ return std::get<0>(elem) == i && std::get<1>(elem) == j; }
	);
	if (!cardOnBuff) //this means the new card WASN'T already in the buffer
	{
		if (_revealBuff.size() >= 2) { //hide all cards
			auto count = static_cast<size_t>(std::count_if(RANGE(_revealBuff),
				[&](const std::tuple<size_t, size_t>& elem) {
					return compareEqual(elem, _revealBuff[0]);
				}
			));
			if (count < _revealBuff.size()) {
				for (auto& c : _revealBuff) {
					setReveal(std::get<0>(c), std::get<1>(c), false);
				}
			}
			_revealBuff.clear();
		}
		if (!_revealed[hash(i, j)]) {
			_revealBuff.push_back(std::make_tuple(i, j));
			setReveal(i, j, true);
		}
	}
}

template <class T>
void GameGrid<T>::update() {
	
}

template <class T>
bool GameGrid<T>::compareEqual(const std::tuple<size_t, size_t>& a, const std::tuple<size_t, size_t>& b) {
	return compareEqual(std::get<0>(a), std::get<1>(a), std::get<0>(b), std::get<1>(b));
}

template <class T>
bool GameGrid<T>::compareEqual(size_t ia, size_t ja, size_t ib, size_t jb) {
	return (*this)(ia, ja) == (*this)(ib, jb);
}

}