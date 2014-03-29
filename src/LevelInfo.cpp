#include "LevelInfo.hpp"

#include <fstream>
#include <cmath>

using namespace game;

LevelInfo::LevelInfo(const char* levelName, const char* descFile) 
	: sprites(), levelName(levelName), descriptFile(descFile),  width(0U), 
	height(0U)
{
	std::ifstream f(descriptFile);
	if (f.is_open()) {
		std::string tmp;
		while (std::getline(f, tmp)) {
			sprites.push_back(tmp);
		}
		const auto numSlots = sprites.size() * 2;
		width = static_cast<size_t>(std::round(std::sqrt(numSlots)));
		height = numSlots / width;
	}
}

