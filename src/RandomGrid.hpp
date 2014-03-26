#pragma once

#include <vector>
#include <algorithm>

namespace game {

template <class T>
struct RandomGrid {
	RandomGrid();
	virtual ~RandomGrid();
	inline T& get(int i, int j);
	inline const T& get(int i, int j) const;
	void feed(size_t sx, size_t sy);
	size_t width() const;
	size_t height() const;
private:
	std::vector<T> _data;
	size_t _sx, _sy;
};

template <class T>
RandomGrid<T>::RandomGrid() 
	: _data(), _sx(0), _sy(0) {
}

template <class T> 
RandomGrid<T>::~RandomGrid() {

}

template <class T>
T& RandomGrid<T>::get(int i, int j) {
	return _data[j * _sx + i];
}

template <class T>
const T& RandomGrid<T>::get(int i, int j) const {
	return _data[j * _sx + i];
}

template <class T>
void RandomGrid<T>::feed(size_t sx, size_t sy) {
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
}

template <class T>
size_t RandomGrid<T>::width() const {
	return _sx;
}

template <class T>
size_t RandomGrid<T>::height() const {
	return _sy;
}

}