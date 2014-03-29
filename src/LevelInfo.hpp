#pragma once

#include <vector>
#include <string>

namespace game {

struct LevelInfo {
	LevelInfo(const char* levelName, const char* descFile);
	
	std::vector<std::string> sprites;
	std::string hiddenSprite;
	const std::string levelName;
	const std::string descriptFile;
	size_t width;
	size_t height;
};

}