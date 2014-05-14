solution "MemoryGame"
	configurations { "release", "debug" }

	flags { "FatalWarnings" }
	warnings "Extra"

	targetdir "bin"

	configuration "debug"
		defines { "DEBUG" }
		flags { "symbols" }
		optimize "Off"
	
	configuration "release"
		defines { "NDEBUG" }
		optimize "On"
	
	configuration "gmake"
		buildoptions { "-std=c++11", "-Wall"}

	project "MemoryGame"
		kind "ConsoleApp"
		language "c++"
		files { "src/**.cpp", "src/**.hpp", "src/**.c", "src/**.cpp" }
		includedirs { "src" }
		links { "SDL2", "SDL2_image", "SDL2_ttf", "SDL2_mixer" }

